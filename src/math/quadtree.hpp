#pragma once

#include <list>
#include <vector>
#include "../entity.hpp"

class Quadtree {
public:
    Quadtree(int level, RectangleShape bounds);
    ~Quadtree();

    bool IsEmpty() const;

    void Clear();
    void Split();
    void Insert(RectangleShape*r);
    void Remove(RectangleShape*r);
    void Update(RectangleShape*r);
    void Retrieve(RectangleShape*r, std::vector<RectangleShape*> &objects) const;

    // Debugging purposes
    void Render(float r, float g, float b) const;


private:
    static const int MAX_OBJECTS;

    int level_;
    std::list<RectangleShape*> objects_;
    RectangleShape bounds_;
    Quadtree* children_[4];

    int ChildFor(RectangleShape* r) const;
};
