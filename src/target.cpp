#include "target.h"

Target::Target(const ofRectangle& zone) :
    targetZone(zone), neededFlowRate(0.1)  {
        lastParticleTime = ofGetElapsedTimef();

        progress = 0;
}

bool Target::inside(const ofPoint& point) const {
    return targetZone.inside(point);
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

    progress = ofClamp(progress, 0, 100);
}

void Target::updateParticle(Particle &particle) {
    particle.kill();

    lastParticleTime = ofGetElapsedTimef();
}

void Target::draw() const {
    ofPushStyle();

    ofNoFill();

    ofDrawRectangle(targetZone);

    ofFill();

    ofRectangle progressRender = ofRectangle(targetZone.x, targetZone.y, targetZone.width, 1);
    progressRender.scaleHeight(ofMap(progress, 0, 100, 1, targetZone.height));

    ofDrawRectangle(progressRender);

    ofPopStyle();
}
