#include "map_object.hpp"

MapObject::MapObject(Tileset *tileset, int gid, float x, float y, float width, float height) :
        super(x, y, width, height, 1),
        tileset_(tileset),
        gid_(gid-1)
{}

void MapObject::Render() const {
    tileset_->bind();
    tileset_->RenderTile(position_.x, position_.y, gid_);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Sprite *MapObject::CurrentSprite(vec2f &sprite_position) const {
    return nullptr;
}

Sprite *MapObject::CurrentSprite() const {
    return nullptr;
}
