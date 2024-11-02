#pragma once

#include <map>
#include <string>
#include <vector>

struct Style{
    std::map<std::string, std::string> options;
    
    Style();
    Style(std::map<std::string, std::string> options);
    void addOption(std::string name, std::string value);
    std::string get(const std::string name);
    bool hasOption(std::string name);
};