#pragma once

#include <map>
#include <string>

#include "object.h"
#include "log.h"

class ObjectManager{
public:
    static std::map<std::string, Object*> objects;

    static void addObject(std::string name, Object* object);
    static Object* getObject(std::string name);
    static bool hasObject(std::string name);

};