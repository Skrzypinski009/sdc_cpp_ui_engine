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