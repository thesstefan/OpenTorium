#include "field.h"

Field::Field(Shape* shape) : shape(shape) {}

void Field::draw() const {
    ofPushStyle();

    ofNoFill();
    shape->draw();

    ofPopStyle();
}

bool Field::inside(const ofPoint &point) const {
    return shape->inside(point);
}

ColorField::ColorField(Shape *shape, const ofColor &color) : 
    Field(shape), color(color) {}

void ColorField::updateParticle(std::unique_ptr<Particle> &particle) const {
    particle->setColor(color);
}

ForceField::ForceField(Shape *shape, const ofVec2f &force) : 
    Field(shape), force(force) {}

void ForceField::updateParticle(std::unique_ptr<Particle> &particle) const {
    particle->applyForce(force);
}
