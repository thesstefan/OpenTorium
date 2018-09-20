#include "target.h"

Target::Target(const ofRectangle &zone, float neededFlowRate, const ofColor &color) :
    targetZone(zone), 
    neededFlowRate(neededFlowRate), 
    color(color) {
        lastParticleTime = ofGetElapsedTimef();

        progress = 0;
}

bool Target::inside(const ofPoint& point) const {
    return targetZone.inside(point);
}

void Target::update() {
    const float timeSinceLastParticle = ofGetElapsedTimef() - lastParticleTime;

    if (timeSinceLastParticle > neededFlowRate)
        progress--;

    progress = ofClamp(progress, 0, 100);
}

bool Target::ready() const {
    return progress == 100;
}

void Target::updateParticle(Particle &particle) {
    if (particle.getColor() != color)
        return;

    particle.kill();

    if (progress < 100)
        progress++;

    lastParticleTime = ofGetElapsedTimef();
}

void Target::draw() const {
    ofPushStyle();

    ofSetColor(color);

    ofNoFill();

    ofDrawRectangle(targetZone);

    ofFill();

    ofRectangle progressRender = ofRectangle(targetZone.x, targetZone.y, targetZone.width, 1);
    progressRender.scaleHeight(ofMap(progress, 0, 100, 1, targetZone.height));

    ofDrawRectangle(progressRender);

    ofPopStyle();
}
