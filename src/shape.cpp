#include "shape.h"

Shape::Shape() {}

Rectangle::Rectangle(const ofPoint& origin, float width, float height) 
    : origin(origin), width(width), height(height) {}

void Rectangle::draw() const {
    ofDrawRectangle(origin, width, height);
}

bool Rectangle::inside(const ofPoint& point) const {
    return point.x >= origin.x && point.x <= origin.y + width &&
           point.y >= origin.y && point.y <= origin.y + height;
}

Ellipse::Ellipse(const ofPoint& center, float width, float height) :
    center(center), width(width), height(height) {}

void Ellipse::draw() const {
    ofDrawEllipse(center, width, height);
}

bool Ellipse::inside(const ofPoint& point) const {
    return (point.x * point.x + point.y + point.y) <= (width * width + height * height);
}
