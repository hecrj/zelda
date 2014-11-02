#pragma once

#include "../../math/vec2.hpp"
#include "../callback_effect.hpp"
#include <vector>
#include <string>

class Dialog : public CallbackEffect {
public:
    typedef CallbackEffect super;
    struct Message {
        std::string line1;
        std::string line2;
        float speed;
        int length;

        Message(const std::string& line1, const std::string& line2, float speed);
    };

    Dialog(const std::vector<Message*> messages, const CallbackEffect::Callback& callback);

    bool IsFinished() const;

    void Tick(double delta);
    void Render() const;

private:
    std::vector<Message*> messages_;
    int current_message_;
    float elapsed_time_;
};
