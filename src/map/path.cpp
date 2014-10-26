#include "path.hpp"

const int Path::RESOLUTION = 1;

Path::Path(Mob* from, Entity* to) :
        from(from),
        to(to),
        rectangle(new Rectangle(0, 0, from->width(), from->height())),
        ready(false),
        calculating(false),
        accum(0),
        found(false)
{
    destination = vec2i((int)(to->x() / RESOLUTION), (int)(to->y() / RESOLUTION));
    vec2i origin = vec2i((int)(from->x() / RESOLUTION), (int)(from->y() / RESOLUTION));

    Path::Node* start = new Path::Node(origin, destination, 0, 0);
    pending.insert(start);
}

Path::~Path() {
    for(int i = 0; i < nodes.size(); ++i)
        delete nodes[i];

    delete rectangle;
}

bool Path::Update(double delta) {
    accum += delta;

    if(found) {
        if(accum < 0.1)
            return true;

        Node* last = nodes[0];

        rectangle->set_position(last->x * RESOLUTION, last->y * RESOLUTION);
        return rectangle->CollidesWith(to);
    }

    return accum < 2;
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
