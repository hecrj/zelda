#include "door.hpp"
#include "../../audio/sound.hpp"

sf::SoundBuffer* Door::OPEN_SOUND;

void Door::Load() {
    OPEN_SOUND = Sound::Buffer("door/open.wav");
}

// TODO: Implement doors
Door::Door() : super(0, 0, 0) {

}
