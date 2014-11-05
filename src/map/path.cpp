#include "path.hpp"

const int Path::RESOLUTION = 4;

Path::Path(Mob* from, Entity* to) :
        from(from),
        to(to),
        rectangle(new RectangleShape(0, 0, from->width(), from->height())),
        ready(false),
        calculating(false),
        found(false),
        accum(0),
        rest(0)
{
    origin = vec2i((int)(from->x() / RESOLUTION), (int)(from->y() / RESOLUTION));
    destination = vec2i((int)(to->x() / RESOLUTION), (int)(to->y() / RESOLUTION));
}

Path::~Path() {
    delete rectangle;
}

bool Path::Update(double delta) {
    accum += delta;

    if(found) {
        if(accum < 0.2)
            return true;

        if(accum > 1)
            return false;

        const vec2i& last = nodes[0];

        rectangle->set_position(last.x * RESOLUTION, last.y * RESOLUTION);
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
    return n1->cost < n2->cost || n1->cost == n2->cost && (n1->h_cost < n2->h_cost ||
            n1->h_cost == n2->h_cost && (n1->x < n2->x || n1->x == n2->x && n1->y < n2->y));
}

unsigned int Path::Node::HeuristicCost(const vec2i& destination) const {
    // Using Manhattan distance with diagonal movement it is not admissible
    // But we get more natural paths this way, despite being longer
	return (unsigned int)(abs((int)(destination.x - x)) + abs((int)(destination.y - y)));
}

void Path::Node::UpdateGCost(unsigned int g_cost) {
    this->g_cost = g_cost;
    cost = g_cost + h_cost;
}

void Path::Render() const {
    if(ready) {
        for(const vec2i node : nodes) {
            RectangleShape r(node.x * RESOLUTION, node.y * RESOLUTION, RESOLUTION, RESOLUTION);
            r.DrawBox(1, 1, 1);
        }
    }
}
