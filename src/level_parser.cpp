#include "level_parser.h"
#include "constants.h"
#include "misc.h"
#include "exceptions.h"

#include <sstream>

const std::vector<std::string> emitterIdentifiers = 
    { "direction", "maxRelativeSpeed", "lifeTime", "spawnRate", "shape", "position", "color", "size", "particleSize" };

const std::vector<std::string> fieldIdentifiers = 
    { "shape", "position", "mobile", "type", "force_or_color", "size" };

const std::vector<std::string> targetIdentifiers = 
    { "position", "flowRate", "color", "trackPath", "size" };


const std::vector<std::string> getIdentifiers(const std::string &type) {
    if (type == "EMITTER")
        return emitterIdentifiers;

    if (type == "FIELD")
        return fieldIdentifiers;

    if (type == "TARGET")
        return targetIdentifiers;

    throw UnknownType("UnknownType : getIdentifiers -> " + type);
}

Shape *getShape(const ofPoint &position, const std::string &shape, const float width, 
                                                                   const float height) {
    if (shape == "ELLIPSE")
        return new Ellipse(position, width, height);
        
    if (shape == "RECTANGLE")
        return new Rectangle(position, width, height);

    throw UnknownType("UnknownType : getShape -> " + shape);
}

Emitter *createEmitter(const ofXml& data) {
    const ofPoint position = getScreenScaled(getVec2f(data.getChild("position")));

    ofVec2f scalingMatrix;
    ofGetWidth() > ofGetHeight() ? scalingMatrix = ofVec2f(1, ofGetWidth() / ofGetHeight()) :
                                   scalingMatrix = ofVec2f(ofGetHeight() / ofGetWidth(), 1);

    const ofVec2f direction = getScaled(getVec2f(data.getChild("direction")), scalingMatrix).getNormalized();

    const float maxRelativeSpeed = data.getChild("maxRelativeSpeed").getFloatValue();
    const float lifeTime = data.getChild("lifeTime").getFloatValue();
    const float spawnRate = data.getChild("spawnRate").getFloatValue();
    const float particleSize = data.getChild("particleSize").getFloatValue();

    Shape *shape = nullptr;

    if (data.getChild("shape").getValue() == "POLYLINE")
        shape = getPolyline(data.getChild("size").getValue());
    else {
        const ofVec2f size = getScreenScaled(getVec2f(data.getChild("size")));
        
        shape = getShape(position, data.getChild("shape").getValue(), size.x, size.y);
    }

    const ofColor color = getColor(data.getChild("color").getValue());

    return new Emitter(shape, direction, maxRelativeSpeed, lifeTime, spawnRate, color, particleSize);
}

Field *createField(const ofXml& data) {
    const ofPoint position = getScreenScaled(getVec2f(data.getChild("position")));
    const bool mobile = data.getChild("mobile").getBoolValue();

    Shape *shape = nullptr;

    if (data.getChild("shape").getValue() == "POLYLINE")
        shape = getPolyline(data.getChild("size").getValue());
    else {
        const ofVec2f size = getScreenScaled(getVec2f(data.getChild("size")));
        
        shape = getShape(position, data.getChild("shape").getValue(), size.x, size.y);
    }

    if (data.getChild("type").getValue() == "FORCE") {
        const ofVec2f force = getScreenScaled(getVec2f(data.getChild("force_or_color")));

        return new ForceField(shape, force, mobile);
    } 
        
    if (data.getChild("type").getValue() == "COLOR") {
        const ofColor color = getColor(data.getChild("force_or_color").getValue());

        return new ColorField(shape, color, mobile);
    }

    throw UnknownType("Unknown field type : " + data.getChild("type").getValue());
}

Target *createTarget(const ofXml& data) {
    const ofPoint position = getScreenScaled(getVec2f(data.getChild("position")));

    const ofVec2f size = getScreenScaled(getVec2f(data.getChild("size")));

    const ofRectangle zone(position, size.x, size.y);

    const float flowRate = data.getChild("flowRate").getFloatValue();
    const ofColor color = getColor(data.getChild("color").getValue());

    const std::string trackPath = data.getChild("trackPath").getValue();

    return new Target(zone, flowRate, color, trackPath);
}

std::variant<Emitter *, Field *, Target *> createObject(const ofXml& objectData) {
    const std::string type = objectData.getAttribute("type").getValue();

    std::variant<Emitter *, Field *, Target *> object;

    if (type == "EMITTER")
        object = createEmitter(objectData);
    else if (type == "FIELD")
        object = createField(objectData);
    else if (type == "TARGET")
        object = createTarget(objectData);
    else
        throw UnknownType("Unknown object type : " + type);

    return object;
}

bool hasRequiredFields(const ofXml& data, const std::vector<std::string>& identifiers) {
    for (const auto& identifier : identifiers) {
        auto child = data.getChild(identifier);

        if (!child) 
            return false;
    }

    return true;
}

LevelParser::LevelParser() {}

void LevelParser::load(const std::string &path) {
    ofXml level;
    level.load(path);

    if (!level)
        throw LevelLoadFail("Error opening level file : " + path);

    auto header = level.getChild("header");

    if (!header)
        throw LevelLoadFail("Could not find header in file : " + path);
    else if (header.getValue() != "OpenTorium Level File")
        throw LevelLoadFail("Error processing file. " + path + " is not a level file.");

    auto data = level.getChild("data");

    if (!data)
        throw LevelLoadFail("Could not process game data in file : " + path);

    currentObjectData = data.getFirstChild();
}

std::variant<Emitter *, Field *, Target *> LevelParser::getObject() {
    if (!currentObjectData)
        throw EOFReached("Reached EOF");

    if (hasRequiredFields(currentObjectData, getIdentifiers(currentObjectData.getAttribute("type").getValue())) == false)
        throw LevelLoadFail("Could not process object data in level file.");

    auto object = createObject(currentObjectData);

    currentObjectData = currentObjectData.getNextSibling();

    return object;
}
