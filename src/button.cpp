#include "button.h"

#include <iostream>

#include "signal_manager.h"

Button::Button() 
    : Object({0,0}, {100,100}, ObjectType::BUTTON) {}

Button::Button(const Veci2 position_, const Veci2 size_) 
    : Object(position_, size_, ObjectType::BUTTON) {}

Button::Button(const Button &other) 
    : Object(other.getPosition(), other.getSize(), other.type) {
    // setMinSize(other.getMinSize());
}

void Button::setPressed(const bool pressed_){
    pressed = pressed_;
    if(pressed){
        just_pressed = true;
        std::cout<<"button_pressed"<<std::endl;
        SignalManager::emitSignal("button_pressed");
    } else {
        std::cout<<"button_released"<<std::endl;
    }
}

bool Button::isPressed() const {
    return pressed;
}

bool Button::isJustPressed() const {
    return just_pressed;
}

// void Button::setReleased(const bool released_){
//     released = released_;
// }

// bool Button::isReleased() const {
//     return released;
// }

// void Button::setHover(const bool hover_){
//     hover = hover_;
// }

// bool Button::isHover() const {
//     return hover;
// }



bool Button::pressedCheck(const Veci2 click_pos) const {
    Veci2 start_pos = getGlobalPosition();
    Veci2 end_pos = start_pos + size;
    if(
        click_pos.x > start_pos.x && 
        click_pos.y > start_pos.y &&
        click_pos.x < end_pos.x &&
        click_pos.y < end_pos.y
    ){
        return true;
    }
    return false;
}

void Button::onLoopUpdate() {
    if(just_pressed){
        just_pressed_counter = true;
        if(just_pressed && just_pressed_counter){
            just_pressed = false;
            just_pressed_counter = false;
        }
    }
}

void Button::draw(SDL_Renderer* renderer){
    Object::draw(renderer);
}