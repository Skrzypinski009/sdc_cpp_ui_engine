#pragma once

#include <vector>

#include "button.h"

class EventManager{
    std::vector<Button*> buttons;
    Button* focus_button;

public:
    bool exit_signal;

    EventManager();

    void update();
    int registerButton(Button* button);
    int unregisterButton(Button* button);
    void unregisterAllButtons();
    void registerAllButtons(Object* obj);
    void scanObjectForButtons(Object* obj);
    Button* checkButtons(const Veci2 click_pos);
};