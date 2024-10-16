#include "signal_manager.h"

#include <functional>
#include <map>
#include <vector>

std::map<std::string, std::vector<void (*)()>> SignalManager::signals = {};

void SignalManager::connect(std::string name, void (*func)()) {
    SignalManager::signals[name].push_back(func);
}

void SignalManager::emitSignal(std::string name) {
    for (auto signal : SignalManager::signals[name]) {
        signal();
    }
}