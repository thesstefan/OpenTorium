#include "shape.h"

Shape::Shape() {}

Rectangle::Rectangle(const ofPoint& origin, float width, float height) 
    : origin(origin), width(width), height(height) {}

void Rectangle::draw() const {
    ofDrawRectangle(origin, width, height);
}

ofPoint Rectangle::getCenter() const {
    return ofPoint(origin.x + width / 2, origin.y + height / 2);
}

ofPoint Rectangle::getRandomPoint() const {
    return ofPoint(ofRandom(origin.x, origin.x + width), ofRandom(origin.y, origin.y + height));
}

bool Rectangle::inside(const ofPoint& point) const {
    return point.x >= origin.x && point.x <= origin.x + width &&
           point.y >= origin.y && point.y <= origin.y + height;
}

void Rectangle::scale(float amount) {
    width *= amount;
    height *= amount;
}

void Rectangle::translate(const ofPoint &amount) {
    origin = amount;
}

Ellipse::Ellipse(const ofPoint& center, float width, float height) :
    center(center), width(width), height(height) {}

void Ellipse::draw() const {
    ofDrawEllipse(center, width, height);
}

ofPoint Ellipse::getCenter() const {
    return center;
}

ofPoint Ellipse::getRandomPoint() const {
    Rectangle boundingBox(ofPoint(center.x - width / 2, center.y - height / 2), width, height);

    while (true) {
        ofPoint point = boundingBox.getRandomPoint();

        if (inside(point))
            return point;
    }
}

bool Ellipse::inside(const ofPoint& point) const {
    return (((point.x - center.x) * (point.x - center.x)) / ((width * width) / 4)) +
           (((point.y - center.y) * (point.y - center.y)) / ((height * height) / 4)) <= 1;

}

void Ellipse::scale(float amount) {
    width *= amount;
    height *= amount;
}

void Ellipse::translate(const ofPoint &amount) {
    center = amount;
}

PolylineShape::PolylineShape() {}

void PolylineShape::draw() const {
    ofPolyline::draw();
}

ofPoint PolylineShape::getCenter() const {
    return getCentroid2D();
}

ofPoint PolylineShape::getRandomPoint() const {
    ofRectangle boundingBox = ofPolyline::getBoundingBox();

    while (true) {
        ofPoint point = ofPoint(ofRandom(boundingBox.x + boundingBox.width),
                                ofRandom(boundingBox.y + boundingBox.height));

        if (ofPolyline::inside(point))
            return point;
    }
}

bool PolylineShape::inside(const ofPoint& point) const {
    return ofPolyline::inside(point);
}

void PolylineShape::scale(float amount) {
    ofPoint center = getCenter();

    ofPolyline::scale(amount, amount);

    ofPolyline::translate(center - getCenter());
}

void PolylineShape::translate(const ofPoint &amount) {
    ofPolyline::translate(amount - getCenter());
}
