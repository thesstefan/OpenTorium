#include "ofApp.h"

ofApp::ofApp() :
    targetMap(ofGetWidth(), ofGetHeight()),
    fieldsMap(ofGetWidth(), ofGetHeight()),

    parser("level.txt");

    lastDragPosition = ofPoint(0, 0) {}

void ofApp::addObject(const std::variant<Emitter *, Target *, Field *> &object) {
    if (std::holds_alternative<Emitter *>(object))
        emitters.push_back(std::unique_ptr<Emitter>(std::get<Emitter *>(object)));
    else if (std::holds_alternative<Target *>(object))
        targetMap.addZone(std::get<Target *>(object));
    /*
    else if (std::holds_alternative<Field *>(object)) {
        if (std::get<Field *>(object)->movable())
            fields.push_back(std::unique_ptr<Field>(std::get<Field *>(object)));
        else
            fieldMap.addZone(std::get<Field *>(object));
    } else
    */
    else
        throw "Error";
}

void ofApp::setup() {
    bool read = false;

    while (read == false) {
        try {
            addObject(parser.getObject());
        } catch (const std::exception &exception) {
            std::cerr << exception.what() << std::endl;

            read = true;
        }
    }

    ofSetFrameRate(60);
    ofBackground(20, 20, 20);

    ofSetDataPathRoot("data/");
        
    timePassed = ofGetElapsedTimef();
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
