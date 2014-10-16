#include <list>
#include <vector>
#include "../entity.hpp"

#pragma once

class Quadtree {
public:
    Quadtree(int level, Rectangle bounds);
    ~Quadtree();

    bool IsEmpty() const;

    void Clear();
    void Split();
    void Insert(Rectangle *r);
    void Remove(Rectangle *r);
    void Update(Rectangle *r);
    void Retrieve(Rectangle *r, std::vector<Rectangle *> &objects) const;

    // Debugging purposes
    void Render() const;


private:
    static const int MAX_OBJECTS;

    int level_;
    std::list<Rectangle*> objects_;
    Rectangle bounds_;
    Quadtree* children_[4];

    int child_for(Rectangle* r) const;
};
