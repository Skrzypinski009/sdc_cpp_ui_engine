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


void createObjects(App &app){
    // rect_style
    RectStyle *rect_style = new RectStyle({Color("#000"), Color("#FFF")});
    app.register_style(rect_style);
    RectStyle *rect_style2 = new RectStyle({40,40,40, 255}, {0,0,0,0});
    app.register_style(rect_style2);

    Container *con = new Container;
    con->setRectStyle(rect_style);
    app.root_obj = con;
    
    OrderContainer *or_con = new OrderContainer;
    {
        or_con->setPosition({300, 140});
        or_con->setSize({300, 400});
        or_con->setRectStyle(rect_style2);
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
        button->setRectStyle(rect_style);
        button->setAlignH(Object::ALIGN_CENTER);
        or_con->addObject(button);
    }
}


int main(int argc, char *argv[])
{
    App app({1280, 720});
    createObjects(app);
    
    app.start();
    app.loop();
    app.stop();
    
    
    return 0;
}
