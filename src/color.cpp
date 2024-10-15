#include "color.h"

#include <string.h>
#include <string>
#include <algorithm>

#include "SDL.h"

#include "utils.h"
#include "log.h"

const Color Color::TRANSPARENT =    Color(0,0,0,0);
const Color Color::BLACK =          Color(0,0,0,255);
const Color Color::WHITE =          Color(255,255,255,255);
const Color Color::RED =            Color(255,0,0,255);
const Color Color::GREEN =          Color(0,255,0,255);
const Color Color::BLUE =           Color(0,0,255,255);
const Color Color::YELLOW =         Color(255,255,0,255);
const Color Color::CYAN =           Color(0,255,255,255);
const Color Color::MAGENTA =        Color(255,0,255,255);

Color::Color(){
    Color(Color::BLACK);
}

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a=255):
    r(r), g(g), b(b), a(a) {}

Color::Color(Color* other) {
    r = other->r;
    g = other->g;
    b = other->b;
    a = other->a;
}

Color::Color(const char* hex) : Color(Color::BLACK) {
    int len = strlen(hex);
    if (len != 7 && len != 9 && len != 4 && len != 5){
        setColor(Color::BLACK); 
        Log::warning("Color hex code len is not correct! Setting color to BLACK.");
        return;
    }
    if (hex[0] != '#'){
        setColor(Color::BLACK);
        Log::warning("Color hex code begining is not '#'! Setting color to BLACK.");
        return;
    };

    const char* hex_code = "0123456789ABCDEF";

    Uint8* current_val = &r;

    for (int i=1; i<len; i++) {
        std::size_t val = findInString(hex_code, hex[i]);
        if (val == -1) {
            setColor(Color::BLACK); 
            Log::warning("Color hex code char is wrong! Setting color to BLACK.");
            return;
        }
        if (len != 4 && len != 5){
            *current_val += i%2==1 ? val*16 : val;
            current_val += i%2==0? 1: 0;
        } else {
            *current_val += val*16 + val;
            current_val += 1;
        }
    }
}

void Color::setColor(const Color color){
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
}
