#pragma once

#include <string>
#include <map>
#include <vector>

#include "SDL.h"

#include "color.h"
#include "veci2.h"
#include "vec2.h"
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
    std::string name;

    void (*loop_function)(Object*, float);
public:
    int type;
    Vec2 position;
    Vec2 size;
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
    Object(const Vec2 position_, const Vec2 size_, const int type_=ObjectType::OBJECT);

    std::string strType() const;
    virtual void setPosition(const Vec2 position_);
    virtual void setSize(const Vec2 size_);
    // virtual void setMinSize(const Vec2 min_size_); 
    virtual void setExpand(const bool expand_);
    virtual void setFill(const bool fill_);
    virtual void setAlignH(const int align_h_);
    virtual void setAlignV(const int align_v_);
    virtual void setParent(Object* object);
    virtual void setRectStyle(RectStyle *rect_style);
    virtual void setStyle(const std::string);
    virtual void setName(const std::string);
    virtual void setLoopFunction(void (*loop_func)(Object*, float));

    virtual Vec2 getPosition() const;
    virtual Vec2 getSize() const;
    // virtual Vec2 getMinSize() const;
    virtual bool getExpand() const;
    virtual bool getFill() const;
    virtual std::size_t getAlignH() const;
    virtual std::size_t getAlignV() const;
    virtual Object* getParent() const;
    virtual RectStyle* getRectStyle() const;
    virtual std::string getName() const;

    virtual void clearParent();
    virtual Vec2 getGlobalPosition() const;
    
    SDL_Rect getClipRect() const;

    virtual void draw(SDL_Renderer *renderer);
    virtual void onLoopUpdate(float delta);
    virtual void update();
    virtual void updateParent();

    virtual void emitSignal(std::string signal_name);
    virtual void connect(std::string signal_name, void (*func)(Object*));

// Old Object Manager
    static std::map<std::string, Object*> objects;
    static void addObject(std::string name, Object* object);
    static Object* getObject(std::string name);
    static bool hasObject(std::string name);
};

/*
    (object_ptr, signal_name, signal_args?)


*/