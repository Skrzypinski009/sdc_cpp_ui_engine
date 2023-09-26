#pragma once

#include <iostream>

struct Veci2 {
    int x;
    int y;

    Veci2(int x_, int y_) : x(x_), y(y_) {}

    Veci2() : x(0), y(0) {}

    void add(const Veci2& other) {
        x += other.x;
        y += other.y;
    }

    void diff(const Veci2& other) {
        x -= other.x;
        y -= other.y;
    }
    
    Veci2& operator+=(const Veci2& other) {
        add(other);
        return *this;
    }

    Veci2& operator-=(const Veci2& other) {
        diff(other);
        return *this;
    }
};

Veci2 operator+(const Veci2& lhs, const Veci2& rhs);
Veci2 operator-(const Veci2& lhs, const Veci2& rhs);

