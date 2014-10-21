#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <iostream>
#include "sprite.hpp"
#include "../game.hpp"


Sprite::Sprite(GLuint texture, int width, int height, float tex_x, float tex_y, float tex_width, float tex_height) :
    Sprite(texture, width, height, tex_x, tex_y, tex_width, tex_height, 0)
{
    hitmap_ = new Hitmap(width, height);

    // Render the sprite and read the pixels
    // The pixels that are not transparent in the sprite are considered as a hit pixel
    GLuint fbo = Game::FramebufferAux();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    Render(vec2f(0, 0));

    GLubyte pixels[height][width][4];

    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glReadPixels(0, 480-height, width, height, GL_RGBA, GL_UNSIGNED_BYTE, (void*)pixels);

    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            hitmap_->map_[i][j] = pixels[height-i-1][j][3] != 0;
        }
    }

    hitmap_->Print();

    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

Sprite::Sprite(GLuint texture, int width, int height, float tex_x, float tex_y, float tex_width, float tex_height,
        Hitmap* hitmap) :
        texture_(texture),
        width_(width),
        height_(height),
        tex_x_(tex_x),
        tex_y_(tex_y),
        tex_width_(tex_width),
        tex_height_(tex_height),
        hitmap_(hitmap)
{

}

void Sprite::Render(const vec2f& position) const {
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

float Sprite::width() const {
    return width_;
}

float Sprite::height() const {
    return height_;
}

Hitmap* Sprite::hitmap() const {
    return hitmap_;
}
