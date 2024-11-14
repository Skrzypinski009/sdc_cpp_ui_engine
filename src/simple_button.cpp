#include "simple_button.h"

#include <iostream>

#include "signal_manager.h"
#include "log.h"

SimpleButton::SimpleButton() 
    : InputObject({0,0}, {100,100}, ObjectType::BUTTON) {}

SimpleButton::SimpleButton(const Vec2 position_, const Vec2 size_) 
    : InputObject(position_, size_, ObjectType::BUTTON) {}

SimpleButton::SimpleButton(const SimpleButton &other) 
    : InputObject(other.getPosition(), other.getSize(), other.type) {
    // setMinSize(other.getMinSize());
}

// void SimpleButton::setPressed(const bool pressed_){
//     pressed = pressed_;
//     if(pressed){
//         just_pressed = true;
//         std::cout<<"button_pressed"<<std::endl;
//         emitSignal("button_pressed");
//     } else {
//         std::cout<<"button_released"<<std::endl;
//         emitSignal("button_released");
//     }
// }

void SimpleButton::onLoopUpdate(float delta) {
    Object::onLoopUpdate(delta);
    if(just_pressed)
            just_pressed = false;
}

void SimpleButton::draw(SDL_Renderer* renderer){
    if (style == nullptr) return;

    Veci2 pos = getGlobalPosition();
    SDL_Rect rect = {pos.x, pos.y, (int)size.x, (int)size.y};
    if (isPressed())
    {
        style->drawRect(renderer, &rect, "pressed");
        return;
    }
    style->drawRect(renderer, &rect);
}