#include "ofApp.h"

ofApp::ofApp() :
    targetMap(ofGetWidth(), ofGetHeight()),
    emitter(new Ellipse(ofPoint(300, 100), 200.0, 200.0), ofVec2f(1, 0), 100, 5, 10, ofColor::blue) {}


void ofApp::setup() {
    ofSetFrameRate(60);

    ofBackground(0, 0, 0);

    timePassed = ofGetElapsedTimef();

    targetMap.addZone(new Target(ofRectangle(600, 0, 300, 200), 200, 1, ofColor::blue));
}

void ofApp::clearDeadParticles() {
    const auto removeIt = std::remove_if(particles.begin(), particles.end(),
                          [](const std::unique_ptr<Particle> &particle)
                            { return !particle->isAlive(); });

    particles.erase(removeIt, particles.end());
}

void ofApp::update() {
    const float time = ofGetElapsedTimef();
    const float deltaTime = ofClamp(time - timePassed, 0, 0.1);

    timePassed = time;

    clearDeadParticles();

    std::insert_iterator<std::list<std::unique_ptr<Particle>>> 
        inserter(particles, particles.end());

    if (STOP == false)
        emitter.update(deltaTime, inserter);

    targetMap.update();

    for (auto& particle : particles) {
        particle->update(deltaTime);

        targetMap.updateParticle(*particle);
    }
}

void ofApp::draw() {
    ofBackground(0, 0, 0);

    emitter.draw();

    targetMap.draw();

    for (const auto &particle : particles)
        particle->draw();
}

void ofApp::keyPressed(int key) {
    if (key == 'p')
        STOP = true;

    if (key == 's')
        STOP = false;
}
