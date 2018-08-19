#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);

    ofBackground(0, 0, 0);

    timePassed = ofGetElapsedTimef();

    ofPoint center(ofGetWidth() / 4, ofGetHeight() / 2);

    emitter_1 = std::unique_ptr<Emitter>(new Emitter(new Ellipse(ofPoint(300, 100), 200.0, 200.0)));
    emitter_2 = std::unique_ptr<Emitter>(new Emitter(new Ellipse(ofPoint(300, 400), 200.0, 200.0)));
    emitter_3 = std::unique_ptr<Emitter>(new Emitter(new Ellipse(ofPoint(300, 700), 200.0, 200.0)));

    map = std::unique_ptr<FieldMap>(new FieldMap(ofGetWidth(), ofGetHeight()));

    map->addField(new ColorField(new Ellipse(ofPoint(900, 100), 200.0, 200.0), ofColor::blue));
    map->addField(new ColorField(new Rectangle(ofPoint(800, 400), 200.0, 200.0), ofColor::red));

    PolylineShape *poly = new PolylineShape();

    poly->addVertex(700, 600);

    poly->addVertex(750, 650);
    poly->addVertex(800, 700);
    poly->addVertex(750, 700);

    poly->addVertex(700, 600);

    map->addField(new ColorField(poly, ofColor::green));

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
    
    emitter_1->update(deltaTime, particles);
    emitter_2->update(deltaTime, particles);
    emitter_3->update(deltaTime, particles);

    for (auto& particle : particles) {
        map->updateParticle(particle);

        particle->update(deltaTime);

        // Show-off of particle force interaction.
        // When the particle moves in the right half of the screen
        // it should be pulled in the down-right corner by a force.
        if (particle->getPosition().x > ofGetWidth() / 2)
            particle->applyForce(ofPoint(100, 100));
    }
}

void ofApp::draw() {
    ofBackground(0, 0, 0);

    ofSetColor(0, 0, 255);

    emitter_1->draw();
    emitter_2->draw();
    emitter_3->draw();
    map->draw();

    for (auto it = particles.begin(); it != particles.end(); it++)
        (*it)->draw();
}
