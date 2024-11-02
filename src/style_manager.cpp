#include "style_manager.h"

#include <string>
#include <map>
#include <exception>

#include "log.h"

std::map<std::string, Style*> StyleManager::styles = {};

void StyleManager::addStyle(const std::string key, Style* style)
{
    try
    {
        StyleManager::styles[key] = style;
    }
    catch (std::exception)
    {
        Log::error("Tried to add style to key, that already exist!");
    }
}

Style* StyleManager::getStyle(const std::string key)
{
    try
    {
        return StyleManager::styles[key];
    }
    catch (std::exception)
    {
        Log::error("There is no style with that name!");
    }
    return nullptr;
}

void StyleManager::clearStyles() {
    for (const auto p : StyleManager::styles) {
        delete p.second;
    }
    StyleManager::styles.clear();
}