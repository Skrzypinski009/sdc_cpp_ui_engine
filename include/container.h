#pragma once

#include "object.h"
#include <vector>
#include "veci2.h"

class Container: public Object{
public:
    std::vector<Object*> objects;
    Container();
    Container(const Veci2 position_, const Veci2 size_, const int type_ = ObjectType::CONTAINER);
    
    void setSize(const Veci2 size_) override;
    virtual void updateObjectsPosition();
    void draw(SDL_Renderer *renderer) override;
    static int findObject(std::vector<Object*> objects_, Object* obj);
    void addObject(Object* obj);
    void removeAt(const size_t idx);
};
