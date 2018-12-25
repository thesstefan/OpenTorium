#include "field.h"

Field::Field(Shape* shape, bool mobile) : shape(shape), mobile(mobile) {}

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

void Field::scale(const ofVec2f& screenChangeProportion) {
    shape->scale(screenChangeProportion);
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

    ofNoFill();
    ofSetColor(ofColor::white);

    ofSetCircleResolution(80);

    shape->draw();

    ofPopStyle();
}

ColorField::ColorField(Shape *shape, const ofColor &color, bool mobile) : 
    Field(shape, mobile), color(color) {}

void ColorField::updateParticle(Particle &particle) const {
    particle.setColor(color);
}

void ColorField::draw() const {
    ofPushStyle();

    ofNoFill();
    ofSetColor(color);
    
    ofSetCircleResolution(80);

    shape->draw();

    ofPopStyle();
}

ForceField::ForceField(Shape *shape, const ofVec2f &force, bool mobile) : 
    Field(shape, mobile), force(force) {}

void ForceField::updateParticle(Particle &particle) const {
    particle.applyForce(force);
}
