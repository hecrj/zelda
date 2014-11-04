#pragma once

#include "../entity/mob.hpp"
#include <set>

class Path {
public:
    static const int RESOLUTION;

    struct Node {
        Node* parent;
        unsigned int x;
        unsigned int y;
        unsigned int g_cost;
        unsigned int h_cost;
        unsigned int cost;
        bool closed;

        Node(const vec2i& position, const vec2i& destination, unsigned int g_cost, Node* parent);

        unsigned int HeuristicCost(const vec2i& destination) const;

        void UpdateGCost(unsigned int g_cost);

        struct SortByCostAsc {
            bool operator() (Node* n1, Node* n2) const;
        };
    };

    Mob* from;
    Entity* to;
    RectangleShape* rectangle;
    bool ready;
    bool calculating;
    bool found;
    std::set<Path::Node*, Path::Node::SortByCostAsc> pending;
    std::vector<vec2i> nodes;
    vec2i origin;
    vec2i destination;
    float rest;

    Path(Mob* from, Entity* to);
    ~Path();

    bool Update(double delta);
    void Render() const;

private:
    float accum;
};
