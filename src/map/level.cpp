#include <iostream>
#include "level.hpp"
#include "level_events.hpp"
#include "events/intro.hpp"
#include "../debug.hpp"
#include "../entity/object.hpp"
#include "../game.hpp"
#include "../entity/object/plant.hpp"
#include "../entity/event/map_transition.hpp"
#include "../audio/music.hpp"
#include "../entity/door/key_door.hpp"
#include "../entity/object/pole_switch.hpp"
#include "../entity/object/pole.hpp"
#include "../entity/mob/stalfos.hpp"
#include "../entity/mob/guard.hpp"
#include "../entity/mob/linkfollower.hpp"


const int Level::FOLLOW_MARGIN = 120;
const int Level::MAX_NODES_PER_TICK = 600;
std::map<std::string, LevelEvents*> Level::LEVEL_EVENTS;

Level::Level(const char *map, Hud* hud) :
        super(map),
        name_(map),
        hud_(hud),
        current_frame_(0),
        accum_(0),
        position_(vec2f(0, 0)),
        main_player_(0),
        transition_requested_(false)
{
    nodes_ = std::vector<std::vector<Path::Node*>>(map_->height_pixels / Path::RESOLUTION,
            std::vector<Path::Node*>(map_->width_pixels / Path::RESOLUTION, 0));
    dynamic_collidables_ = new Quadtree(0, Rectangle(0, 0, map_->width_pixels, map_->height_pixels));

    for(auto& g : map_->object_groups) {
        TMX::ObjectGroup& object_group = g.second;

        for(auto& o : object_group.objects) {
            TMX::Object& object = o.second;

            if(object.type == "location") {
                Location* location = new Location(object.x, object.y, object.width, object.height, object.name,
                    object.property["orientation"]);
                AddLocation(location);
            } else {
                Entity* map_object = 0;

                if(object.type == "plant") {
                    map_object = new Plant(tileset_->sprite(object.gid), object.x, object.y - 16);
                } else if(object.type == "key_door") {
                    map_object = new KeyDoor(object.x, object.y - 16, object.gid, tileset_);
                } else if(object.type == "pole_switch") {
                    map_object = new PoleSwitch(object.x, object.y - 16,
                            tileset_->sprite(object.gid), tileset_->sprite(object.gid + 1));
                } else if(object.type == "blue_pole" or object.type == "yellow_pole") {
                    map_object = new Pole(object.x, object.y - 16,
                            object.type == "blue_pole" ? Pole::Type::BLUE : Pole::Type::YELLOW,
                            tileset_->sprite(object.gid), tileset_->sprite(object.gid+1));
                } else if(object.type == "stalfos") {
                    map_object = new Stalfos(object.x, object.y - 16);
                } else if(object.type == "guard") {
                    map_object = new Guard(object.x, object.y - 16);
                }
                else if(object.type == "follower") {
                    map_object = new LinkFollower(object.x, object.y - 16);
                }

                if(map_object)
                    AddEntity(map_object);
            }

            // Events
            if(object.type == "map_transition") {
                MapTransition* transition = new MapTransition(this, object.x, object.y, object.width, object.height,
                        object.name, object.property["orientation"], object.property["map"], object.property["place"]);
                AddCollidable(transition);
            }
        }
    }

    if(not map_->tilesets[0]->music.empty()) {
        if(not map_->tilesets[0]->intro.empty())
            Music::Enqueue(map_->tilesets[0]->intro, Music::NO_LOOP);

        Music::Enqueue(map_->tilesets[0]->music, Music::LOOP);
    }

    show_hud_ = map_->tilesets[0]->show_hud;

    if(LEVEL_EVENTS.find(std::string(map)) != LEVEL_EVENTS.end())
        events_ = LEVEL_EVENTS[name_];
    else
        events_ = 0;
}

