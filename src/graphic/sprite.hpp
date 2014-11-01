#include <GL/gl.h>
#include "../math/vec2.hpp"
#include "pixelmap.hpp"

#pragma once

class Sprite {
public:
    Sprite(GLuint texture, int width, int height, float tex_x, float tex_y, float tex_width, float tex_height);
    Sprite(GLuint texture, int width, int height, float tex_x, float tex_y, float tex_width, float tex_height,
            Pixelmap* hitmap);

    float width() const;
    float height() const;
    Pixelmap* hit_map() const;
    Pixelmap* damage_map() const;

    void Render(const vec2f& position) const;
    void DrawGeom(const vec2f& position) const;

private:
    GLuint texture_;
    int width_;
    int height_;
    float tex_x_;
    float tex_y_;
    float tex_width_;
    float tex_height_;
    Pixelmap* hit_map_;
    Pixelmap* damage_map_;
};
