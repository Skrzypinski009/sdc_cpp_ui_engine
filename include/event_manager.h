#pragma once

#include <vector>

#include "simple_button.h"
#include "container.h"
#include "input_object.h"

class EventManager{
    InputObject* focus_object;

public:
    bool exit_signal;

    EventManager();

    void update(Container* root_obj);
// new
    bool changeFocus(const Veci2 click_pos, Container* container);
    bool pressedCheck(Object* obj, const Veci2 click_pos);
};