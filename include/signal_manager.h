#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>

class SignalManager{
public:
    static std::map<std::string, std::vector<void (*)()>> signals;
    static void connect(std::string name, void (*func)());
    static void emitSignal(std::string name);
};