#include "input_object.h"


InputObject::InputObject(const Vec2 position_, const Vec2 size_, const int type_)
    :Object(position_, size_, type_) {
        setEnabled();
        setReleased();
        setFocused(false);
    }


void InputObject::setDisabled() {
    disabled = true;
    emitSignal("disabled");
}

void InputObject::setEnabled() {
    disabled = false;
    emitSignal("enabled");
}

bool InputObject::isDisabled() {
    return disabled;
}

void InputObject::setFocused(bool focused_) {
    focused = focused_;
    if (focused)
        emitSignal("focus_on");
    else
        emitSignal("focus_off");
}

bool InputObject::isFocused() {
    return focused;
}


void InputObject::setPressed() {
    pressed = true;
    emitSignal("pressed");
}

void InputObject::setReleased() {
    pressed = false;
    emitSignal("released");
}

bool InputObject::isPressed() {
    return pressed;
}