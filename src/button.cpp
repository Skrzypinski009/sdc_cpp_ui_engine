#include "button.h"

#include <iostream>

#include "signal_manager.h"

Button::Button() 
    : InputObject({0,0}, {100,100}, ObjectType::BUTTON) {}

Button::Button(const Vec2 position_, const Vec2 size_) 
    : InputObject(position_, size_, ObjectType::BUTTON) {}

Button::Button(const Button &other) 
    : InputObject(other.getPosition(), other.getSize(), other.type) {
    // setMinSize(other.getMinSize());
}

// void Button::setPressed(const bool pressed_){
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

void Button::onLoopUpdate(float delta) {
    Object::onLoopUpdate(delta);
    if(just_pressed)
            just_pressed = false;
}

void Button::draw(SDL_Renderer* renderer){
    if (style == nullptr) return;

    Veci2 pos = getGlobalPosition();
    SDL_Rect rect = {pos.x, pos.y, (int)size.x, (int)size.y};
    if (isPressed())
    {
        style->drawBackground(renderer, "background_color:pressed", &rect);
        style->drawBorder(renderer, "border_color:pressed", &rect);
        return;
    }
    style->drawBackground(renderer, "background_color", &rect);
    style->drawBorder(renderer, "border_color", &rect);
}