#include "ofApp.h"

#include <iterator>

ofApp::ofApp() :
    map(ofGetWidth(), ofGetHeight()),

    emitter_1(new Ellipse(ofPoint(300, 100), 200.0, 200.0), ofVec2f(1, 0), 100, 5, 100, ofColor::white),
    emitter_2(new Ellipse(ofPoint(300, 400), 200.0, 200.0), ofVec2f(1, 1), 200, 10, 50, ofColor::green),
    emitter_3(new Ellipse(ofPoint(300, 700), 200.0, 200.0), ofVec2f(1, 0), 300, 2, 300, ofColor::red) {}


void ofApp::setup() {
    ofSetFrameRate(60);

    ofBackground(0, 0, 0);

    timePassed = ofGetElapsedTimef();

    map.addField(new ForceField(new Ellipse(ofPoint(600, 100), 200.0, 200.0), ofVec2f(0, 100)));
    map.addField(new ColorField(new Rectangle(ofPoint(800, 400), 200.0, 200.0), ofColor::blue));

    PolylineShape *poly = new PolylineShape();

    poly->addVertex(700, 600);

    poly->addVertex(750, 650);
    poly->addVertex(800, 700);
    poly->addVertex(750, 700);

    poly->addVertex(700, 600);

    map.addField(new ColorField(poly, ofColor::green));

    map.update();
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

    emitter_1.update(deltaTime, inserter);
    emitter_2.update(deltaTime, inserter);
    emitter_3.update(deltaTime, inserter);

    for (auto& particle : particles) {
        map.updateParticle(particle);

        particle->update(deltaTime);
    }
}

void ofApp::draw() {
    ofBackground(0, 0, 0);

    ofSetColor(0, 0, 255);

    emitter_1.draw();
    emitter_2.draw();
    emitter_3.draw();

    map.draw();

    for (const auto &particle : particles)
        particle->draw();
}

