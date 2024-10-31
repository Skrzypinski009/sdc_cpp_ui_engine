#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>

class Object;

class SignalManager{
public:
    static std::map<
        Object*, 
        std::map< std::string, std::vector<void (*)(Object*)> > 
    > signals;
    static void connect(Object* sender, std::string name, void (*func)(Object*));
    static void emitSignal(Object* sender, std::string name);
};