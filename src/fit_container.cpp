#include "fit_container.h"
#include "container.h"
#include "veci2.h"
#include "object.h"

#include "SDL.h"
#include <iostream>

FitContainer::FitContainer()
    : Container({0,0}, {100,100}, ObjectType::FIT_CONTAINER) {}

FitContainer::FitContainer(const Veci2 position_, const Veci2 size_, const int type_)
    : Container(position_, size_, type_) {}

void FitContainer::setHorisontal(const bool horisontal_){
    if(horisontal != horisontal_){
        horisontal = horisontal_;
        updateObjectsPosition();
    }
}

void FitContainer::addObject(Object *obj){
    Container::addObject(obj);
    updateObjectsPosition();
}

void FitContainer::removeAt(const size_t idx){
    Container::removeAt(idx);
    updateObjectsPosition();
}

void FitContainer::updateObjectsHPosition(){

    int avg_w = getSize().x/objects.size();
    int space_in_count = getSize().x;
    std::vector<Object*> objects_in_count = objects;

    for(Object* object: objects){
        if(!object->expand || object->getMinSize().x > avg_w){
            objects_in_count.erase(objects_in_count.begin() + findObject(objects_in_count, object));
            object->setSize(object->getMinSize());
            space_in_count -= object->getMinSize().x;
            if(objects_in_count.size() == 0){
                avg_w = 0;
            } else {
                avg_w = space_in_count/objects_in_count.size();
            }
        }
    }
    
    for(Object* object: objects_in_count){
        object->setSize({avg_w, object->getSize().y});
    }

    int next_pos=0;
    for(Object* object: objects){
        object->setPosition({next_pos, 0});
        next_pos += object->getSize().x;
        int obj_y = 0;
        if(object->fill == true){
            object->setSize({object->getSize().x, getSize().y});
        } else {
            object->setSize({object->getSize().x, 0});
            if(object->align == Object::ALIGN_CENTER){
                obj_y = getSize().y/2 - object->getMinSize().y/2;
            } else if(object->align == Object::ALIGN_BOTTOM){
                obj_y = getSize().y - object->getSize().y;
            }
            object->setPosition({object->getPosition().x, obj_y});
        }
    }


}

void FitContainer::updateObjectsVPosition(){

    int avg_h = getSize().y/objects.size();
    int space_in_count = getSize().y;
    std::vector<Object*> objects_in_count = objects;

    for(Object* object: objects){
        if(!object->expand || object->getMinSize().y > avg_h){
            objects_in_count.erase(objects_in_count.begin() + findObject(objects_in_count, object));
            object->setSize(object->getMinSize());
            space_in_count -= object->getMinSize().y;
            if(objects_in_count.size() == 0){
                avg_h = 0;
            } else {
                avg_h = space_in_count/objects_in_count.size();
            }
        }
    }
    
    for(Object* object: objects_in_count){
        object->setSize({object->getSize().x, avg_h});
    }

    int next_pos=0;
    for(Object* object: objects){
        object->setPosition({0, next_pos});
        next_pos += object->getSize().y;
        int obj_x = 0;
        if(object->fill == true){
            object->setSize({getSize().x, object->getSize().y});
        } else {
            object->setSize({0, object->getSize().y});
            if(object->align == Object::ALIGN_CENTER){
                obj_x = getSize().x/2 - object->getMinSize().x/2;
            } else if(object->align == Object::ALIGN_BOTTOM){
                obj_x = getSize().x - object->getSize().x;
            }
            object->setPosition({obj_x, object->getPosition().y});
        }
    }


}

void FitContainer::updateObjectsPosition(){
    if(horisontal){
        updateObjectsHPosition();
        return;
    }
    updateObjectsVPosition();
}
