#include "object.h"

#include <math.h>
#include <map>
#include <vector>

#include "color.h"
#include "veci2.h"
#include "rect_style.h"
#include "log.h"

#include "style_manager.h"
#include "signal_manager.h"

Object::Object(){
    type = ObjectType::OBJECT;
    setPosition(Veci2(0,0));
    // setMinSize(Veci2(0,0));
    setSize(Veci2(0,0));
    setParent(nullptr);
    setRectStyle(nullptr);
    setAlignH(ALIGN_LEFT);
    setAlignV(ALIGN_TOP);
}

Object::Object(const Veci2 position_, const Veci2 size_, const int type_){
    type = type_;
    setPosition(position_);
    // setMinSize(Veci2(0,0));
    setSize(size_);
    setParent(nullptr);
    setRectStyle(nullptr);
    setAlignH(ALIGN_LEFT);
    setAlignV(ALIGN_TOP);
}

Object::Object(const Object &other){
    type = other.type;
    setPosition(other.getPosition());
    setSize(other.getSize());
    // setMinSize(other.getMinSize());
    setParent(nullptr);
    setRectStyle(other.rect_style);
    setAlignH(other.align_h);
    setAlignV(other.align_v);
}

std::string Object::strType() const {
    std::string names[] = {
        "OBJECT",
        "CONTAINER",
        "ORDER_CONTAINER",
        "RECTANGLE",
        "LABEL",
        "BUTTON"
    };
    return names[type];
}

void Object::setPosition(const Veci2 position_){
    position = position_;
}

void Object::setSize(const Veci2 size_){
    // size.x = std::max(size_.x, min_size.x);
    // size.y = std::max(size_.y, min_size.y);
    size = size_;
}

// void Object::setMinSize(const Veci2 min_size_){
//     min_size = min_size_;
//     size.x = std::max(size.x, min_size.x);
//     size.y = std::max(size.y, min_size.y);
// }

void Object::setExpand(const bool expand_){
    expand = expand_;
}

void Object::setFill(const bool fill_){
    fill = fill_;
}

void Object::setAlignH(const int align_h_){
    align_h = align_h_;
}

void Object::setAlignV(const int align_v_){
    align_v = align_v_;
}

void Object::setParent(Object* object_){
    parent = object_;
}

void Object::setRectStyle(RectStyle *rect_style_){
    rect_style = rect_style_;
}

void Object::setStyle(const std::string key){
    rect_style = StyleManager::getStyle(key);
}

void Object::setName(const std::string name_){
    if (name != "") {
        Log::error("Object already has it's name! You canno't change it");
        return;
    }
    if (Object::hasObject(name_)) {
        Log::error("Object with that name already exist!");
        return;
    }
    name = name_;
    addObject(name, this);
}
std::string Object::getName() const {
    return name;
}

// getters

Veci2 Object::getPosition() const {
    return position;
}

Veci2 Object::getSize() const {
    return size;
}

// Veci2 Object::getMinSize() const {
//     return min_size;
// }

bool Object::getExpand() const {
    return expand;
}

bool Object::getFill() const {
    return fill;
}

std::size_t Object::getAlignH() const {
    return align_h;
}

std::size_t Object::getAlignV() const {
    return align_v;
}

Object* Object::getParent() const {
    return parent;
}

RectStyle* Object::getRectStyle() const {
    return rect_style;
}

// -----

void Object::clearParent(){
    this->parent = nullptr;
}

Veci2 Object::getGlobalPosition() const {
    if(parent){
        return getPosition() + parent->getGlobalPosition();
    }
    return getPosition();
}


SDL_Rect Object::getClipRect() const {
    if(!parent)
        return {getPosition().x, getPosition().y, getSize().x, getSize().y};
    SDL_Rect clip_rect;
    clip_rect.x = std::max(getGlobalPosition().x, parent->getGlobalPosition().x);
    clip_rect.y = std::max(getGlobalPosition().y, parent->getGlobalPosition().y);
    clip_rect.w = std::min(getGlobalPosition().x + getSize().x, parent->getGlobalPosition().x + parent->getSize().x) - clip_rect.x;
    clip_rect.h = std::min(getGlobalPosition().y + getSize().y, parent->getGlobalPosition().y + parent->getSize().y) - clip_rect.y;
    if(clip_rect.w < 0 || clip_rect.h < 0)
        return {0,0,0,0};
    return clip_rect;
}

void Object::draw(SDL_Renderer *renderer){
    // std::cout<<"drawing object\n";
    if(getRectStyle())
        getRectStyle()->draw(renderer, getGlobalPosition(), getSize());
}

void Object::emitSignal(std::string signal_name)
{
    SignalManager::emitSignal(this, signal_name);
}

void Object::connect(std::string signal_name, void (*func)(Object*))
{
    SignalManager::connect(this, signal_name, func);
}


// Old Object Manager
    std::map<std::string, Object*> Object::objects = {};

    void Object::addObject(std::string name, Object* object){
        if (Object::hasObject(name)) {
            Log::error("Object Manager can't register object with that name!");
            return;
        }
        Object::objects[name] = object;
    }

    Object* Object::getObject(std::string name){
        if (!Object::hasObject(name)) {
            Log::error("Object Manager can't return object with that name!");
            return NULL;
        }
        return Object::objects.at(name);
    }

    bool Object::hasObject(std::string name){
        if (Object::objects.find(name) == Object::objects.end())
            return false;
        return true;
    }
// --- Object manager