#pragma once 

struct Veci2;
struct Vec2 {
    float x, y;

    Vec2(float x_, float y_) : x(x_), y(y_) {}
    Vec2(int x_, int y_) : x((float)x_), y((float)y_) {}

    Vec2() : x(0), y(0) {}

    Vec2(const Veci2& vi2);

    void add(const Vec2& other) {
        x += other.x;
        y += other.y;
    }

    void diff(const Vec2& other) {
        x -= other.x;
        y -= other.y;
    }
    
    Vec2& operator+=(const Vec2& other) {
        add(other);
        return *this;
    }

    Vec2& operator-=(const Vec2& other) {
        diff(other);
        return *this;
    }
};

Vec2 operator+(const Vec2& lhs, const Vec2& rhs);
Vec2 operator-(const Vec2& lhs, const Vec2& rhs);
