#include "../include/app.h"
#include "../include/utils.h"
#include "../include/event_manager.h"

#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_render.h>

App::App(){
    root_obj = nullptr;

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
        800, 600, 
        SDL_WINDOW_SHOWN //| SDL_WINDOW_RESIZABLE
    );
    
    renderer = SDL_CreateRenderer(window, 0, 0);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);

    if(window == NULL){
        throw "Window Creation Eroor";
    }
}

void App::start(){
    event_manager.registerAllButtons(root_obj);
    updateRootObject();
}

void App::stop(){
    if(root_obj) 
        deleteObject(root_obj);
    delete_styles();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
}

void App::loop(){
    
    while(true){
        draw();
        event_manager.update();
        if(event_manager.exit_signal) 
            return;
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
        root_obj->setSize({w,h});
        root_obj->setPosition({0,0});
    }
}

void App::deleteObject(Object *obj){
    if(obj->type == ObjectType::CONTAINER || obj->type == ObjectType::FIT_CONTAINER){
        for(Object *child : ((Container*)obj)->objects){
            deleteObject(child);
        }
    }
    std::cout<<"deleting: "<<obj->strType()<<"\n";
    delete obj;
}

void App::register_style(RectStyle *rect_style){
    styles.push_back(rect_style);
}

void App::delete_styles(){
    for(RectStyle* rect_style : styles)
        delete rect_style;
}
