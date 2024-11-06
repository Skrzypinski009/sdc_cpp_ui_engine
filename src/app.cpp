#include "app.h"

#include <chrono>

#include "SDL.h"

#include "utils.h"
#include "event_manager.h"
#include "log.h"
#include "container.h"

namespace ch = std::chrono;

App::App(Veci2 window_size_){
    root_obj = nullptr;
    window_size = window_size_;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        throw "SDL Video Error";
    }
    if (TTF_Init() < 0){
        std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
    }

    window = SDL_CreateWindow(
        "APP",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_size.x, window_size.y, 
        SDL_WINDOW_SHOWN //| SDL_WINDOW_RESIZABLE
    );
    
    renderer = SDL_CreateRenderer(window, 0, 0);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);

    if(window == NULL){
        throw "Window Creation Eroor";
    }
}

void App::start(){
    // event_manager.registerAllButtons(root_obj);
    updateRootObject();
}

void App::stop(){
    if(root_obj) 
        deleteObject(root_obj);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
}

#define TIME_POINT std::chrono::time_point<std::chrono::high_resolution_clock>
#define DURATION std::chrono::duration<float>
#define NOW ch::high_resolution_clock::now()

float calculateDelta(TIME_POINT prev_time)
{
    TIME_POINT now = NOW;
    DURATION rdelta = now - prev_time;
    float delta = rdelta.count();
    return delta;
}

void App::loop(){
    TIME_POINT prev_time = NOW;
    float delta;

    while(true & root_obj != nullptr){
        event_manager.update((Container*) root_obj);
        if(event_manager.exit_signal) 
            return;
        delta = calculateDelta(prev_time);
        prev_time = NOW;
        root_obj->onLoopUpdate(delta);
        
        // go through every object loop
        // maybe we should register objects that are doing something
        draw();
    }
}

void App::draw(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    if(root_obj)
        root_obj->draw(renderer);
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);
}

void App::setRootObject(Object* obj){
    root_obj = obj;
}

void App::updateRootObject(){
    if(root_obj){
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        root_obj->setSize(Vec2(w,h));
        root_obj->setPosition(Vec2(0,0));
    }
}

void App::deleteObject(Object *obj){
    if(obj->type == ObjectType::CONTAINER || obj->type == ObjectType::ORDER_CONTAINER){
        for(Object *child : ((Container*)obj)->objects){
            deleteObject(child);
        }
    }
    Log::info((std::string("deleting: ") + obj->strType()).c_str());
    delete obj;
}
