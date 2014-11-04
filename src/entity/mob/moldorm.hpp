#include "../mob.hpp"
#include "../../graphic/spritesheet.hpp"
#include "../object.hpp"

#pragma once

class Moldorm : public Mob {
    class MoldormNode : public RectangleShape {
    public:
        typedef RectangleShape super;
        MoldormNode(float x, float y, float width, float height, const vec2f& offset, float max_distance,
                Sprite* sprite, Moldorm* head, RectangleShape* parent);

        void Update(double delta);
        void Draw() const;

    private:
        Sprite* sprite_;
        Moldorm* head_;
        RectangleShape* parent_;
        vec2f offset_;
        float max_distance_;
    };

    class MoldormHitbox : public Entity {
    public:
        typedef Entity super;
        MoldormHitbox(Moldorm* moldorm);

        bool CanCollideWith(RectangleShape* rectangle) const;
        bool HandleCollisionWith(Mob* mob);
        bool CollidesWith(RectangleShape const * rectangle) const;

        Sprite* CurrentSprite(vec2f& position) const;
        Sprite* CurrentSprite() const;

        void Damage(Entity* from, int amount);

    private:
        Moldorm* moldorm_;
    };

public:
    typedef Mob super;

    static SpriteSheet* SPRITESHEET;
    static SpriteSet* HEAD;
    static Sprite* MIDDLE1;
    static Sprite* MIDDLE2;
    static Sprite* MIDDLE3;
    static Sprite* TAIL;
    static void Load();

    Moldorm(float x, float y, Level* level);
    ~Moldorm();

    bool CanCollideWith(RectangleShape* rectangle) const;
    bool CollidesWith(RectangleShape const * rectangle) const;
    bool HandleCollisionWith(Mob* mob);
    MoldormNode* tail() const;
    vec2f direction() const;

    void Hit();
    void Rotate();

    void Update(double delta);
    void Draw() const;

    void Dead();

private:
    RectangleShape* hitbox_;
    std::vector<MoldormNode*> nodes_;
    MoldormNode* tail_;
    int rotation;
};
