#include "intro.hpp"
#include "../../graphic/effect/dialog.hpp"

namespace IntroPrivate {
    std::vector<Dialog::Message*> messages = {
            new Dialog::Message(
                    "A long, long time ago...",
                    "Hyrule was saved by a hero...",
                    20
            )
    };

    void start(Level* level) {
        level->ChangeEffect(new Dialog(messages));
    }
};

Intro::Intro() {
    Register("start", IntroPrivate::start);
}
