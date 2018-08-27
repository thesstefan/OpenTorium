#include "ofApp.h"

#include <iterator>

ofApp::ofApp() :
    target(ofRectangle(600, 0, 300, 200)),
    emitter(new Ellipse(ofPoint(300, 100), 200.0, 200.0), ofVec2f(1, 0), 100, 5, 100, ofColor::white) {}


void ofApp::setup() {
    ofSetFrameRate(60);

    ofBackground(0, 0, 0);

    timePassed = ofGetElapsedTimef();
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

    target.update();

    clearDeadParticles();

    std::insert_iterator<std::list<std::unique_ptr<Particle>>> 
        inserter(particles, particles.end());

    if (STOP == false)
        emitter.update(deltaTime, inserter);

    for (auto& particle : particles) {
        particle->update(deltaTime);

        if (target.inside(particle->getPosition()))
            target.updateParticle(*particle);
    }
}

void ofApp::draw() {
    ofBackground(0, 0, 0);

    emitter.draw();

    target.draw();

    for (const auto &particle : particles)
        particle->draw();
}

void ofApp::keyPressed(int key) {
    if (key == 'p')
        STOP = true;

    if (key == 's')
        STOP = false;
}
