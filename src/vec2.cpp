#include "vec2.h"

#include "veci2.h"

Vec2::Vec2(const Veci2& vi2){
    x=(float)vi2.x;
    y=(float)vi2.y;
}

Vec2 operator+(const Vec2& lhs, const Vec2& rhs) {
    return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vec2 operator-(const Vec2& lhs, const Vec2& rhs) {
    return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

