#include <iostream>
#include "level.hpp"
#include "../debug.hpp"
#include "../entity/map_object.hpp"
#include "../game.hpp"

const int Level::FOLLOW_MARGIN = 200;
const int Level::MAX_NODES_PER_TICK = 300;

Level::Level(const char *map) :
        super(map),
        position_(vec2f(0, 0))
{
    nodes_ = std::vector<std::vector<Path::Node*>>(map_->height_pixels / Path::RESOLUTION,
            std::vector<Path::Node*>(map_->width_pixels / Path::RESOLUTION, 0));
    dynamic_collidables_ = new Quadtree(0, Rectangle(0, 0, map_->width_pixels, map_->height_pixels));

    for(const auto& k : map_->object_groups) {
        const TMX::ObjectGroup& object_group = k.second;

        for(const TMX::Object& object : object_group.object) {
            MapObject* map_object = new MapObject(tileset_->sprite(object.gid - 1), object.x, object.y - 16);
            AddEntity(map_object);
        }
    }
}

void Level::Update(double delta) {
    // We calculate one path per game tick
    // This way we distribute work in different ticks
    if(!path_queue_.empty())
        CalculatePath();

    for(Entity* entity : entities_) {
        if(entity->IsMob()) {
            dynamic_collidables_->Remove(entity);

            entity->Update(delta);

            if (entity->IsAlive()) {
                dynamic_collidables_->Insert(entity);
                temp_entities_.push_back(entity);
            } else if (entity != main_player_) {
                delete entity;
            }
        } else {
            if(entity->IsAlive()) {
                temp_entities_.push_back(entity);
            } else {
                dynamic_collidables_->Remove(entity);
                delete entity;
            }
        }
    }

    // We need to update the set in order to keep it sorted
    // TODO: Do the sorting when rendering?
    entities_.clear();
    entities_.insert(temp_entities_.begin(), temp_entities_.end());
    temp_entities_.clear();
}

void Level::Render() {
    // Recalculate scrolling
    const vec2f& player_position = main_player_->position();
    float right = position_.x + Game::WIDTH;
    float bottom = position_.y + Game::HEIGHT;

    float left_limit = position_.x + FOLLOW_MARGIN;
    float top_limit = position_.y + FOLLOW_MARGIN;
    float right_limit = right - FOLLOW_MARGIN;
    float bottom_limit = bottom - FOLLOW_MARGIN;

    if(right < map_->width_pixels and player_position.x > right_limit)
        position_.x = std::min((float)(map_->width_pixels - Game::WIDTH),
                position_.x + player_position.x - right_limit);

    else if(position_.x > 0 and player_position.x < left_limit)
        position_.x = std::max(0.0f, position_.x + player_position.x - left_limit);

    if(bottom < map_->height_pixels and player_position.y > bottom_limit)
        position_.y = std::min((float)(map_->height_pixels - Game::HEIGHT),
                position_.y + player_position.y - bottom_limit);

    else if(position_.y > 0 and player_position.y < top_limit)
        position_.y = std::max(0.0f, position_.y + player_position.y - top_limit);

    glTranslatef(-position_.x, -position_.y, 0);

    // Rendering
    super::RenderLayersBelow();

    // TODO: Render visible entities only
    for(Entity* entity : entities_) {
        entity->Render();
    }

    super::RenderLayersAbove();

    if(Debug::enabled) {
        dynamic_collidables_->Render(1, 0, 0);

        // Show collidable candidates
        std::vector<Rectangle*> candidates;

        for(Entity* entity : entities_) {
            if(entity->IsMob()) {
                static_collidables_->Retrieve(entity, candidates);
                dynamic_collidables_->Retrieve(entity, candidates);
            }
        }

        for(Rectangle* candidate : candidates)
            candidate->Render(1, 0, 1);
    }
}

void Level::AddEntity(Entity* entity) {
    entities_.insert(entity);
    dynamic_collidables_->Insert(entity);
}

void Level::AddPlayer(Entity* player) {
    if(!main_player_)
        main_player_ = player;
    players_.push_back(player);
    AddEntity(player);
}

void Level::CollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const {
    super::CollidablesFor(rectangle, collidables);
    dynamic_collidables_->Retrieve(rectangle, collidables);
}

void Level::DynamicCollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const {
    dynamic_collidables_->Retrieve(rectangle, collidables);
}

Path* Level::FindPath(Mob* from, Entity* to) {
    Path* path = new Path(from, to);
    path_queue_.push(path);
    return path;
}

void Level::CalculatePath() {
    Path& path = *path_queue_.front();
    Path::Node* start = *path.pending.begin();

    if(not path.calculating) {
        // Clear unused nodes from last search
        for(int i = 0; i < nodes_.size(); ++i) {
            for(int j = 0; j < nodes_[0].size(); ++j) {
                if(nodes_[i][j]) {
                    delete nodes_[i][j];
                    nodes_[i][j] = 0;
                }
            }
        }

        nodes_[start->y][start->x] = start;
        path.calculating = true;
    }

    std::vector<Rectangle*> collision_candidates;
    bool collision;
    int i = 0;

    while(not path.pending.empty()) {
        if(i > MAX_NODES_PER_TICK)
            return;

        Path::Node* current = *path.pending.begin();
        path.pending.erase(path.pending.begin());
        current->closed = true;
        i++;

        path.rectangle->set_position(current->x * Path::RESOLUTION, current->y * Path::RESOLUTION);

        if(not IsInbounds(path.rectangle))
            continue;

        collision_candidates.clear();
        collision = false;
        CollidablesFor(path.rectangle, collision_candidates);

        for(Rectangle* candidate : collision_candidates) {
            if(candidate == path.to) {
                if(path.rectangle->CollidesWith(candidate)) {
                    // Path found
                    while(current) {
                        nodes_[current->y][current->x] = 0;
                        path.nodes.push_back(current);
                        current = current->parent;
                    }

                    // Remove start node
                    path.nodes.pop_back();
                    path.ready = true;
                    path.found = true;
                    path.pending.clear();
                    path_queue_.pop();
                    return;
                }
            } else {
                collision = collision or path.from->CanCollideWith(candidate) && path.rectangle->CollidesWith(candidate);
            }
        }

        if(not collision || current == start) {
            for(const vec2i& dir : Dir::VECTORS) {
                int x = current->x - dir.x;
                int y = current->y - dir.y;

                if(x < 0 or y < 0 or x >= nodes_[0].size() or y >= nodes_.size())
                    continue;

                Path::Node* neighbor = nodes_[y][x];

                if(not neighbor) {
                    neighbor = new Path::Node(vec2i(x, y), path.destination, current->g_cost, current);
                    nodes_[y][x] = neighbor;
                    path.pending.insert(neighbor);
                } else if(neighbor->g_cost > current->g_cost + 1) {
                    if(not neighbor->closed)
                        path.pending.erase(neighbor);

                    neighbor->UpdateGCost(current->g_cost + 1);
                    path.pending.insert(neighbor);
                }
            }
        }
    }

    // Path not found
    path.ready = true;
    path_queue_.pop();
}

const std::vector<Entity*>& Level::players() const {
    return players_;
}
