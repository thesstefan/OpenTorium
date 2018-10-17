#include "level_parser.h"
#include "constants.h"
#include "get_functions.h"
#include "exceptions.h"

#include <sstream>

const std::vector<std::string> emitterIdentifiers = 
    { "direction", "maxVelocity", "lifeTime", "spawnRate", "shape", "position", "color" };

const std::vector<std::string> fieldIdentifiers = 
    { "shape", "position", "mobile", "type", "force/color" };

const std::vector<std::string> targetIdentifiers = 
    { "position", "flowRate", "color", "trackPath" };


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

Shape *getShape(const ofPoint &position, const std::string &shape, const enum ObjectType &type) {
    if (type == ObjectType::EmitterType) {
        if (shape == "CIRCLE")
            return new Ellipse(position, EMITTER_CIRCLE_SIZE, EMITTER_CIRCLE_SIZE);
        
        if (shape == "SQUARE")
            return new Rectangle(position, EMITTER_SQUARE_SIZE, EMITTER_SQUARE_SIZE);

        throw UnknownType("getShape -> Unknown shape type : " + shape);
    }

    if (type == ObjectType::FieldType) {
        if (shape == "CIRCLE")
            return new Ellipse(position, FIELD_CIRCLE_SIZE, FIELD_CIRCLE_SIZE);
        
        if (shape == "SQUARE")
            return new Rectangle(position, FIELD_SQUARE_SIZE, FIELD_SQUARE_SIZE);

        throw UnknownType("getShape -> Unknown shape type : " + shape);
    }

    throw UnknownType("getShape -> Can't use getShape for Target");
}

std::variant<Emitter *, Field *, Target *> 
    createObject(const std::map<const std::string, std::string>& data, 
                 const enum ObjectType& type) {

    std::variant<Emitter *, Field *, Target *> object;

    if (type == ObjectType::EmitterType) {
        const ofPoint position = getVec2f(data.at("position"));
        const ofVec2f direction = getVec2f(data.at("direction"));

        const float maxVelocity = std::stof(data.at("maxVelocity"));
        const float lifeTime = std::stof(data.at("lifeTime"));
        const float spawnRate = std::stof(data.at("spawnRate"));

        Shape *shape = getShape(position, data.at("shape"), type);
        const ofColor color = getColor(data.at("color"));

        object = new Emitter(shape, direction, maxVelocity, lifeTime, spawnRate, color);
    } else if (type == ObjectType::FieldType) {
        const ofPoint position = getVec2f(data.at("position"));
        const bool mobile = getBool(data.at("mobile"));

        Shape *shape = getShape(position, data.at("shape"), type);

        if (data.at("type") == "FORCE") {
            const ofVec2f force = getVec2f(data.at("force/color"));

            object = new ForceField(shape, force, mobile);
        } else if (data.at("type") == "COLOR") {
            const ofColor color = getColor(data.at("force/color"));

            object = new ColorField(shape, color, mobile);
        } else
            throw UnknownType("Unknown field type : " + data.at("type"));
    } else if (type == ObjectType::TargetType) {
        const ofPoint position = getVec2f(data.at("position"));
        const ofRectangle zone(position, TARGET_SIZE, TARGET_SIZE);

        const float flowRate = std::stof(data.at("flowRate"));
        const ofColor color = getColor(data.at("color"));

        const std::string trackPath = data.at("trackPath");

        object = new Target(zone, flowRate, color, trackPath);
    } else
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

        std::string value;
        stringStream >> value;

        std::string temp;
        stringStream >> temp;

        if (temp.empty() == false)
            value = value + " " + temp;

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
