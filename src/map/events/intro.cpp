#include "intro.hpp"
#include "../../graphic/effect/dialog.hpp"

namespace IntroPrivate {
    Dialog::Message* dialog(const std::string& line1, const std::string& line2) {
        return new Dialog::Message(line1, line2, 20);
    }

    std::vector<Dialog::Message*> messages = {
            dialog(
                    "A long, long time ago...",
                    "Hyrule was saved by a hero..."
            ),
            dialog(
                    "But now...",
                    "An evil power has returned..."
            )
    };

    void start(Level* level) {
        level->ChangeEffect(new Dialog(messages, [level]{
            level->Transition("bigger", "start");
        }));
    }
};

Intro::Intro() {
    Register("start", IntroPrivate::start);
}
