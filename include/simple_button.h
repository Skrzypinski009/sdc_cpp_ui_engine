#pragma once

#include "input_object.h"
#include "veci2.h"

class SimpleButton: public InputObject{
    bool just_pressed;
public:
    SimpleButton(const SimpleButton &other);
    SimpleButton();
    SimpleButton(const Vec2 position_, const Vec2 size_);

    void onLoopUpdate(float delta) override;
    void draw(SDL_Renderer* renderer) override;
};

