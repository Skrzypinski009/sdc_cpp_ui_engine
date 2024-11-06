#pragma once

#include "input_object.h"
#include "veci2.h"

class Button: public InputObject{
    bool just_pressed;
public:
    Button(const Button &other);
    Button();
    Button(const Vec2 position_, const Vec2 size_);

    void onLoopUpdate(float delta) override;
    void draw(SDL_Renderer* renderer) override;
};

