#include "level_parser.h"
#include "constants.h"
#include "misc.h"
#include "exceptions.h"

#include <sstream>

const std::vector<std::string> emitterIdentifiers = 
    { "direction", "maxVelocity", "lifeTime", "spawnRate", "shape", "position", "color", "size" };

const std::vector<std::string> fieldIdentifiers = 
    { "shape", "position", "mobile", "type", "force/color", "size" };

const std::vector<std::string> targetIdentifiers = 
    { "position", "flowRate", "color", "trackPath", "size" };


const enum ObjectType getObjectType(const std::string &typeString) {
    if (typeString == "EMITTER" || typeString == "emitter")
        return ObjectType::EmitterType;
    
    if (typeString == "FIELD" || typeString == "field")
        return ObjectType::FieldType;

    if (typeString == "TARGET" || typeString == "target")
        return ObjectType::TargetType;

    throw UnknownType("Unknown object type : " + typeString);
}

const std::vector<std::string> getIdentifiers(const enum ObjectType &type) {
    if (type == ObjectType::EmitterType)
        return emitterIdentifiers;

    if (type == ObjectType::FieldType)
        return fieldIdentifiers;

    if (type == ObjectType::TargetType)
        return targetIdentifiers;

    throw UnknownType("getIdentifiers -> UnknownType");
}

Shape *getShape(const ofPoint &position, const std::string &shape, const float width, 
                                                                   const float height) {
    if (shape == "ELLIPSE")
        return new Ellipse(position, width, height);
        
    if (shape == "RECTANGLE")
        return new Rectangle(position, width, height);

    throw UnknownType("getShape -> UnknownType");
}

Emitter *createEmitter(const std::map<const std::string, std::string>& data) {
    const ofPoint position = scaleToScreen(getVec2f(data.at("position")));
    const ofVec2f direction = getVec2f(data.at("direction"));

    const float maxVelocity = std::stof(data.at("maxVelocity"));
    const float lifeTime = std::stof(data.at("lifeTime"));
    const float spawnRate = std::stof(data.at("spawnRate"));

    Shape *shape = nullptr;

    if (data.at("shape") == "POLYLINE")
        shape = getPolyline(data.at("size"));
    else {
        const ofVec2f size = scaleToScreen(getVec2f(data.at("size")));
        
        shape = getShape(position, data.at("shape"), size.x, size.y);
    }

    const ofColor color = getColor(data.at("color"));

    return new Emitter(shape, direction, maxVelocity, lifeTime, spawnRate, color);
}

Field *createField(const std::map<const std::string, std::string>& data) {
    const ofPoint position = scaleToScreen(getVec2f(data.at("position")));
    const bool mobile = getBool(data.at("mobile"));

    Shape *shape = nullptr;

    if (data.at("shape") == "POLYLINE")
        shape = getPolyline(data.at("size"));
    else {
        const ofVec2f size = scaleToScreen(getVec2f(data.at("size")));
        
        shape = getShape(position, data.at("shape"), size.x, size.y);
    }

    if (data.at("type") == "FORCE") {
        const ofVec2f force = getVec2f(data.at("force/color"));

        return new ForceField(shape, force, mobile);
    } 
        
    if (data.at("type") == "COLOR") {
        const ofColor color = getColor(data.at("force/color"));

        return new ColorField(shape, color, mobile);
    }

    throw UnknownType("Unknown field type : " + data.at("type"));
}

Target *createTarget(const std::map<const std::string, std::string>& data) {
    const ofPoint position = scaleToScreen(getVec2f(data.at("position")));

    const ofVec2f size = scaleToScreen(getVec2f(data.at("size")));

    const ofRectangle zone(position, size.x, size.y);

    const float flowRate = std::stof(data.at("flowRate"));
    const ofColor color = getColor(data.at("color"));

    const std::string trackPath = data.at("trackPath");

    return new Target(zone, flowRate, color, trackPath);
}

std::variant<Emitter *, Field *, Target *> 
    createObject(const std::map<const std::string, std::string>& data, 
                 const enum ObjectType& type) {

    std::variant<Emitter *, Field *, Target *> object;

    if (type == ObjectType::EmitterType)
        object = createEmitter(data);
    else if (type == ObjectType::FieldType)
        object = createField(data);
    else if (type == ObjectType::TargetType)
        object = createTarget(data);
    else
        throw UnknownType("Unknown object type");

    return object;
}

ObjectParser::ObjectParser(const std::vector<std::string>& identifiers,
                           std::ifstream& stream,
                           const enum ObjectType type) : stream(stream), type(type) {

    for (const auto& identifier : identifiers)
        data.insert(std::pair<const std::string, std::string>(identifier, ""));
}

void ObjectParser::addValue(const std::string& identifier, const std::string& value) {
    if (data.count(identifier) == 0)
        throw UnknownType("Unknown identifier : " + identifier);

    if (data.find(identifier)->second == "")
        data[identifier] = value;
}

bool ObjectParser::ready() const {
    for (const auto& pair : data) 
        if (pair.second == "")
            return false;

    return true;
}

const std::map<const std::string, std::string> &ObjectParser::parse() {
    std::string line;
    
    while (line.empty())
        std::getline(stream, line);

    while (ready() == false && line.empty() == false) {
        std::stringstream stringStream(line);

        std::string identifier;
        stringStream >> identifier;

        int valuePosition = 0;

        for ( ; isspace(line[valuePosition]); valuePosition++);

        valuePosition += identifier.length();

        for ( ; isspace(line[valuePosition]); valuePosition++);

        std::string value(line.substr(valuePosition));

        addValue(identifier, value);

        std::getline(stream, line);
    }

    return data;
}

LevelParser::LevelParser() {}

void LevelParser::load(const std::string &path) {
    levelStream.open(path, std::ifstream::in);

    if (levelStream.fail())
        throw LevelLoadFail("Error opening level file : " + path);

    std::string levelHeader;
    std::getline(levelStream, levelHeader);

    if (levelHeader != "OpenTorium Level File")
        throw LevelLoadFail("Error processing file. " + path + " is not a level file.");
}

std::variant<Emitter *, Field *, Target *> LevelParser::getObject() {
    std::string typeString;
    levelStream >> typeString;

    if (levelStream.eof())
        throw EOFReached("Reached EOF");

    enum ObjectType type = getObjectType(typeString);

    ObjectParser objectParser(getIdentifiers(type), levelStream, type);

    auto objectData = objectParser.parse();

    return createObject(objectData, type);
}