Level::~Level() {
    delete dynamic_collidables_;

    for(Entity* entity : alive_entities_) {
        if(entity->type() != PLAYER)
            delete entity;
    }

    for(Entity* zombie : zombies_) {
        if(zombie->type() != PLAYER)
            delete zombie;
    }

    for(const auto& klocation : locations_) {
        delete klocation.second;
    }

    for(const auto& row : nodes_) {
        for(Path::Node* node : row) {
            if(node)
                delete node;
        }
    }

    for(Path* path : pending_paths_)
        delete path;
}

void Level::Init() {
    if(events_) {
        // Trigger start event
        LevelEvents::LevelEvent event = events_->event("start");

        if(event)
            event(this);
    }
}


void Level::Update(double delta) {
    if(tileset_->frames > 1) {
        // Update the current map frame
        accum_ += delta;

        if(accum_ >= tileset_->interval) {
            accum_ -= tileset_->interval;

            if(tileset_->random) {
                int old = current_frame_;
                current_frame_ = rand() % tileset_->frames;

                if(old == current_frame_)
                    current_frame_ = (current_frame_ + 1) % tileset_->frames;
            } else {
                current_frame_ = (current_frame_ + 1) % tileset_->frames;
            }
        }
    }

    // We calculate one path per game tick
    // This way we distribute work in different ticks
    if(!pending_paths_.empty())
        CalculatePath();

    // Zombies are entities that are dying :(
    std::vector<Entity*>::iterator it = zombies_.begin();
    while(it != zombies_.end()) {
        Entity* zombie = *it;
        entities_.erase(zombie);

        if(zombie->IsFinallyDead()) {
            zombie->Dead();

            it = zombies_.erase(it);

            if(zombie != main_player_)
                delete zombie;
        } else {
            zombie->Tick(delta);
            entities_.insert(zombie);
            it++;
        }
    }

    it = alive_entities_.begin();
    while(it != alive_entities_.end()) {
        Entity* entity = *it;

        if(entity->IsMob()) {
            entities_.erase(entity);
            dynamic_collidables_->Remove(entity);

            entity->Tick(delta);

            entities_.insert(entity);

            if (entity->IsAlive()) {
                dynamic_collidables_->Insert(entity);
                ++it;
            } else {
                entity->Die();

                RemovePendingPaths(entity);
                zombies_.push_back(entity);
                it = alive_entities_.erase(it);
            }
        } else {
            entity->Tick(delta);

            if(entity->IsAlive()) {
                ++it;
            } else {
                entity->Die();

                RemovePendingPaths(entity);
                dynamic_collidables_->Remove(entity);
                zombies_.push_back(entity);
                it = alive_entities_.erase(it);
            }
        }
    }

    if(main_player_->moving())
        CalculateScrolling();
}

void Level::Draw() const {
    glTranslatef(-position_.x * Game::SCALE, -position_.y * Game::SCALE, 0);
    glScalef(Game::SCALE, Game::SCALE, 0);

    // Rendering
    super::RenderLayersBelow(current_frame_);

    // Render visible entities only
    Game::RECTANGLE.set_position(position_.x, position_.y);
    Rectangle* view = &Game::RECTANGLE;
    for(Entity* entity : entities_) {
        if(entity->CollidesWith(view))
            entity->Render();
    }

    super::RenderLayersAbove();

    if(Debug::enabled) {
        dynamic_collidables_->Render(1, 0, 0);

        // Show collidable candidates
        std::vector<Rectangle*> candidates;

        for(Entity* entity : players_) {
            if(entity->IsMob()) {
                static_collidables_->Retrieve(entity, candidates);
                dynamic_collidables_->Retrieve(entity, candidates);
            }
        }

        for(Rectangle* candidate : candidates)
            candidate->DrawBox(1, 0, 1);
    }

    if(show_hud_)
        hud_->Render();
}

void Level::AddLocation(Location* location) {
    locations_[location->name()] = location;
}

void Level::AddCollidable(Rectangle* rectangle) {
    dynamic_collidables_->Insert(rectangle);
}

