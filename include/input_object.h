#pragma once

#include "object.h"

class InputObject: public Object {
    bool disabled;
    bool focused;
    bool pressed;

public:    
    InputObject(const Vec2 position_, const Vec2 size_, const int type_);

    void setDisabled();
    void setEnabled();
    bool isDisabled();

    void setFocused(bool focused_);
    bool isFocused();

    void setPressed();
    void setReleased();
    bool isPressed();
};