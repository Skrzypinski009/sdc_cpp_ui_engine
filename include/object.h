#pragma once

#include <string>

#include "SDL.h"

#include "color.h"
#include "veci2.h"
#include "rect_style.h"


enum ObjectType{
    OBJECT = 0,
    CONTAINER,
    ORDER_CONTAINER,
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
    bool expand;
    bool fill;

    int align_h;
    int align_v;

    typedef enum {
        ALIGN_LEFT,
        ALIGN_RIGHT,
        ALIGN_CENTER
    } AlignHorizontal;

    typedef enum{
        ALIGN_TOP = 0,
        ALIGN_BOTTOM,
        ALIGN_MIDDLE
    } AlignVertical;

    struct {
        std::size_t top;
        std::size_t right;
        std::size_t bottom;
        std::size_t left;
    } margin;

    Object(const Object &other);
    Object();
    Object(const Veci2 position_, const Veci2 size_, const int type_=ObjectType::OBJECT);

    std::string strType() const;
    virtual void setPosition(const Veci2 position_);
    virtual void setSize(const Veci2 size_);
    // virtual void setMinSize(const Veci2 min_size_); 
    virtual void setExpand(const bool expand_);
    virtual void setFill(const bool fill_);
    virtual void setAlignH(const int align_h_);
    virtual void setAlignV(const int align_v_);
    virtual void setParent(Object* object);
    virtual void setRectStyle(RectStyle *rect_style);

    virtual Veci2 getPosition() const;
    virtual Veci2 getSize() const;
    // virtual Veci2 getMinSize() const;
    virtual bool getExpand() const;
    virtual bool getFill() const;
    virtual std::size_t getAlignH() const;
    virtual std::size_t getAlignV() const;
    virtual Object* getParent() const;
    virtual RectStyle* getRectStyle() const;

    virtual void clearParent();
    virtual Veci2 getGlobalPosition() const;
    
    SDL_Rect getClipRect() const;

    virtual void draw(SDL_Renderer *renderer);
    virtual void onLoopUpdate() {}
};
