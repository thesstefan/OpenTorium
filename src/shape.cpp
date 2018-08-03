#include "shape.h"

Shape::Shape() {}

Rectangle::Rectangle(const ofPoint& origin, float width, float height) 
    : origin(origin), width(width), height(height) {}

void Rectangle::draw() const {
    ofDrawRectangle(origin, width, height);
}

bool Rectangle::inside(const ofPoint& point) const {
    return point.x >= origin.x && point.x <= origin.x + width &&
           point.y >= origin.y && point.y <= origin.y + height;
}

Ellipse::Ellipse(const ofPoint& center, float width, float height) :
    center(center), width(width), height(height) {}

void Ellipse::draw() const {
    ofDrawEllipse(center, width, height);
}

bool Ellipse::inside(const ofPoint& point) const {
    return (((point.x - center.x) * (point.x - center.x)) / ((width * width) / 4)) +
           (((point.y - center.y) * (point.y - center.y)) / ((height * height) / 4)) <= 1;

}
