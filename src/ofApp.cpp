#include "ofApp.h"

#include "kernel.h"

static constexpr size_t KERNEL_WIDTH = 75;
static constexpr size_t KERNEL_HEIGHT = 75;
static constexpr double KERNEL_SIGMA = 10;

static constexpr GLuint KERNEL_X_BINDING_INDEX = 0;
static constexpr GLuint KERNEL_Y_BINDING_INDEX = 1;

ofApp::ofApp() :
    screenBounds(ofGetWidth(), ofGetHeight()),

    targetMap(ofGetWidth(), ofGetHeight()),
    fieldMap(ofGetWidth(), ofGetHeight()),

    lastDragPosition(0, 0),
    BACKGROUND_COLOR(20, 20, 20) {
    
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

void ofApp::addObject(const std::variant<Emitter *, Field *, Target *> &object) {
    if (std::holds_alternative<Emitter *>(object)) {
        emitters.push_back(std::unique_ptr<Emitter>(std::get<Emitter *>(object)));
    } else if (std::holds_alternative<Field *>(object)) {
        if (std::get<Field *>(object)->mobile)
            fields.push_back(std::unique_ptr<Field>(std::get<Field *>(object)));
        else
            fieldMap.addZone(std::get<Field *>(object));
    } else if (std::holds_alternative<Target *>(object)) {
        targetMap.addZone(std::get<Target *>(object));
    } else
        throw LevelLoadFail("addObject -> Unknown object received");
}

void ofApp::applyBlur() {
    ofTexture screen;
    screen.allocate(screenBounds.x, screenBounds.y, GL_RGBA);

    scene.draw(0, 0);
    screen.loadScreenData(0, 0, screenBounds.x, screenBounds.y);
    ofClear(BACKGROUND_COLOR);

    blurX.begin();
        blurX.setUniformTexture("tex0", screen, 0);

        scene.draw(0, 0);
    blurX.end();

    screen.loadScreenData(0, 0, screenBounds.x, screenBounds.y);
    ofClear(BACKGROUND_COLOR);

    scene.begin();
        blurY.begin();
            blurY.setUniformTexture("tex0", screen, 0);

            screen.draw(0, 0);
        blurY.end();
    scene.end();
}
            
void ofApp::applyGlow() {
    ofTexture screen;
    screen.allocate(screenBounds.x, screenBounds.y, GL_RGBA);

    scene.draw(0, 0);
    screen.loadScreenData(0, 0, screenBounds.x, screenBounds.y);
    ofClear(BACKGROUND_COLOR);

    applyBlur();

    ofFbo glow;
    glow.allocate(screenBounds.x, screenBounds.y, GL_RGBA);

    glow.begin();
        blend.begin();
            blend.setUniformTexture("tex0", screen, 0);
            blend.setUniform4f("backgroundColor", ofFloatColor(BACKGROUND_COLOR));

            scene.draw(0, 0);
        blend.end();
    glow.end();

    scene = glow;
}

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(BACKGROUND_COLOR);

    timePassed = ofGetElapsedTimef();

    scene.allocate(screenBounds.x, screenBounds.y, GL_RGBA);

    try {
        loadLevel("data/level.xml");
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
    }

    lastDragField = fields.end();
        
    targetMap.update();
    fieldMap.update();

    // Load shaders
    blurX.load("blur.vert", "blurX.frag");
    blurY.load("blur.vert", "blurY.frag");
    blend.load("blend.vert", "blend.frag");

    GaussianKernel<float, KERNEL_WIDTH, 1> kernelX(KERNEL_SIGMA);
    kernelX.normalize();
    kernelBufferX.allocate(sizeof(float) * kernelX[0].size(), kernelX[0].data(), GL_STATIC_COPY);

    GaussianKernel<float, KERNEL_HEIGHT, 1> kernelY(KERNEL_SIGMA);
    kernelY.normalize();
    kernelBufferY.allocate(sizeof(float) * kernelY[0].size(), kernelY[0].data(), GL_STATIC_COPY);

    kernelBufferX.bindBase(GL_SHADER_STORAGE_BUFFER, KERNEL_X_BINDING_INDEX);
    kernelBufferY.bindBase(GL_SHADER_STORAGE_BUFFER, KERNEL_Y_BINDING_INDEX);
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
    scene.begin();
        ofBackground(BACKGROUND_COLOR);

        if (UNSUPPORTED_RES)
            drawLowResOverlay();
        else if (END == false) { 
            fieldMap.draw();
            targetMap.draw();

            for (auto& emitter : emitters)
                emitter->draw();

            for (auto& field : fields)
                field->draw();

            for (const auto &particle : particles)
                particle->draw();
        } else {
            ofTrueTypeFont font;

            font.load("arial.ttf", 80, true, true);
            font.drawString(std::string("Game Over"), 150, 400);
        }
    scene.end();

    applyGlow();

    scene.draw(0, 0);
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

    scene.allocate(screenBounds.x, screenBounds.y, GL_RGBA);
}
