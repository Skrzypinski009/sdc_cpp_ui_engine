#include "../include/veci2.h"

Veci2 operator+(const Veci2& lhs, const Veci2& rhs) {
    return Veci2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Veci2 operator-(const Veci2& lhs, const Veci2& rhs) {
    return Veci2(lhs.x - rhs.x, lhs.y - rhs.y);
}

