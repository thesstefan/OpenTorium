#include "level_parser.h"

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

void LevelParser::identifierCheck(const std::string &identifier) {
    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");

    std::string identifierString;
    levelStream >> identifierString;

    if (identifierString != identifier)
        throw LevelIdentifierFail
            ("Could not find '" + identifier + "' identifier. Got " + identifierString + " instead.");
}

Shape *getShape(const ofPoint &position, const std::string& shape, const std::string& object) {
    if (object == "EMITTER") {
        if (shape == "CIRCLE")
            return new Ellipse(position, 200, 200);
        
        if (shape == "SQUARE")
            return new Rectangle(position, 200, 200);

        throw UnknownType("getShape -> Unknown shape type : " + shape);
    }

    throw UnknownType("getShape -> Unknown object type : " + object);
}

ofColor getColor(const std::string &colorString) {
    if (colorString == "WHITE")
        return ofColor::white;

    throw UnknownType("getColor -> Unknown color : " + colorString);
}

Emitter *LevelParser::createEmitter() {
    try {
        identifierCheck("position");
    } catch (const std::exception& exception) {
        throw;
    }
    
    ofPoint position;

    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");

    levelStream >> position.x;

    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");

    levelStream >> position.y;

    try {
        identifierCheck("shape");
    } catch (const std::exception& exception) {
        throw;
    }

    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");

    std::string shapeString;
    levelStream >> shapeString;

    Shape *shape = nullptr;

    try {
        shape = getShape(position, shapeString, "EMITTER");
    } catch (const std::exception &exception) {
        throw;
    }

    try {
        identifierCheck("direction");
    } catch (const std::exception &exception) {
        throw;
    }

    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");

    ofVec2f direction;
    levelStream >> direction.x;

    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");
    
    levelStream >> direction.y;

    try {
        identifierCheck("maxVelocity");
    } catch (const std::exception &exception) {
        throw;
    }

    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");

    float maxVelocity;
    levelStream >> maxVelocity;

    try {
        identifierCheck("lifeTime");
    } catch (const std::exception &exception) {
        throw;
    }

    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");

    float lifeTime;
    levelStream >> lifeTime;

    try {
        identifierCheck("spawnRate");
    } catch (const std::exception &exception) {
        throw;
    }

    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");

    float spawnRate;
    levelStream >> spawnRate;

    try {
        identifierCheck("color");
    } catch (const std::exception &exception) {
        throw;
    }

    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");

    std::string colorString;
    levelStream >> colorString;

    ofColor color;
    
    try {
        color = getColor(colorString);
    } catch (const std::exception &exception) {
        throw;
    }

    return new Emitter(shape, direction, maxVelocity, lifeTime, spawnRate, color);
}

std::variant<Emitter *, Target *, Field *> 
LevelParser::createObject(const enum ObjectType &type) {
    if (type == ObjectType::EmitterType) {
        std::variant<Emitter *, Target *, Field *> emitter;

        try {
            emitter = createEmitter();
        } catch (const std::exception &exception) {
            throw;
        }

        return emitter;
    }
    /*
    if (type == ObjectType::TargetType)
        return std::variant<Emitter *, Target *, Field *>(createTarget());

    if (type == ObjectType::FieldType)
        return std::variant<Emitter *, Target *, Field *>(createField());
    */

    throw UnknownType("createObject : Unknown object type");
}

enum ObjectType LevelParser::getObjectType() {
    std::string objectString;

    if (levelStream.eof())
        throw EOFReached("Reached EOF");

    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");

    levelStream >> objectString;

    if (objectString == "EMITTER")
        return ObjectType::EmitterType;

    if (objectString == "TARGET")
        return ObjectType::TargetType;

    if (objectString == "FIELD")
        return ObjectType::FieldType;

    throw UnknownType(std::string("Unknown object type : ") + objectString);
}

std::variant<Emitter *, Target *, Field *> LevelParser::getObject() {
    enum ObjectType type;
    
    try {
        type = getObjectType();
    } catch (const std::exception &exception) {
        throw;
    }

    std::variant<Emitter *, Target *, Field *> object;

    try {
        object = createObject(type);
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;

        throw;
    }

    return object;
}

LevelLoadFail::LevelLoadFail(const std::string& message) :
    std::runtime_error(message) {}

const char *LevelLoadFail::what() const noexcept {
    return std::string(std::string("LevelLoadFail : ") + std::runtime_error::what()).c_str();
}

LevelIdentifierFail::LevelIdentifierFail(const std::string& message) :
    std::runtime_error(message) {}

const char *LevelIdentifierFail::what() const noexcept {
    return std::string(std::string("LevelIdentifierFail : ") + std::runtime_error::what()).c_str();
}

EOFReached::EOFReached(const std::string& message) :
    std::runtime_error(message) {}

const char *EOFReached::what() const noexcept {
    return std::string(std::string("LevelLoadFail : ") + std::runtime_error::what()).c_str();
}

UnknownType::UnknownType(const std::string& message) :
    std::runtime_error(message) {}

const char *UnknownType::what() const noexcept {
    return std::string(std::string("UnknownType : ") + std::runtime_error::what()).c_str();
}
