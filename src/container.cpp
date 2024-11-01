#include "container.h"

#include "color.h"
#include "object.h"
#include "veci2.h"


Container::Container()
    : Object({0,0}, {100, 100}, ObjectType::CONTAINER) {}

Container::Container(const Veci2 position_, const Veci2 size_, const int type_)
    : Object(position_, size_, type_) {}


void Container::setClip(bool clip_) {
    clip = clip_;
}

bool Container::getClip() const {
    return clip;
}

void Container::setSize(const Veci2 size_){
    Object::setSize(size_);
    updateObjectsPosition();
}

void Container::updateObjectsPosition(){
    for(Object* object: objects)
        if(object->fill){
            object->setPosition({0,0});
            object->setSize(size);
        }
}

void Container::draw(SDL_Renderer *renderer){
    if(getRectStyle())
        getRectStyle()->draw(renderer, getGlobalPosition(), getSize());

    SDL_Rect clip_rect = getClipRect();

    for(Object* obj: objects){
        if (clip)
            SDL_RenderSetClipRect(renderer, &clip_rect);
        obj->draw(renderer);
    }
    SDL_RenderSetClipRect(renderer, NULL);
}

int Container::findObject(std::vector<Object*> objects, Object* object){
    for(std::size_t i=0; i<objects.size(); i++){
        if(object == objects.at(i)){
            return i;
        }
    }
    return -1;
}

void Container::addObject(Object* obj){
    if(findObject(objects, obj) != -1)
        throw "Adding Object to Container, multiple times";
    objects.push_back(obj);
    obj->setParent(this);
    updateObjectsPosition();
}

void Container::removeAt(const std::size_t idx){
    objects[idx]->clearParent();
    objects.erase(objects.begin() + idx);
}

void Container::onLoopUpdate(float delta)
{
    for (Object* object : objects)
        object->onLoopUpdate(delta);
    Object::onLoopUpdate(delta);
}

void Container::update(){
    updateObjectsPosition();
}
