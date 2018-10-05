#include "level_parser.h"

LevelParser::LevelParser(const std::string &path) {
    levelStream.open(path, std::ifstream::in);

    if ((levelStream.rdstate() & std::ifstream::failbit) != 0)
        std::cerr << "Error opening level file : " << path << std::endl;

    if (levelStream.getline() != "OpenTorium Level File")
        std::cerr << "Error processing file. " << path << " is not a level file." << std::endl;

    levelStream.getline();
}

void LevelParser::identifierCheck(const std::string &identifier) {
    std::string identifierString;
    levelStream >> identifierString;

    if (identifierString != identifier)
        throw "Could not find '" + identifier + "' identifier. Got " + identifierString + " instead.";
}

Shape *getShape(const ofPoint &position, const std::string& shape, const std::string& object) {
    if (object == "emitter") {
        if (shape == "CIRCLE")
            return new Ellipse(position, 200, 200);
        
        if (shape == "SQUARE")
            return new Rectangle(position, 200, 200);

        throw "getShape -> Unknown shape type : " + shape;
    }

    throw "getShape -> Unknown object type : " + object;
}

ofColor getColor(const std::string &colorString) {
    if (colorString == "WHITE")
        return ofColor::white;

    throw "getColor -> Unknown color : " + colorString;
}

Emitter *LevelParser::createEmitter() {
    identifierCheck("position");
    
    ofPoint position;
    levelStream >> position.x >> position.y;

    identifierCheck("shape");

    std::string shapeString;
    levelStream >> shapeString;

    Shape *shape;

    try {
        shape = getShape(position, shapeString, "emitter");
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
    }

    identifierCheck("direction");

    ofVec2f direction;
    levelStream >> direction.x >> direction.y;

    identifierCheck("maxVelocity");

    float maxVelocity;
    levelStream >> maxVelocity;

    identifierCheck("lifeTime");

    float lifeTime;
    levelStream >> lifeTime;

    identifierCheck("spawnRate");

    float spawnRate;
    levelStream >> spawnRate;

    identifierCheck("color");

    std::string colorString;
    levelStream >> colorString;

    ofColor color;
    
    try {
        color = getColor(colorString);
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
    }

    return new Emitter(shape, direction, maxVelocity, lifeTime, spawnRate, color);
}

std::variant<Emitter *, Target *, Field *> 
LevelParser::createObject(const enum ObjectType &type) {
    if (type == ObjectType::Emitter)
        return std::variant<Emitter *, Target *, Field *>(createEmitter());
    
    if (type == ObjectType::Target)
        return std::variant<Emitter *, Target *, Field *>(createTarget());

    if (type == ObjectType::Field)
        return std::variant<Emitter *, Target *, Field *>(createField());

    throw "createObject : Unknown object type";
}

enum ObjectType LevelParser::getObjectType() {
    std::string objectString;

    if (levelStream.rdstate() != std::ios::eofbit)
        std::cerr << "Reached EOF" << std::endl;

    levelStream >> objectString;

    if (levelStream.rdstate() != std::ios::goodbit)
        throw "Error reading file";

    if (objectString == "EMITTER")
        return ObjectType::Emitter;

    if (objectString == "TARGET")
        return ObjectType::Target;

    if (objectString == "FIELD")
        return ObjectType::Field;

    throw "Unknown object type" + objectString;
}

std::variant<Emitter *, Target *, Field *> LevelParser::getObject() {
    enum ObjectType type;
    
    try {
        type = getObjectType();
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;

        throw "STOP";
    }

    std::variant<Emitter *, Target *, Field *> object;

    try {
        object = createObject(type);
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
    }

    return object;
}
