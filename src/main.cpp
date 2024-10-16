#include <iostream>
#include <vector>

#include "object.h"
#include "color.h"
#include "container.h"
#include "order_container.h"
#include "label.h"
#include "app.h"
#include "rect_style.h"
#include "log.h"
#include "style_manager.h"

void registerStyles() {
    RectStyle *black_white = new RectStyle({Color("#000"), Color("#FFF")});
    StyleManager::addStyle("BlackWhite", black_white);
    RectStyle *gray = new RectStyle({40,40,40, 255}, {0,0,0,0});
    StyleManager::addStyle("Gray", gray);
    Log::print(StyleManager::styles);
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
        Label *label = new Label("Hey, what's up?",
            "../fonts/SourceCodePro-Regular.ttf",
            20, {255,255,255}, true);
        label->loadFont();
        label->setPosition({100,100});
        label->setSize({200, 30});
        label->setAlignH(Object::ALIGN_CENTER);
        // label->setRectStyle(rect_style);
        or_con->addObject(label);
    }
    
    { //button
        Button *button = new Button(Veci2(200, 200), Veci2(200,200));
        button->setStyle("BlackWhite");
        button->setAlignH(Object::ALIGN_CENTER);
        or_con->addObject(button);
    }
}


int main(int argc, char *argv[])
{
    App app({1280, 720});
    registerStyles();
    createObjects(app);
    
    app.start();
    app.loop();
    app.stop();
    
    StyleManager::clearStyles();
    return 0;
}
