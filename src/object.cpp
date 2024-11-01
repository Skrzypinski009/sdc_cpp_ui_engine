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
    setPosition(Vec2(0,0));
    // setMinSize(Vec2(0,0));
    setSize(Vec2(0,0));
    setParent(nullptr);
    setRectStyle(nullptr);
    setAlignH(ALIGN_LEFT);
    setAlignV(ALIGN_TOP);
    loop_function = nullptr;
}

Object::Object(const Vec2 position_, const Vec2 size_, const int type_){
    type = type_;
    setPosition(position_);
    // setMinSize(Vec2(0,0));
    setSize(size_);
    setParent(nullptr);
    setRectStyle(nullptr);
    setAlignH(ALIGN_LEFT);
    setAlignV(ALIGN_TOP);
    loop_function = nullptr;
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
    loop_function = nullptr;
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

void Object::setPosition(const Vec2 position_){
    position = position_;
}

void Object::setSize(const Vec2 size_){
    // size.x = std::max(size_.x, min_size.x);
    // size.y = std::max(size_.y, min_size.y);
    size = size_;
    updateParent();
}

// void Object::setMinSize(const Vec2 min_size_){
//     min_size = min_size_;
//     size.x = std::max(size.x, min_size.x);
//     size.y = std::max(size.y, min_size.y);
// }

void Object::setExpand(const bool expand_){
    expand = expand_;
    updateParent();
}

void Object::setFill(const bool fill_){
    fill = fill_;
    updateParent();
}

void Object::setAlignH(const int align_h_){
    align_h = align_h_;
    updateParent();
}

void Object::setAlignV(const int align_v_){
    align_v = align_v_;
    updateParent();
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

void Object::setLoopFunction(void (*loop_func)(Object*, float)){
    Log::info((strType() + " object loop function is set").c_str());
    loop_function = loop_func;
}

// getters

Vec2 Object::getPosition() const {
    return position;
}

Vec2 Object::getSize() const {
    return size;
}

// Vec2 Object::getMinSize() const {
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

Vec2 Object::getGlobalPosition() const {
    if(parent){
        return getPosition() + parent->getGlobalPosition();
    }
    return getPosition();
}


SDL_Rect Object::getClipRect() const {
    if(!parent)
        return {(int)getPosition().x, (int)getPosition().y, (int)getSize().x, (int)getSize().y};
    SDL_Rect clip_rect;
    clip_rect.x = (int)std::max(getGlobalPosition().x, parent->getGlobalPosition().x);
    clip_rect.y = (int)std::max(getGlobalPosition().y, parent->getGlobalPosition().y);
    clip_rect.w = (int)std::min(getGlobalPosition().x + getSize().x, parent->getGlobalPosition().x + parent->getSize().x) - clip_rect.x;
    clip_rect.h = (int)std::min(getGlobalPosition().y + getSize().y, parent->getGlobalPosition().y + parent->getSize().y) - clip_rect.y;
    if(clip_rect.w < 0 || clip_rect.h < 0)
        return {0,0,0,0};
    return clip_rect;
}

void Object::draw(SDL_Renderer *renderer){
    // std::cout<<"drawing object\n";
    if(getRectStyle())
        getRectStyle()->draw(renderer, Veci2(getGlobalPosition()), Veci2(getSize()));
}

void Object::onLoopUpdate(float delta) {
    if(loop_function == nullptr) return;
    loop_function(this, delta);
}

void Object::update() {}

void Object::updateParent()
{
    if (parent == nullptr) return;
    parent->update();
}

// ------- Methods for Signal Manger

    void Object::emitSignal(std::string signal_name)
    {
        SignalManager::emitSignal(this, signal_name);
    }

    void Object::connect(std::string signal_name, void (*func)(Object*))
    {
        SignalManager::connect(this, signal_name, func);
    }
// ----------------------------

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