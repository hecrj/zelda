#include "path.hpp"
#include "level.hpp"

Path::Path(Mob* from, Entity* to) :
        from(from),
        to(to),
        r(0, 0, from->width(), from->height()),
        ready(false),
        calculating(false),
        accum(0)
{}

Path::~Path() {
    for(int i = 0; i < nodes.size(); ++i)
        delete nodes[i];
}

bool Path::Update(double delta) {
    accum += delta;

    if(accum < 1)
        return true;

    if(nodes.size() == 0)
        return accum < 2;

    Node* last = nodes.back();

    r.set_position(last->x * Level::PATH_RESOLUTION, last->y * Level::PATH_RESOLUTION);
    return r.CollidesWith(to);
}

Path::Node::Node(const vec2i& position, const vec2i& destination, unsigned int g_cost, Path::Node* parent) :
        x((unsigned int) position.x),
        y((unsigned int) position.y),
        g_cost(g_cost),
        parent(parent),
        closed(false)
{
    h_cost = HeuristicCost(destination);
    cost = g_cost + h_cost;
}

bool Path::Node::SortByCostAsc::operator()(Path::Node* n1, Path::Node* n2) const {
    return n1->cost < n2->cost or (n1->cost == n2->cost and n1->x < n2->x) or (n1->x == n2->x and n1->y < n2->y);
}

unsigned int Path::Node::HeuristicCost(const vec2i& destination) const {
    return (unsigned int)(abs(destination.x - x) + abs(destination.y - y));
}

void Path::Node::UpdateGCost(unsigned int g_cost) {
    this->g_cost = g_cost;
    cost = g_cost + h_cost;
}
