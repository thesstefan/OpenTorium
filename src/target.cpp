#include "target.h"

#include "constants.h"

#include <iostream>

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
    ofSetColor(TARGET_CONSTANTS::BACKGROUND);
    ofDrawRectangle(targetZone);

    // Draw the progress rectangle.
    ofSetColor(color);

    ofRectangle progressRender = ofRectangle(targetZone.x, targetZone.y, targetZone.width, 1);
    progressRender.scaleHeight(ofMap(progress, 0, 100, 1, targetZone.height));

    ofDrawRectangle(progressRender);

    // Draw the grid.
    ofSetColor(TARGET_CONSTANTS::GRID_LINE_COLOR);
    ofSetLineWidth(TARGET_CONSTANTS::GRID_LINE_WIDTH);

    // Draw the horizontal lines of the grid.
    ofPoint currentPosition(targetZone.x, targetZone.y);
    for (int hLineIndex = 0; 
         hLineIndex < TARGET_CONSTANTS::GRID_HORIZONTAL_LINES
         && currentPosition.y < targetZone.y + targetZone.height; 

         hLineIndex++, currentPosition.y += targetZone.height / TARGET_CONSTANTS::GRID_HORIZONTAL_LINES) {

            ofDrawLine(currentPosition, currentPosition + ofPoint(targetZone.width, 0));
    }

    // Draw the vertical lines of the grid.
    currentPosition = ofPoint(targetZone.x, targetZone.y);
    for (int vLineIndex = 0; 
         vLineIndex < TARGET_CONSTANTS::GRID_VERTICAL_LINES 
         && currentPosition.x < targetZone.x + targetZone.width; 

         vLineIndex++, currentPosition.x += targetZone.width / TARGET_CONSTANTS::GRID_VERTICAL_LINES) {

            ofDrawLine(currentPosition, currentPosition + ofPoint(0, targetZone.height));
    }

    ofNoFill();
    ofDrawRectRounded(targetZone, TARGET_CONSTANTS::GRID_RECT_RADIUS);

    ofPopStyle();
}
