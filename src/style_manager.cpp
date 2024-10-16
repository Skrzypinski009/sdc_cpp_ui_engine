#include "style_manager.h"

#include <string>
#include <map>

#include "log.h"

std::map<std::string, RectStyle*> StyleManager::styles = {};

void StyleManager::addStyle(const std::string key, RectStyle* style) {
    if (StyleManager::styles.find(key) != StyleManager::styles.end()){
        Log::error("Tried to add style to key, that already exist!");
        return;
    }
    StyleManager::styles[key] = style;
}

RectStyle* StyleManager::getStyle(const std::string key) {
    if (StyleManager::styles.find(key) == StyleManager::styles.end()) {
        Log::error("Tried to get style by key, that doesn't exist!");
        return NULL;
    }
    return StyleManager::styles.at(key); 
}

void StyleManager::clearStyles() {
    for (const auto p : styles) {
        delete p.second;
    }
    styles.clear();
}