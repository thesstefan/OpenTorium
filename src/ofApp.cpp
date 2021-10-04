#include "ofApp.h"

ofApp::ofApp() :
    screenBounds(ofGetWidth(), ofGetHeight()),

    targetMap(ofGetWidth(), ofGetHeight()),
    fieldMap(ofGetWidth(), ofGetHeight()),

    lastDragPosition(0, 0) {
    
    blur.setup(screenBounds.x, screenBounds.y, BLUR_RADIUS, BLUR_SHAPE, 
                                               BLUR_PASSES, BLUR_DOWNSAMPLE);
    ofSetDataPathRoot("data/");
}

void ofApp::loadLevel(const std::string& path) {
    try {
        parser.load(path);
    } catch (const LevelLoadFail& exception) {
        std::cerr << exception.what() << std::endl;

        return;
    }

    bool read = false;

    while (read == false) {
        try {
            addObject(parser.getObject());
        } catch (const EOFReached &exception) {
            read = true;
        } catch (const std::exception &exception) {
            throw;
        }
    }
}

void ofApp::addObject(const std::pair<void *, std::string> &object) {
    if (object.second == "EMITTER")
        emitters.push_back(std::unique_ptr<Emitter>(static_cast<Emitter *>(object.first)));
    else if (object.second == "FIELD") {
        Field *field = static_cast<Field *>(object.first);

        if (field->mobile)
            fields.push_back(std::unique_ptr<Field>(field));
        else
            fieldMap.addZone(field);
    } else if (object.second == "TARGET") {
        targetMap.addZone(static_cast<Target *>(object.first));
    } else
        throw LevelLoadFail("addObject -> Unknown object received");
}

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(20, 20, 20);

    timePassed = ofGetElapsedTimef();

    try {
        loadLevel("data/level.xml");
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
    }

    lastDragField = fields.end();
        
    targetMap.update();
    fieldMap.update();
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

        targetMap.updateObjects();
        fieldMap.updateObjects();

        END = targetMap.ready();

        for (auto &emitter : emitters)
            emitter->update(deltaTime, inserter);

        for (auto& particle : particles) {
            for (auto& field : fields)
                if (field->inside(particle->getPosition()))
                    field->updateParticle(*particle);
            
            particle->update(deltaTime);

            fieldMap.updateParticle(*particle);
            targetMap.updateParticle(*particle);
        }
    }
}

void ofApp::draw() {
    if (UNSUPPORTED_RES)
        drawLowResOverlay();
    else if (END == false) { 
        blur.begin();
            ofBackground(0);
            for (auto& field : fields)
                field->drawInside();

            fieldMap.draw();

            targetMap.draw();

            for (auto& field : fields)
                field->draw();


            for (const auto &particle : particles)
                particle->draw();


        blur.end();
    
        blur.draw();


        for (auto& emitter : emitters)
            emitter->draw();



    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
    } else {
        ofTrueTypeFont font;

        font.load("arial.ttf", 35, true, true);
        font.drawString(std::string("Level Completed"), 20, 50);
    }
}

void ofApp::mousePressed(int x, int y, int button) {
    if (button == 0)
        for (auto field = fields.begin(); field != fields.end(); field++)
            if ((*field)->inside(ofPoint(x, y))) {
                lastDragPosition = ofPoint(x, y);

                lastDragField = field;
            }
}

void ofApp::mouseReleased(int x, int y, int button) {
    lastDragPosition = ofPoint(0, 0);

    lastDragField = fields.end();
}

void ofApp::mouseDragged(int x, int y, int button) {
    if (button == 0)
        if (lastDragPosition != ofPoint(0, 0) && lastDragField != fields.end()) {
            ofPoint center = (*lastDragField)->getCenter();
            
            (*lastDragField)->move(center + ofPoint(x,y) - lastDragPosition);

            lastDragPosition = ofPoint(x, y);
        }
}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {
    for (auto& field : fields)
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

void ofApp::drawLowResOverlay() {
    ofDrawBitmapString(std::string("Unsupported \n Resolution. \n Resize."), 20, 20);
}

void ofApp::windowResized(int w, int h) {
    if (w < MIN_RESOLUTION_WIDTH || h < MIN_RESOLUTION_HEIGHT) {
        UNSUPPORTED_RES = true;

        return;
    } else
        UNSUPPORTED_RES = false;

    const ofVec2f newScreenBounds(w, h);
    const ofVec2f screenChangeProportion = newScreenBounds / screenBounds;

    for (auto& emitter : emitters)
        emitter->scale(screenChangeProportion);

    for (auto& field : fields)
        field->scale(screenChangeProportion);

    for (auto& particle : particles)
        particle->scale(screenChangeProportion);

    targetMap.scale(screenChangeProportion);
    fieldMap.scale(screenChangeProportion);

    screenBounds = newScreenBounds;

    blur.setup(screenBounds.x, screenBounds.y, BLUR_RADIUS, BLUR_SHAPE, 
                                               BLUR_PASSES, BLUR_DOWNSAMPLE);
}
