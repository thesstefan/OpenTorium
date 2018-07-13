#include "field.h"

Field::Field(const ofPoint& center, int size) : center(center), size(size) {}

bool pointIsInCircle(const ofPoint& point, const ofPoint& circleCenter, int size) {
    float distance = (point.x - circleCenter.x) * (point.x - circleCenter.x) +
                     (point.y - circleCenter.y) * (point.y - circleCenter.y);

    return (distance * distance <= size * size);
}

void Field::update(std::list<std::unique_ptr<Particle>>& particles) {
    for (auto it = particles.begin(); it != particles.end(); it++) {
        if (pointIsInCircle((*it)->getPosition(), center, size))
            (*it)->setColor(ofColor::blue);
    }
}

void Field::draw() const{
    ofPushStyle();

    ofSetColor(ofColor::blue);
    ofNoFill();

    ofDrawCircle(center, size);

    ofPopStyle();
}
