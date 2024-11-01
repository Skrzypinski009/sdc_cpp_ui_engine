#pragma once

#include "object.h"
#include "container.h"
#include "veci2.h"

class OrderContainer: public Container{
public:
    bool horisontal;

    OrderContainer();
    OrderContainer(const Vec2 position_, const Vec2 size_, const int type_=ObjectType::ORDER_CONTAINER);

    void setHorisontal(const bool horisontal_);

    void addObject(Object *obj);
    void removeAt(const std::size_t idx);
    void updateObjectsHPosition();
    void updateObjectsVPosition();
    void updateObjectsPosition() override;
}; 
