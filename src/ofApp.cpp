#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);

    ofBackground(0, 0, 0);

    timePassed = ofGetElapsedTimef();

    ofPoint center(ofGetWidth() / 2, ofGetHeight() / 2);

    shape.addVertex(center);

    shape.addVertex(center + ofPoint(100, 0));
    shape.addVertex(center + ofPoint(100, 50));
    shape.addVertex(center + ofPoint(200, 200));
    shape.addVertex(center + ofPoint(0, 50));

    shape.addVertex(center);

    emitter = std::unique_ptr<Emitter>(new Emitter(shape));
    map = std::unique_ptr<FieldMap>(new FieldMap(ofGetWidth(), ofGetHeight()));

    map->addField(new ColorField(new Ellipse(ofPoint(900, 400), 200.0, 200.0), ofColor::blue));

    map->update();
}

void ofApp::update() {
    float time = ofGetElapsedTimef();
    float deltaTime = ofClamp(time - timePassed, 0, 0.1);

    timePassed = time;

    auto it = particles.begin();
    while (it != particles.end()) {
        if ((*it)->isAlive() == false)
            it = particles.erase(it);
        else
            ++it;
    }
    
    emitter->update(deltaTime, particles);

    for (auto it = particles.begin(); it != particles.end(); it++) {
        map->updateParticle(*it);

        (*it)->update(deltaTime);
    }
}

void ofApp::draw() {
    ofBackground(0, 0, 0);

    ofSetColor(0, 0, 255);

    emitter->draw();
    map->draw();

    for (auto it = particles.begin(); it != particles.end(); it++)
        (*it)->draw();
}
