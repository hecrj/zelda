#include "sprite.hpp"

Sprite::Sprite(GLuint texture, int width, int height, float tex_x, float tex_y, float tex_width, float tex_height) :
    texture_(texture),
    width_(width),
    height_(height),
    tex_x_(tex_x),
    tex_y_(tex_y),
    tex_width_(tex_width),
    tex_height_(tex_height)
{}

void Sprite::Render(vec2f position) const {
    glBindTexture(GL_TEXTURE_2D, texture_);
    glBegin(GL_QUADS);

    glTexCoord2f(tex_x_, tex_y_);
    glVertex2f(position.x, position.y);

    glTexCoord2f(tex_x_ + tex_width_, tex_y_);
    glVertex2f(position.x + width_, position.y);

    glTexCoord2f(tex_x_ + tex_width_, tex_y_ + tex_height_);
    glVertex2f(position.x + width_, position.y + height_);

    glTexCoord2f(tex_x_, tex_y_ + tex_height_);
    glVertex2f(position.x, position.y + height_);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}
