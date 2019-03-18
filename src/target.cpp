#include "target.h"

const ofColor Target::BACKGROUND(60, 60, 60);
const ofColor Target::GRID_LINE_COLOR(25, 25, 25);

Target::Target(const ofRectangle &zone, float neededFrameParticles, const ofColor &color,
               const std::string &trackPath = "") :
    targetZone(zone), 
    neededFrameParticles(neededFrameParticles), 
    color(color) {
        track.load(trackPath);

        if (track.isLoaded() == false)
            throw "Could not load track : " + trackPath;

        track.setLoop(true);

        track.play();
        track.setPaused(true);

        progress = 0;
}

bool Target::inside(const ofPoint& point) const {
    return point.x > targetZone.x && point.x < targetZone.x + targetZone.width &&
           point.y > targetZone.y && point.y < targetZone.y + targetZone.height;
}

void Target::update() {
    static int decreaseDelay = 0;
    static int increaseDelay = 0;

    if (currentFrameParticles < neededFrameParticles) {
        if (decreaseDelay == 0) {
            progress -= PROGRESS_DECREASE_STEP;

            decreaseDelay = DECREASE_DELAY;
        } else
            decreaseDelay--;
    } else {
        if (increaseDelay)
            increaseDelay--;
        else {
            const float progressChange = ofMap(currentFrameParticles - neededFrameParticles,
                                               0, currentFrameParticles,
                                               0, MAX_PROGRESS_CHANGE);

            increaseDelay = ofMap(progressChange, 0, MAX_PROGRESS_CHANGE, 0, MAX_DELAY_INCREASE);

            progress += progressChange;
        }
    }

    progress = ofClamp(progress, 0, 100);

    float volume = ofMap(progress, 0, 100, 0.1, 1);

    track.setVolume(volume);

    if (progress == 0)
        track.setPaused(true);

    currentFrameParticles = 0;
}

bool Target::ready() const {
    return progress == 100;
}

void Target::updateParticle(Particle &particle) {
    if (particle.getColor() != color)
        return;

    currentFrameParticles++;

    if (track.isPlaying() == false && progress >= 5)
        track.setPaused(false);
}

void Target::scale(const ofVec2f& screenDifferenceProportion) {
    targetZone.setPosition(targetZone.getPosition() * ofVec3f(screenDifferenceProportion.x,
                                                              screenDifferenceProportion.y,
                                                              1));

    targetZone.setWidth(targetZone.width * screenDifferenceProportion.x);
    targetZone.setHeight(targetZone.height * screenDifferenceProportion.y);

    GRID_LINE_WIDTH *= screenDifferenceProportion.y;
    GRID_MARGIN_LINE_WIDTH *= screenDifferenceProportion.y;
}

void Target::drawProgress() const {
    ofPushStyle();

    ofFill();
    ofSetColor(color);

    ofRectangle progressRender = ofRectangle(targetZone.x, targetZone.y + targetZone.height,
                                             targetZone.width, -(targetZone.height / GRID_HORIZONTAL_LINES));

    const float heightScale = ofMap(progress, 0, 100, 1, GRID_HORIZONTAL_LINES);

    progressRender.scaleHeight(floor(heightScale));

    ofDrawRectangle(progressRender);

    const float nextBarProgress = heightScale - floor(heightScale);

    ofRectangle nextBar = ofRectangle(targetZone.x, 
                                      targetZone.y + (targetZone.height / GRID_HORIZONTAL_LINES) * 
                                                     (GRID_HORIZONTAL_LINES - floor(heightScale) + 1),
                                      targetZone.width, -(targetZone.height / GRID_HORIZONTAL_LINES));

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    const float barAlpha = ofMap(nextBarProgress, 0, 1, 0, 255);

    ofSetColor(color.r, color.g, color.b, barAlpha);

    ofDrawRectangle(nextBar);

    ofDisableBlendMode();
    
    ofPopStyle();
}

void Target::drawGrid() const {
    ofPushStyle();

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


void Target::draw() const {
    ofPushStyle();

    // Draw the background of the Target.
    ofSetColor(BACKGROUND);
    ofDrawRectangle(targetZone);

    drawProgress();
    drawGrid();

    ofPopStyle();
}
