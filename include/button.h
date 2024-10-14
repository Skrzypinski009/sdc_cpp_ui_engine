#pragma once

#include "object.h"
#include "veci2.h"

class Button: public Object{
    bool pressed;
    bool just_pressed;
    bool just_pressed_counter;

public:
    Button(const Button &other);
    Button();
    Button(const Veci2 position_, const Veci2 size_);

    void setPressed(const bool pressed_);
    bool isPressed() const;
    bool isJustPressed() const;

    bool pressedCheck(const Veci2 click_pos) const;
    void onLoopUpdate() override;
    void draw(SDL_Renderer* renderer) override;
};

