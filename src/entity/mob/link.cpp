#include "link.hpp"
#include "action/move.hpp"

Link::Link(Level* level) :
        super(
                "link",
                level,
                vec2f(4.0f, 12.0f),
                vec2f(16.0f, 24.0f),
                new ::Move(this)
        )
{}
