#include "signal_manager.h"

#include <functional>
#include <map>
#include <vector>
#include <exception>

std::map<Object*, std::map<
                    std::string, 
                    std::vector<void (*)(Object*)>>
                > SignalManager::signals = {};

void SignalManager::connect(Object* sender, std::string name, void (*func)(Object*)) {
    SignalManager::signals[sender][name].push_back(func);
}

void SignalManager::emitSignal(Object* sender, std::string name) {
    std::vector<void (*)(Object*)> this_signals;
    try{
        this_signals = SignalManager::signals[sender][name];
    } catch (std::exception) {
        return;
    }
    for (auto signal : this_signals)
        signal(sender);
}