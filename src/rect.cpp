#include "../include/internal/rect.hpp"

Rect::Rect(float x, float y, float w, float h) : x(x),
                                                 y(y),
                                                 w(w),
                                                 h(h) {
}

bool Rect::Contains(float x, float y) {
    if ((x >= this->x)&&(x <= this->x + this->w)) {   
        return ((y >= this->y) && (y <= this->y + this->h))
        ? true 
        : false;
    } else {
        return false;
    }
}