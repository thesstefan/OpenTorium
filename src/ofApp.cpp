#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);

    int width = ofGetWidth();
    int height = ofGetHeight();

    fbo.allocate(width, height, GL_RGB32F_ARB);

    fbo.begin();
    ofBackground(0, 0, 0);
    fbo.end();

    emitter.setup();

    timePassed = ofGetElapsedTimef();
}

void ofApp::update() {
    float time = ofGetElapsedTimef();
    float d_time = ofClamp(time - timePassed, 0, 0.1);

    timePassed = time;

    if (!particle.isAlive())
        particle.setup(emitter);

    particle.update(d_time);
}

void ofApp::draw() {
    ofBackground(0, 0, 0);

    fbo.begin();

    particle.draw();

    fbo.end();

    ofSetColor(255, 255, 255);
    fbo.draw(0, 0);
}
