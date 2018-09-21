#include "target.h"

Target::Target(const ofRectangle &zone, float neededFlowRate, const ofColor &color,
               const std::string &trackPath = "") :
    targetZone(zone), 
    neededFlowRate(neededFlowRate), 
    color(color) {
        lastParticleTime = ofGetElapsedTimef();

        track.load(trackPath);

        if (track.isLoaded() == false)
            throw "Could not load sound : " + trackPath;

        track.setLoop(true);

        track.play();
        track.setPaused(true);

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

    float volume = ofMap(progress, 0, 100, 0.1, 1);

    track.setVolume(volume);

    if (progress == 0)
        track.setPaused(true);
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

    if (track.isPlaying() == false && progress >= 5)
        track.setPaused(false);

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
