#include "style.h"

#include <map>
#include <string>

Style::Style()
{
    options = {};
}

Style::Style(std::map<std::string, std::string> options) : options(options) {}

void Style::addOption(std::string name, std::string value)
{
    options[name] = value;
}

std::string Style::get(const std::string name)
{
    return options[name];
}

bool Style::hasOption(std::string name)
{
    return options.find(name) != options.end();
}