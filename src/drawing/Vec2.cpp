#include "core/Vec2.h"

Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

Vec2::Vec2() {
    
}

Vec2::~Vec2() {

}

void Vec2::setX(float x) {
    this->x = x;
}

void Vec2::setY(float y) {
    this->y = y;
}

float Vec2::getX() {
    return x;
}

float Vec2::getY() {
    return y;
}
