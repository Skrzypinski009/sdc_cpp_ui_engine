#pragma once

#include <vector>

#include "object.h"
#include "veci2.h"

class Container: public Object{
public:
    std::vector<Object*> objects;
    bool clip;

    Container();
    Container(const Veci2 position_, const Veci2 size_, const int type_ = ObjectType::CONTAINER);
    
    void setClip(bool clip_);
    bool getClip() const;

    void setSize(const Veci2 size_) override;
    virtual void updateObjectsPosition();
    void draw(SDL_Renderer *renderer) override;
    static int findObject(std::vector<Object*> objects_, Object* obj);
    void addObject(Object* obj);
    void removeAt(const std::size_t idx);
    void onLoopUpdate(float delta) override;
    void update() override;
};
