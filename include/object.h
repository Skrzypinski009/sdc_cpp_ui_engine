#pragma once

#include <SDL2/SDL_render.h>
#include "color.h"
#include "veci2.h"
#include "rect_style.h"

#include <iostream>
#include <string>
#include <vector>

enum ObjectType{
    OBJECT = 0,
    CONTAINER,
    FIT_CONTAINER,
    RECTANGLE,
    LABEL,
    BUTTON
};

class Object{
    Object* parent;
    RectStyle *rect_style;
public:
    int type;
    Veci2 position;
    Veci2 size;
    Veci2 min_size;
    bool expand;
    bool fill;
    size_t align;

    enum{
        ALIGN_LEFT,
        ALIGN_RIGHT,
        ALIGN_TOP,
        ALIGN_BOTTOM,
        ALIGN_CENTER
    };

    Object(const Object &other);
    Object();
    Object(const Veci2 position_, const Veci2 size_, const int type_=ObjectType::OBJECT);

    std::string strType() const;
    virtual void setPosition(const Veci2 position_);
    virtual void setSize(const Veci2 size_);
    virtual void setMinSize(const Veci2 min_size_); 
    virtual void setExpand(const bool expand_);
    virtual void setFill(const bool fill_);
    virtual void setAlign(const size_t align_);
    virtual void setParent(Object* object);
    virtual void setRectStyle(RectStyle *rect_style);

    virtual Veci2 getPosition() const;
    virtual Veci2 getSize() const;
    virtual Veci2 getMinSize() const;
    virtual bool getExpand() const;
    virtual bool getFill() const;
    virtual size_t getAlign() const;
    virtual Object* getParent() const;
    virtual RectStyle* getRectStyle() const;

    virtual void clearParent();
    virtual Veci2 getGlobalPosition() const;
    
    SDL_Rect getClipRect() const;

    virtual void draw(SDL_Renderer *renderer);
    virtual void onLoopUpdate() {}
};
