#include "object_manager.h"

std::map<std::string, Object*> ObjectManager::objects = {};

void ObjectManager::addObject(std::string name, Object* object){
    if (ObjectManager::hasObject(name)) {
        Log::error("Object Manager can't register object with that name!");
        return;
    }
    ObjectManager::objects[name] = object;
}

Object* ObjectManager::getObject(std::string name){
    if (!ObjectManager::hasObject(name)) {
        Log::error("Object Manager can't return object with that name!");
        return NULL;
    }
    return ObjectManager::objects.at(name);
}

bool ObjectManager::hasObject(std::string name){
    if (ObjectManager::objects.find(name) == ObjectManager::objects.end())
        return false;
    return true;
}