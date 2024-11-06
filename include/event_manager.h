#pragma once

#include <vector>

#include "button.h"
#include "container.h"
#include "input_object.h"

class EventManager{
    std::vector<Button*> buttons;
    InputObject* focus_object;

public:
    bool exit_signal;

    EventManager();

    void update(Container* root_obj);
    // int registerButton(Button* button);
    // int unregisterButton(Button* button);
    // void unregisterAllButtons();
    // void registerAllButtons(Object* obj);
    // void scanObjectForButtons(Object* obj);
    // Button* checkButtons(const Veci2 click_pos);
// new
    bool changeFocus(const Veci2 click_pos, Container* container);
    bool pressedCheck(Object* obj, const Veci2 click_pos);
};