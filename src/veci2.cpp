#include "veci2.h"

#include "vec2.h"

Veci2::Veci2(const Vec2& v2){
    x=(int)v2.x;
    y=(int)v2.y;
}

Veci2 operator+(const Veci2& lhs, const Veci2& rhs) {
    return Veci2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Veci2 operator-(const Veci2& lhs, const Veci2& rhs) {
    return Veci2(lhs.x - rhs.x, lhs.y - rhs.y);
}

