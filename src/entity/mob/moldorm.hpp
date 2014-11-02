#include "../mob.hpp"
#include "../../graphic/spritesheet.hpp"
#include "../object.hpp"

#pragma once

class Moldorm : public Mob {
public:
    typedef Mob super;

    static SpriteSheet* SPRITESHEET;
    static SpriteSet* HEAD;
    static Sprite* MIDDLE1;
    static Sprite* MIDDLE2;
    static Sprite* MIDDLE3;
    static Sprite* TAIL;
    static void Load();

    Moldorm(float x, float y);

    bool CanCollideWith(Rectangle* rectangle) const;
    bool CollidesWith(Rectangle const * rectangle) const;

    void Update(double delta);
    void Draw() const;

private:
    class MoldormNode : public Rectangle {
    public:
        typedef Rectangle super;
        MoldormNode(float x, float y, float width, float height, const vec2f& offset, float max_distance,
                Sprite* sprite, Moldorm* head, Rectangle* parent);

        void Update(double delta);
        void Draw() const;

    private:
        Sprite* sprite_;
        Moldorm* head_;
        Rectangle* parent_;
        vec2f offset_;
        float max_distance_;
    };

    Rectangle hitbox_;
    std::vector<MoldormNode*> nodes_;
    int rotation;
};
