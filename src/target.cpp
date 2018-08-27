#include "target.h"

Target::Target(const ofRectangle& shape) :
    shape(shape), neededFlowRate(0.1)  {
        lastParticleTime = ofGetElapsedTimef();

        progress = 0;
    }

bool Target::inside(const ofPoint& point) const {
    return shape.inside(point);
}

void Target::update() {
    const float timeSinceLastParticle = ofGetElapsedTimef() - lastParticleTime;

    if (progress >= 100.0)
        std::cout << "DONE" << std::endl;
    else {
        if (timeSinceLastParticle > neededFlowRate)
            progress -= 0.1;
        else 
            progress += 0.1;
    }

    slidingShape = ofRectangle(shape.x, shape.y, shape.width, 1);

    if (progress < 0)
        progress = 0;

    slidingShape.scaleHeight(ofMap(progress, 0, 100, 1, shape.height));
}

void Target::updateParticle(Particle &particle) {
    particle.kill();

    lastParticleTime = ofGetElapsedTimef();
}

void Target::draw() const {
    ofPushStyle();

    ofNoFill();

    ofDrawRectangle(shape);

    ofFill();

    ofDrawRectangle(slidingShape);

    ofPopStyle();
}
