#include "level.hpp"
#include "../debug.hpp"

Level::Level(const char *map) : super(map)
{}

void Level::Update(double delta) {
    // TODO: Remove dead entities

    for(Entity* entity : entities_) {
        entity->Update(delta);

        if(entity->moving())
            collidables_->Update(entity);
    }
}

void Level::Render() {
    super::RenderLayersBelow();

    for(Entity* entity : entities_) {
        entity->Render();
    }

    super::RenderLayersAbove();

    if(Debug::enabled) {
        // Show collidable candidates
        std::vector<Rectangle*> candidates;
        collidables_->Retrieve(player_, candidates);

        for(Rectangle* candidate : candidates)
            candidate->Render(1, 0.5, 0);
    }
}

void Level::AddEntity(Entity* entity) {
    entities_.push_back(entity);
    collidables_->Insert(entity);
}

void Level::set_player(Entity* player) {
    player_ = player;
    AddEntity(player);
}
