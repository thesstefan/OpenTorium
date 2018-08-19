#include "field.h"

Field::Field(Shape* shape) : shape(shape) {}

void Field::draw() const {
    ofPushStyle();

    ofNoFill();
    shape->draw();

    ofPopStyle();
}

const Shape& Field::getShape() const {
    return *shape;
}

ColorField::ColorField(Shape* shape, const ofColor& color) : 
    Field(shape), color(color) {}

void ColorField::updateParticle(std::unique_ptr<Particle>& particle) const {
    particle->setColor(color);
}

ForceField::ForceField(Shape* shape, const ofVec2f& force) : 
    Field(shape), force(force) {}

void ForceField::updateParticle(std::unique_ptr<Particle>& particle) const {
    particle->applyForce(force);
}
