#include <iostream>
#include <vector>

#include "object.h"
#include "color.h"
#include "container.h"
#include "fit_container.h"
#include "label.h"
#include "app.h"
#include "rect_style.h"


void createObjects(App &app){
    // rect_style
    RectStyle *rect_style = new RectStyle({0,0,0, 255}, {255, 255, 255, 255});
    app.register_style(rect_style);

    Container *con = new Container;
    con->setRectStyle(rect_style);
    app.root_obj = con;
    
    { //label
        Label *label = new Label("Hey, what's up?",
            "../fonts/SourceCodePro-Regular.ttf",
            20, {255,255,255}, true);
        label->loadFont();
        label->setPosition({100,100});
        label->setSize({400, 30});
        label->setRectStyle(rect_style);
        con->addObject(label);
    }
    
    { //button
        Button *button = new Button(Veci2(200, 200), Veci2(200,200));
        button->setRectStyle(rect_style);
        con->addObject(button);
    }
}


int main(int argc, char *argv[])
{
    App app;
    createObjects(app);
    
    app.start();
    app.draw();
    app.loop();
    app.stop();
    
    
    return 0;
}
