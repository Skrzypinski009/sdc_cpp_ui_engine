#pragma once

#include "object.h"
#include "container.h"
#include "veci2.h"

class FitContainer: public Container{
public:
    bool horisontal;

    FitContainer();
    FitContainer(const Veci2 position_, const Veci2 size_, const int type_=ObjectType::FIT_CONTAINER);

    void setHorisontal(const bool horisontal_);

    void addObject(Object *obj);
    void removeAt(const size_t idx);
    void updateObjectsHPosition();
    void updateObjectsVPosition();
    void updateObjectsPosition() override;
}; 
