#include <iostream>
#include <vector>

#include "object.h"
#include "color.h"
#include "container.h"
#include "order_container.h"
#include "label.h"
#include "app.h"
#include "log.h"

#include "style_manager.h"
#include "signal_manager.h"

App app({1280, 720});

void registerStyles() {
    Style* black_white = new Style;
        black_white->addOption("background_color", "#111111");
        black_white->addOption("border_color", "#FFFFFF");

    Style* gray = new Style;
        gray->addOption("background_color", "#444444");

    Style* red_border = new Style;
        red_border->addOption("border_color", "#FF0000");

    StyleManager::addStyle("BlackWhite", black_white);
    StyleManager::addStyle("Gray", gray);
    StyleManager::addStyle("RedBorder", red_border);
}

void on_button_pressed(Object* sender){
    Button* b = (Button*) sender;
    b->setSize(Vec2(30,30));
}

void on_button_released(Object* sender){
    Button* b = (Button*) sender;
    b->setSize(Vec2(200,200));
}

void on_button_loop(Object* obj, float delta){
    // Button* b = (Button*) object;
    // Vec2 bs = object->getSize();
    // float speed = delta * 30;
    // if(bs.x > 50)
        // b->setSize(Vec2(bs.x - speed, bs.y - speed));
    Veci2 m_pos;
    Vec2 o_pos = obj->getPosition();
    Vec2 o_size = obj->getSize();
    SDL_GetMouseState(&m_pos.x, &m_pos.y);
    Vec2 pos_delta = Vec2(m_pos) - (o_pos + Vec2(o_size.x/2, o_size.y/2));
    float speed = delta * 2;
    obj->setPosition(Vec2(o_pos.x + pos_delta.x * speed, o_pos.y + pos_delta.y * speed));
}

void createObjects(App &app){
    Container *con = new Container;
    con->setStyle("BlackWhite");
    app.root_obj = con;
    
    OrderContainer *or_con = new OrderContainer;
    {
        or_con->setPosition({300, 140});
        or_con->setSize({300, 400});
        or_con->setStyle("Gray");
        con->addObject(or_con);
    }

    { //button
        Button *button = new Button(Veci2(200, 200), Veci2(200,200));
        button->setStyle("BlackWhite");
        button->setAlignH(Object::ALIGN_CENTER);
        button->setName("button1");
        button->connect("button_pressed", on_button_pressed);
        button->connect("button_released", on_button_released);
        button->setLoopFunction(on_button_loop);
        con->addObject(button);
    }

    { //label
        Label *label = new Label("Hey, what's up?",
            "../fonts/SourceCodePro-Regular.ttf",
            20, {255,255,255}, true);
        label->setStyle("RedBorder");
        label->loadFont();
        label->setPosition({100,100});
        label->setSize({200, 30});
        label->setAlignH(Object::ALIGN_CENTER);
        or_con->addObject(label);
    }
}


int main(int argc, char *argv[])
{
    
    registerStyles();
    createObjects(app);
    app.start();
    app.loop();
    app.stop();
    
    StyleManager::clearStyles();
    return 0;
}
