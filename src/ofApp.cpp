#include "ofApp.h"

#include <iostream>

ofApp::ofApp() :
    targetMap(ofGetWidth(), ofGetHeight()),
    emitter_1(new Ellipse(ofPoint(300, 100), 200.0, 200.0), ofVec2f(1, 0), 100, 5, 10, ofColor::white),
    emitter_2(new Ellipse(ofPoint(300, 600), 200.0, 200.0), ofVec2f(1, 0), 300, 15, 50, ofColor::blue) {}


void ofApp::setup() {
    ofSetFrameRate(60);

    ofBackground(0, 0, 0);

    timePassed = ofGetElapsedTimef();

    targetMap.addZone(new Target(ofRectangle(600, 0, 300, 200), 100, 1.5, ofColor::white));
    targetMap.addZone(new Target(ofRectangle(600, 450, 300, 200), 200, 0.5, ofColor::blue));
}

void ofApp::clearDeadParticles() {
    const auto removeIt = std::remove_if(particles.begin(), particles.end(),
                          [](const std::unique_ptr<Particle> &particle)
                            { return !particle->isAlive(); });

    particles.erase(removeIt, particles.end());
}

void ofApp::update() {
    if (END == false) {
        const float time = ofGetElapsedTimef();
        const float deltaTime = ofClamp(time - timePassed, 0, 0.1);

        timePassed = time;

        clearDeadParticles();

        std::insert_iterator<std::list<std::unique_ptr<Particle>>> 
            inserter(particles, particles.end());

        targetMap.update();

        END = targetMap.ready();

        emitter_1.update(deltaTime, inserter);
        emitter_2.update(deltaTime, inserter);

        for (auto& particle : particles) {
            particle->update(deltaTime);

            targetMap.updateParticle(*particle);
        }
    }
}

void ofApp::draw() {
    ofBackground(0, 0, 0);

    if (END == false) { 
        emitter_1.draw();
        emitter_2.draw();

        targetMap.draw();

        for (const auto &particle : particles)
            particle->draw();
    } else
        ofDrawBitmapString("Game Over", 300, 300);
}

void ofApp::keyPressed(int key) {}
