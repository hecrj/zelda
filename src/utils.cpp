#ifdef _WIN32
#include <Windows.h>
#endif
#include <SFML/System.hpp>
#include <SOIL.h>
#include <sstream>
#include <iostream>
#include "utils.hpp"
#include "game.hpp"

double CurrentTime() {
    return sf::Clock::getCurrentTime();
}

GLuint LoadTexture(const char* file) {
    std::stringstream resource_path;
    resource_path << "res/" << file;

    std::cout << "Loading texture: " << resource_path.str() << std::endl;

    GLuint texture = SOIL_load_OGL_texture(resource_path.str().c_str(),
            SOIL_LOAD_RGBA,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MULTIPLY_ALPHA);

    if(0 == texture) {
        std::stringstream error;
        error << "SOIL loading error: " << SOIL_last_result() << std::endl;
        error << "Unable to load: ";

        Game::Error(error.str().c_str(), file);
    }

    // This avoids blurry sprites (we like retro style)
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}
