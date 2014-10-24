#include <iostream>
#include "level.hpp"
#include "../debug.hpp"
#include "../entity/map_object.hpp"
#include "../game.hpp"

const int Level::FOLLOW_MARGIN = 200;

Level::Level(const char *map) : super(map), position_(vec2f(0, 0))
{
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
    for(Entity* entity : entities_) {
        if(entity->IsMob()) {
            dynamic_collidables_->Remove(entity);

            entity->Update(delta);

            if (entity->IsAlive()) {
                dynamic_collidables_->Insert(entity);
                temp_entities_.push_back(entity);
            } else if (entity != player_) {
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
    entities_.clear();
    entities_.insert(temp_entities_.begin(), temp_entities_.end());
    temp_entities_.clear();
}

void Level::Render() {
    // Recalculate scrolling
    const vec2f& player_position = player_->position();
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

void Level::set_player(Entity* player) {
    player_ = player;
    AddEntity(player);
}

void Level::CollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const {
    super::CollidablesFor(rectangle, collidables);
    dynamic_collidables_->Retrieve(rectangle, collidables);
}

void Level::DynamicCollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const {
    dynamic_collidables_->Retrieve(rectangle, collidables);
}
