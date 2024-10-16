#pragma once

#include <map>
#include <string>

#include "rect_style.h"

class StyleManager {
public:
    static std::map<std::string, RectStyle*> styles;

    static void addStyle(const std::string key, RectStyle* style);
    static RectStyle* getStyle(const std::string key);
    static void clearStyles();
};