#include "field.h"

Field::Field(Shape* shape) : shape(shape) {}

bool Field::inside(const ofPoint &point) const {
    return shape->inside(point);
}

void Field::update() {}

bool Field::ready() const {
    return true;
}

void Field::scale(float amount) {
    shape->scale(amount);
}

void Field::move(const ofPoint &newPosition) {
    shape->translate(newPosition - shape->getCenter());
}

float Field::area() const {
    return shape->area();
}

ofPoint Field::getCenter() const {
    return shape->getCenter();
}

void Field::draw() const {
    ofPushStyle();

    ofFill();

    ofSetColor(15, 15, 15);
    shape->draw();

    ofNoFill();
    ofSetColor(ofColor::white);

    ofSetCircleResolution(80);

    shape->draw();

    ofPopStyle();
}

ColorField::ColorField(Shape *shape, const ofColor &color) : 
    Field(shape), color(color) {}

void ColorField::updateParticle(Particle &particle) const {
    particle.setColor(color);
}

void ColorField::draw() const {
    ofPushStyle();

    ofFill();

    ofSetColor(15, 15, 15);
    shape->draw();

    ofNoFill();
    ofSetColor(color);
    
    ofSetCircleResolution(80);

    shape->draw();

    ofPopStyle();
}

ForceField::ForceField(Shape *shape, const ofVec2f &force) : 
    Field(shape), force(force) {}

void ForceField::updateParticle(Particle &particle) const {
    particle.applyForce(force);
}

