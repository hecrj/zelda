#pragma once

#include "../effect.hpp"
#include "../../math/vec2.hpp"
#include <vector>
#include <string>

class Dialog : public Effect {
public:
    struct Message {
        std::string line1;
        std::string line2;
        float speed;
        int length;

        Message(const std::string& line1, const std::string& line2, float speed);
    };

    Dialog(const std::vector<Message*> messages);

    bool IsFinished() const;

    void Tick(double delta);
    void Render() const;

private:
    std::vector<Message*> messages_;
    int current_message_;
    float elapsed_time_;
};
