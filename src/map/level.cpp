#include "level.hpp"

Level::Level(const char *map) : super(map) {

}

void Level::Update(double delta) {
    // TODO: Remove dead entities

    for(Entity* entity : entities) {
        entity->Update(delta);
    }
}

void Level::Render() {
    // TODO: Render above layers after entities
    super::Render();

    for(Entity* entity : entities) {
        entity->Render();
    }
}

void Level::AddEntity(Entity* entity) {
    entities.push_back(entity);
}
