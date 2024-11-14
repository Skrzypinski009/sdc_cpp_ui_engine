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
        black_white->addOption("background_color:pressed", "#000");
        black_white->addOption("border_color:pressed", "#F00");

    Style* gray = new Style;
        gray->addOption("background_color", "#444444");

    Style* text_style = new Style;
        // font_style->addOption("border_color", "#FF0000");
        text_style->addOption("font_path", "../fonts/SourceCodePro-Regular.ttf");
        text_style->addOption("font_size", "28");
        text_style->addOption("text_color", "#000088");
        text_style->addOption("text_wrap", "false");
        text_style->addOption("text_clip", "false");

    StyleManager::addStyle("BlackWhite", black_white);
    StyleManager::addStyle("Gray", gray);
    StyleManager::addStyle("text_default", text_style);
}

void on_button_pressed(Object* sender){
    SimpleButton* b = (SimpleButton*) sender;
    b->setSize(Vec2(30,30));
}

void on_button_released(Object* sender){
    SimpleButton* b = (SimpleButton*) sender;
    b->setSize(Vec2(200,200));
}

void on_button_loop(Object* obj, float delta){
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

    { //label
        Label *label = new Label(app.renderer, "Hey, what's up?", "text_default");
        label->setPosition({100,100});
        label->setSize({150, 20});
        label->setAlignH(Object::ALIGN_LEFT);
        or_con->addObject(label);
    }

    { //button
        SimpleButton *button = new SimpleButton(Veci2(200, 200), Veci2(200,200));
        button->setStyle("BlackWhite");
        button->setAlignH(Object::ALIGN_CENTER);
        // button->setName("button1");
        button->connect("pressed", on_button_pressed);
        button->connect("released", on_button_released);
        // button->setLoopFunction(on_button_loop);
        or_con->addObject(button);
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
