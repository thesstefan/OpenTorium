#include "ofApp.h"

ofApp::ofApp() :
    targetMap(ofGetWidth(), ofGetHeight()),
    emitter(new Ellipse(ofPoint(300, 100), 200.0, 200.0), ofVec2f(1, 0), 100, 5, 100, ofColor::blue) {

    lastDragPosition = ofPoint(0, 0);
}

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);

    ofSetDataPathRoot("data/");
        
    timePassed = ofGetElapsedTimef();

    targetMap.addZone(new Target(ofRectangle(600, 450, 300, 200), 0.5, ofColor::blue, "track.mp3"));

    userFields.push_back(std::make_unique<ForceField>
            (new Rectangle(ofPoint(300, 300), 200, 200), ofVec2f(0, 100)));
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

        emitter.update(deltaTime, inserter);

        for (auto& particle : particles) {
            for (auto& field : userFields)
                if (field->inside(particle->getPosition()))
                    field->updateParticle(*particle);
            
            particle->update(deltaTime);
            targetMap.updateParticle(*particle);
        }
    }
}

void ofApp::draw() {
    ofBackground(0, 0, 0);

    if (END == false) { 
        targetMap.draw();

        emitter.draw();

        for (auto& field : userFields)
            field->draw();

        for (const auto &particle : particles)
            particle->draw();
    } else {
        ofTrueTypeFont font;

        font.load("arial.ttf", 80, true, true);
        font.drawString(std::string("Game Over"), 150, 400);
    }
}

void ofApp::mousePressed(int x, int y, int button) {
    if (button == 0)
        for (auto& field : userFields)
            if (field->inside(ofPoint(x, y)))
                lastDragPosition = ofPoint(x, y);
}

void ofApp::mouseReleased(int x, int y, int button) {
    lastDragPosition = ofPoint(0, 0);
}

void ofApp::mouseDragged(int x, int y, int button) {
    if (button == 0)
        for (auto& field : userFields)
            if (field->inside(ofPoint(x, y)) && lastDragPosition != ofPoint(0, 0)) {
                ofPoint center = field->getCenter();

                field->move(center + ofPoint(x,y) - lastDragPosition);

                lastDragPosition = ofPoint(x, y);
            }
}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {
    for (auto& field : userFields)
        if (field->inside(ofPoint(x, y))) {
            if (scrollY == 1) {
                if (field->area() < MAX_FIELD_AREA)
                    field->scale(1.1);
            } else if (scrollY == -1) {
                if (field->area() > MIN_FIELD_AREA)
                    field->scale(0.9);
            }
        }
}
