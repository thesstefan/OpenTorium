#include "target.h"

Target::Target(const ofRectangle &zone, int neededParticles, float neededFlowRate,
               const ofColor &color) :
    targetZone(zone), 
    neededParticles(neededParticles), 
    neededFlowRate(neededFlowRate), 
    color(color) {
        lastParticleTime = ofGetElapsedTimef();

        currentParticles = 0;
}

bool Target::inside(const ofPoint& point) const {
    return targetZone.inside(point);
}

void Target::update() {
    const float timeSinceLastParticle = ofGetElapsedTimef() - lastParticleTime;

    if (timeSinceLastParticle > neededFlowRate)
        currentParticles--;

    currentParticles = ofClamp(currentParticles, 0, neededParticles);
}

bool Target::ready() const {
    return currentParticles >= neededParticles;
}

void Target::updateParticle(Particle &particle) {
    if (particle.getColor() != color)
        return;

    particle.kill();

    if (currentParticles < neededParticles)
        currentParticles++;

    lastParticleTime = ofGetElapsedTimef();
}

void Target::draw() const {
    ofPushStyle();

    ofSetColor(color);

    ofNoFill();

    ofDrawRectangle(targetZone);

    ofFill();

    ofRectangle progressRender = ofRectangle(targetZone.x, targetZone.y, targetZone.width, 1);
    progressRender.scaleHeight(ofMap(currentParticles, 0, neededParticles, 1, targetZone.height));

    ofDrawRectangle(progressRender);

    ofPopStyle();
}
