#pragma once

#include <string>

#include "input_object.h"

class TextInput: public InputObject {
    std::string text;
public:
    TextInput();

    void setText(std::string text_);
    std::string getText();
};