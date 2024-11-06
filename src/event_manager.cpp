#include "event_manager.h"

#include "utils.h"
#include "container.h"
#include "input_object.h"
#include "log.h"

#include "SDL.h"

EventManager::EventManager(){
    exit_signal = false;
}


void EventManager::update(Container* root_obj){
    SDL_Event ev;

    while(SDL_PollEvent(&ev) != 0){
        if(ev.type == SDL_QUIT)
            exit_signal = true;
        else if(ev.type == SDL_MOUSEBUTTONDOWN){
            //std::cout<<"Mouse button down at: ("<< ev.button.x << ", " << ev.button.y << ")\n";
            // Button* button = checkButtons({ev.button.x, ev.button.y});
            // if(button){
            //     focus_button = button;
            //     button->setPressed(true);
            // } else {
            //     focus_button = nullptr;
            // }
            if (focus_object != nullptr)
                focus_object->setFocused(false);
            focus_object = nullptr;
            bool ok = changeFocus({ev.button.x, ev.button.y}, root_obj);
            if (ok) {
                focus_object->setPressed();
            }
        }
        else if(ev.type == SDL_MOUSEBUTTONUP){
            //std::cout<<"Mouse button up at: ("<< ev.button.x << ", " << ev.button.y << ")\n";
            if(focus_object != nullptr)
                focus_object->setReleased();
        }
    }
}


// Adding button pointer to buttons in EventManager object.
// returns 1 on success and 0 on fail.
// int EventManager::registerButton(Button *button){
//     if(findObjectInVector(buttons, button) == -1){
//         buttons.push_back(button);
//         return 1;
//     }
//     return 0;
// }

// Removing button pointer from buttons in EventManager object.
// returns 1 on success and 0 on fail.

// int EventManager::unregisterButton(Button *button){
//     int idx = findObjectInVector(buttons, button);
//     if(idx > -1){
//         buttons.erase(buttons.begin() + idx);
//         return 1;
//     }
//     return 0;
// }

// void EventManager::unregisterAllButtons(){
//     buttons.clear();
// }

// void EventManager::registerAllButtons(Object* obj){
//     unregisterAllButtons();
//     if(obj){
//         scanObjectForButtons(obj);
//     }
// }

// void EventManager::scanObjectForButtons(Object* obj){
//     if(obj->type == ObjectType::CONTAINER || obj->type == ObjectType::ORDER_CONTAINER){
//         Container* con = (Container*)obj;
//         for(int i = con->objects.size()-1; i>-1; i--){
//             scanObjectForButtons(con->objects[i]);
//         }
//         return;
//     }
//     if(obj->type == ObjectType::BUTTON){
//         registerButton( (Button*)obj );
//     }
// }

bool EventManager::changeFocus(const Veci2 click_pos, Container* container = nullptr) {
    int n = container->objects.size();
    for(int i=n-1; i>=0; i--){
        auto object = container->objects[i];
        if (object->type == CONTAINER || object->type == ORDER_CONTAINER) {
            bool r = changeFocus(click_pos, (Container*) object);
            if (r) return true;
        } else {
            if (pressedCheck(object, click_pos) & object->isInputObject()) {
                focus_object = (InputObject*) object;
                focus_object->setFocused(true);
                return true;
            }
        }
    }
    return false;
}

bool EventManager::pressedCheck(Object* obj, const Veci2 click_pos) {
    Veci2 start_pos = Veci2(obj->getGlobalPosition());
    Veci2 end_pos = start_pos + Veci2(obj->size);
    if(
        click_pos.x > start_pos.x && 
        click_pos.y > start_pos.y &&
        click_pos.x < end_pos.x &&
        click_pos.y < end_pos.y
    )
        return true;
    return false;
}