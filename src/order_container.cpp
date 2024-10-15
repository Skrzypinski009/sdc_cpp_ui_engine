#include "order_container.h"

#include <iostream>

#include "SDL.h"

#include "container.h"
#include "veci2.h"
#include "object.h"


OrderContainer::OrderContainer()
    : Container({0,0}, {100,100}, ObjectType::ORDER_CONTAINER) {}

OrderContainer::OrderContainer(const Veci2 position_, const Veci2 size_, const int type_)
    : Container(position_, size_, type_) {}

void OrderContainer::setHorisontal(const bool horisontal_){
    if(horisontal != horisontal_){
        horisontal = horisontal_;
        updateObjectsPosition();
    }
}

void OrderContainer::addObject(Object *obj){
    Container::addObject(obj);
    updateObjectsPosition();
}

void OrderContainer::removeAt(const std::size_t idx){
    Container::removeAt(idx);
    updateObjectsPosition();
}

void OrderContainer::updateObjectsHPosition() {
    int next_x = 0;
    for (Object* object: objects) {
        switch(object->getAlignV()){
            case ALIGN_TOP:
                object->setPosition({next_x, 0});
                break;
            case ALIGN_MIDDLE:
                object->setPosition({next_x, getSize().y / 2 - object->getSize().y / 2});
                break;
            case ALIGN_BOTTOM:
                object->setPosition({next_x, getSize().y - object->getSize().y});
        }
        next_x += object->getSize().x;
    }
}

void OrderContainer::updateObjectsVPosition() {
    int next_y = 0;
    for (Object* object: objects) {
        switch(object->getAlignH()){
            case ALIGN_LEFT:
                object->setPosition({0, next_y});
                break;
            case ALIGN_CENTER:
                object->setPosition({getSize().x / 2 - object->getSize().x / 2, next_y});
                break;
            case ALIGN_RIGHT:
                object->setPosition({getSize().x - object->getSize().x, next_y});
        }
        next_y += object->getSize().y;
    }
}

// void OrderContainer::updateObjectsHPosition(){

//     int avg_w = getSize().x/objects.size();
//     int space_in_count = getSize().x;
//     std::vector<Object*> objects_in_count = objects;

//     for(Object* object: objects){
//         if(!object->expand || object->getMinSize().x > avg_w){
//             objects_in_count.erase(objects_in_count.begin() + findObject(objects_in_count, object));
//             object->setSize(object->getMinSize());
//             space_in_count -= object->getMinSize().x;
//             if(objects_in_count.size() == 0){
//                 avg_w = 0;
//             } else {
//                 avg_w = space_in_count/objects_in_count.size();
//             }
//         }
//     }
    
//     for(Object* object: objects_in_count){
//         object->setSize({avg_w, object->getSize().y});
//     }

//     int next_pos=0;
//     for(Object* object: objects){
//         object->setPosition({next_pos, 0});
//         next_pos += object->getSize().x;
//         int obj_y = 0;
//         if(object->fill == true){
//             object->setSize({object->getSize().x, getSize().y});
//         } else {
//             object->setSize({object->getSize().x, 0});
//             if(object->align == Object::ALIGN_CENTER){
//                 obj_y = getSize().y/2 - object->getMinSize().y/2;
//             } else if(object->align == Object::ALIGN_BOTTOM){
//                 obj_y = getSize().y - object->getSize().y;
//             }
//             object->setPosition({object->getPosition().x, obj_y});
//         }
//     }


// }

// void OrderContainer::updateObjectsVPosition(){

//     int avg_h = getSize().y/objects.size();
//     int space_in_count = getSize().y;
//     std::vector<Object*> objects_in_count = objects;

//     for(Object* object: objects){
//         if(!object->expand || object->getMinSize().y > avg_h){
//             objects_in_count.erase(objects_in_count.begin() + findObject(objects_in_count, object));
//             object->setSize(object->getMinSize());
//             space_in_count -= object->getMinSize().y;
//             if(objects_in_count.size() == 0){
//                 avg_h = 0;
//             } else {
//                 avg_h = space_in_count/objects_in_count.size();
//             }
//         }
//     }
    
//     for(Object* object: objects_in_count){
//         object->setSize({object->getSize().x, avg_h});
//     }

//     int next_pos=0;
//     for(Object* object: objects){
//         object->setPosition({0, next_pos});
//         next_pos += object->getSize().y;
//         int obj_x = 0;
//         if(object->fill == true){
//             object->setSize({getSize().x, object->getSize().y});
//         } else {
//             object->setSize({0, object->getSize().y});
//             if(object->align == Object::ALIGN_CENTER){
//                 obj_x = getSize().x/2 - object->getMinSize().x/2;
//             } else if(object->align == Object::ALIGN_BOTTOM){
//                 obj_x = getSize().x - object->getSize().x;
//             }
//             object->setPosition({obj_x, object->getPosition().y});
//         }
//     }


// }

void OrderContainer::updateObjectsPosition(){
    if(horisontal){
        updateObjectsHPosition();
        return;
    }
    updateObjectsVPosition();
}
