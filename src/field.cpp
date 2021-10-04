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

void Field::drawInside() const {}

void Field::draw() const {
    ofPushStyle();

    ofNoFill();
    ofSetColor(ofColor::white);
    ofSetLineWidth(2);

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
    ofSetLineWidth(5);
    
    ofSetCircleResolution(100);

    shape->draw();

    ofPopStyle();
}

ForceField::ForceField(Shape *shape, const ofVec2f &force, bool mobile) : 
    Field(shape, mobile), force(force) {
    arrow.load("data/arrow.png");
    arrow.resize(40, 40);

    arrow.setAnchorPoint(arrow.getWidth()/2, arrow.getHeight()/2);

    rotationAngle = ofVec2f(0, -1).angle(this->force);
}

void ForceField::updateParticle(Particle &particle) const {
    particle.applyForce(force);
}

void ForceField::scale(const ofVec2f& screenChangeProportion) {
    Field::scale(screenChangeProportion);

    force *= screenChangeProportion;
}

void ForceField::drawInside() const {
    ofPushStyle();

    ofFill();
    ofSetColor(ofColor(14, 14, 14));

    ofSetCircleResolution(100);

    shape->draw();

    ofPopStyle();
}

void ForceField::draw() const {
    ofPushStyle();

    ofNoFill();
    ofSetCircleResolution(100);

    ofSetColor(ofColor::white);
    ofSetLineWidth(2);

    shape->draw();

    auto drawPoint = this->shape->getCenter();

    ofPushMatrix();
        ofTranslate(drawPoint.x, drawPoint.y, 0);
        ofRotate(this->rotationAngle, 0, 0, 1);
        ofPushMatrix();
            arrow.draw(0, 0, 0);
        ofPopMatrix();
    ofPopMatrix();

    ofPopStyle();
}
