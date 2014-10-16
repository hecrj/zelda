#include <iostream>
#include "quadtree.hpp"

const int Quadtree::MAX_OBJECTS = 10;

Quadtree::Quadtree(int level, Rectangle bounds) :
        level_(level),
        bounds_(bounds)
{
    std::cout << "Quadtree" << std::endl;
}

Quadtree::~Quadtree() {
    Clear();
}

void Quadtree::Clear() {
    objects_.clear();

    for(int i = 0; i < 4; ++i) {
        if(children_[i]) {
            delete children_[i];
            children_[i] = 0;
        }
    }
}

void Quadtree::Split() {
    float sub_width = bounds_.width() / 2.0f;
    float sub_height = bounds_.height() / 2.0f;
    vec2f position = bounds_.position();

    children_[0] = new Quadtree(level_+1, Rectangle(position.x + sub_width, position.y, sub_width, sub_height));
    children_[1] = new Quadtree(level_+1, Rectangle(position.x, position.y, sub_width, sub_height));
    children_[2] = new Quadtree(level_+1, Rectangle(position.x, position.y + sub_height, sub_width, sub_height));
    children_[3] = new Quadtree(level_+1, Rectangle(position.x + sub_width, position.y + sub_height, sub_width,
            sub_height));
}

int Quadtree::child_for(Rectangle *r) const {
    int index = -1;
    vec2f center = bounds_.center();
    vec2f rposition = r->position();

    bool top_quadrant = (rposition.y < center.y && rposition.y + r->height() < center.y);
    bool bottom_quadrant = (rposition.y > center.y);

    if(rposition.x < center.x &&  rposition.x + r->width() < center.x) {
        if(top_quadrant)
            index = 0;
        else if(bottom_quadrant)
            index = 2;
    } else if(rposition.x > center.x) {
        if(top_quadrant)
            index = 1;
        else if(bottom_quadrant)
            index = 3;
    }

    return index;
}

void Quadtree::Insert(Rectangle *r) {
    if(children_[0]) {
        int child = child_for(r);

        if(child != -1) {
            children_[child]->Insert(r);
            return;
        }
    }

    objects_.push_back(r);

    if(objects_.size() > MAX_OBJECTS) {
        if(!children_[0]) {
            Split();
        }

        std::list<Rectangle*>::iterator it = objects_.begin();
        while(it != objects_.end()) {
            int child = child_for(*it);

            if(child != -1) {
                children_[child]->Insert(*it);
                objects_.erase(it++);
            } else {
                ++it;
            }
        }
    }
}

void Quadtree::Remove(Rectangle *r) {
    if(children_[0]) {
        int child = child_for(r);

        if(child != -1) {
            children_[child]->Remove(r);

            if(children_[0]->IsEmpty() &&
                    children_[1]->IsEmpty() &&
                    children_[2]->IsEmpty() &&
                    children_[3]->IsEmpty()) {
                Clear();
            }
        } else {
            objects_.remove(r);
        }
    } else {
        objects_.remove(r);
    }
}

void Quadtree::Update(Rectangle *r) {
    Remove(r);
    Insert(r);
}

void Quadtree::Retrieve(Rectangle *r, std::vector<Rectangle *> &objects) const {
    if(children_[0]) {
        int child = child_for(r);

        if (child != -1) {
            children_[child]->Retrieve(r, objects);
        }
    }

    objects.insert(objects.end(), objects_.begin(), objects_.end());
}

bool Quadtree::IsEmpty() const {
    return (!children_[0]) && objects_.size() == 0;
}
