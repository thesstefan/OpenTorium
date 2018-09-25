#include "target.h"

const ofColor Target::BACKGROUND(60, 60, 60);
const ofColor Target::GRID_LINE_COLOR(25, 25, 25);

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

    ofFill();

    // Draw the background of the Target.
    ofSetColor(BACKGROUND);
    ofDrawRectangle(targetZone);

    // Draw the progress rectangle.
    ofSetColor(color);

    ofRectangle progressRender = ofRectangle(targetZone.x, targetZone.y + targetZone.height, 
                                             targetZone.width, -(targetZone.height / GRID_HORIZONTAL_LINES));

    progressRender.scaleHeight(ofMap(progress, 0, 100, 1, GRID_HORIZONTAL_LINES));

    ofDrawRectangle(progressRender);

    // Draw the grid.
    ofSetColor(GRID_LINE_COLOR);
    ofSetLineWidth(GRID_LINE_WIDTH);

    // Draw the horizontal lines of the grid.
    ofPoint currentPosition(targetZone.x, targetZone.y);
    for (int hLineIndex = 0; 
         hLineIndex < GRID_HORIZONTAL_LINES
         && currentPosition.y < targetZone.y + targetZone.height; 

         hLineIndex++, currentPosition.y += targetZone.height / GRID_HORIZONTAL_LINES) {

            ofDrawLine(currentPosition, currentPosition + ofPoint(targetZone.width, 0));
    }

    ofNoFill();
    ofSetLineWidth(GRID_MARGIN_LINE_WIDTH);
    ofDrawRectangle(targetZone);

    ofPopStyle();
}