void Level::AddEntity(Entity* entity) {
    entity->set_level(this);

    if(entity->IsAlive())
        alive_entities_.push_back(entity);
    else
        zombies_.push_back(entity);

    entities_.insert(entity);
    AddCollidable(entity);
}

void Level::AddPlayer(Entity* player, std::string location) {
    std::cout << "ola k ase" << std::endl;
    std::map<std::string, Location*>::iterator it = locations_.find(location);

    if(it == locations_.end()) {
        std::cerr << "Location not found: " << location << std::endl;
        exit(1);
    }

    Location* location_object = it->second;
    location_object->Place(player);

    if(!main_player_) {
        main_player_ = player;
        CalculateScrolling();
    }

    players_.push_back(player);
    AddEntity(player);
}

void Level::AddPlayer(Entity* player) {

    if(!main_player_) {
        main_player_ = player;
        CalculateScrolling();
    }

    players_.push_back(player);
    AddEntity(player);
}

const std::vector<Entity*>& Level::players() const {
    return players_;
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
    pending_paths_.push_back(path);
    return path;
}

void Level::CalculatePath() {
    // A*
    Path& path = *pending_paths_.front();

    if(not path.calculating) {
        // Clear unused nodes from last search
        for(int i = 0; i < nodes_.size(); ++i) {
            for(int j = 0; j < nodes_[0].size(); ++j) {
                delete nodes_[i][j];
                nodes_[i][j] = 0;
            }
        }

        Path::Node* start = new Path::Node(path.origin, path.destination, 0, 0);
        nodes_[start->y][start->x] = start;
        path.pending.insert(start);
        path.calculating = true;
    }

    Path::Node* start = *path.pending.begin();
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
                        path.nodes.push_back(vec2i(current->x, current->y));
                        current = current->parent;
                    }

                    path.nodes.pop_back();
                    path.ready = true;
                    path.found = true;
                    path.pending.clear();
                    pending_paths_.pop_front();
                    return;
                }
            } else {
                collision = collision or path.from->CanCollideWith(candidate) && path.rectangle->CollidesWith(candidate);
            }
        }

        if(not collision or current == start) {
            for(const vec2i& dir : Dir::VECTORS) {
                int x = current->x + dir.x;
                int y = current->y + dir.y;

                if(x < 0 or y < 0 or x >= nodes_[0].size() or y >= nodes_.size())
                    continue;

                Path::Node* neighbor = nodes_[y][x];

                if(not neighbor) {
                    neighbor = new Path::Node(vec2i(x, y), path.destination, current->g_cost, current);
                    nodes_[y][x] = neighbor;
                    path.pending.insert(neighbor);
                } else if(not neighbor->closed and neighbor->g_cost > current->g_cost + 1) {
                    path.pending.erase(neighbor);
                    neighbor->UpdateGCost(current->g_cost + 1);
                    path.pending.insert(neighbor);
                }
            }
        }
    }

    // Path not found
    path.ready = true;
    pending_paths_.pop_front();
}

void Level::RemovePendingPaths(Entity* entity) {
    std::list<Path*>::iterator it = pending_paths_.begin();
    while(it != pending_paths_.end()) {
        Path* path = *it;

        if(path->from == entity)
            it = pending_paths_.erase(it);
        else if(path->to == entity) {
            path->ready = true;
            path->found = false;
            path->calculating = true;
            it = pending_paths_.erase(it);
        } else {
            ++it;
        }
    }
}

void Level::Transition(const std::string& map, const std::string& place_) {
    transition_requested_ = true;
    transition_map_ = map;
    transition_place_ = place_;
}

bool Level::transition_requested() const {
    return transition_requested_;
}


void Level::consume_transition(std::string& map, std::string& place) {
    map = transition_map_;
    place = transition_place_;
    transition_requested_ = false;
}

void Level::CalculateScrolling() {
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
}

void Level::Load() {
    LEVEL_EVENTS["intro"] = new Intro();
}
