#pragma once

#include <map>
#include <string>

#include "style.h"

class StyleManager {
public:
    static std::map<std::string, Style*> styles;

    static void addStyle(const std::string key, Style* style);
    static Style* getStyle(const std::string key);
    static void clearStyles();
};