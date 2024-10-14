#include "event_manager.h"

#include "utils.h"
#include "container.h"


#include "SDL.h"

EventManager::EventManager(){
    exit_signal = false;

}


void EventManager::update(){
    SDL_Event ev;
    while(SDL_PollEvent(&ev) != 0){
        if(ev.type == SDL_QUIT)
            exit_signal = true;
        else if(ev.type == SDL_MOUSEBUTTONDOWN){
            //std::cout<<"Mouse button down at: ("<< ev.button.x << ", " << ev.button.y << ")\n";
            Button* button = checkButtons({ev.button.x, ev.button.y});
            if(button){
                focus_button = button;
                button->setPressed(true);
            } else {
                focus_button = nullptr;
            }
        }
        else if(ev.type == SDL_MOUSEBUTTONUP){
            //std::cout<<"Mouse button up at: ("<< ev.button.x << ", " << ev.button.y << ")\n";
            if(focus_button){
                focus_button->setPressed(false);
            }
            
        }
    }
}


// Adding button pointer to buttons in EventManager object.
// returns 1 on success and 0 on fail.
int EventManager::registerButton(Button *button){
    if(findObjectInVector(buttons, button) == -1){
        buttons.push_back(button);
        return 1;
    }
    return 0;
}

// Removing button pointer from buttons in EventManager object.
// returns 1 on success and 0 on fail.
int EventManager::unregisterButton(Button *button){
    int idx = findObjectInVector(buttons, button);
    if(idx > -1){
        buttons.erase(buttons.begin() + idx);
        return 1;
    }
    return 0;
}

void EventManager::unregisterAllButtons(){
    buttons.clear();
}

void EventManager::registerAllButtons(Object* obj){
    unregisterAllButtons();
    if(obj){
        scanObjectForButtons(obj);
    }
}

void EventManager::scanObjectForButtons(Object* obj){
    if(obj->type == ObjectType::CONTAINER || obj->type == ObjectType::FIT_CONTAINER){
        Container* con = (Container*)obj;
        for(int i = con->objects.size()-1; i>-1; i--){
            scanObjectForButtons(con->objects[i]);
        }
        return;
    }
    if(obj->type == ObjectType::BUTTON){
        registerButton( (Button*)obj );
    }
}

Button* EventManager::checkButtons(const Veci2 click_pos){
    for(Button* button : buttons){
        if(button->pressedCheck(click_pos) ){
            return button;
        }
    }
    return nullptr;
}