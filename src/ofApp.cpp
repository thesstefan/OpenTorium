#include "ofApp.h"

ofApp::ofApp() :
    targetMap(ofGetWidth(), ofGetHeight()),
    emitter_1(new Rectangle(ofPoint(100, 100), 75.0, 75.0), ofVec2f(1, 0), 150, 5, 50, ofColor::white),
    emitter_2(new Rectangle(ofPoint(500, 200), 75.0, 75.0), ofVec2f(0, 1), 100, 8, 100, ofColor::blue) {

    lastDragPosition = ofPoint(0, 0);
}

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(20, 20, 20);

    ofSetDataPathRoot("data/");
        
    timePassed = ofGetElapsedTimef();

    targetMap.addZone(new Target(ofRectangle(700, 300, 70, 70), 50, ofColor::white, "track_1.mp3"));
    targetMap.addZone(new Target(ofRectangle(500, 600, 70, 70), 70, ofColor::green, "track_2.mp3"));

    userFields.push_back(std::make_unique<ForceField>
            (new Ellipse(ofPoint(500, 100), 100, 100), ofVec2f(0, 100)));

    userFields.push_back(std::make_unique<ColorField>
            (new Ellipse(ofPoint(200, 200), 100, 100), ofColor::green));
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
            for (auto& field : userFields)
                if (field->inside(particle->getPosition()))
                    field->updateParticle(*particle);
            
            particle->update(deltaTime);
            targetMap.updateParticle(*particle);
        }
    }
}

void ofApp::draw() {
    if (END == false) { 
        targetMap.draw();

//        emitter_1.draw();

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
