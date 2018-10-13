#include "level_parser.h"
#include "constants.h"

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

    if (identifierString != identifier) {
        throw LevelIdentifierFail
            ("Could not find '" + identifier + "' identifier. Got '" + identifierString + "' instead.");
    }
}

Shape *getShape(const ofPoint &position, const std::string& shape, const std::string& object) {
    if (object == "EMITTER") {
        if (shape == "CIRCLE")
            return new Ellipse(position, EMITTER_CIRCLE_SIZE, EMITTER_CIRCLE_SIZE);
        
        if (shape == "SQUARE")
            return new Rectangle(position, EMITTER_SQUARE_SIZE, EMITTER_SQUARE_SIZE);

        throw UnknownType("getShape -> Unknown shape type : " + shape);
    }

    if (object == "FIELD") {
        if (shape == "CIRCLE")
            return new Ellipse(position, FIELD_CIRCLE_SIZE, FIELD_CIRCLE_SIZE);
        
        if (shape == "SQUARE")
            return new Rectangle(position, FIELD_SQUARE_SIZE, FIELD_SQUARE_SIZE);

        throw UnknownType("getShape -> Unknown shape type : " + shape);
    }

    throw UnknownType("getShape -> Unknown object type : " + object);
}

ofColor getColor(const std::string &colorString) {
    if (colorString == "WHITE")
        return ofColor::white;

    if (colorString == "BLUE")
        return ofColor::blue;

    if (colorString == "RED")
        return ofColor::red;

    if (colorString == "GREEN")
        return ofColor::green;

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
    } catch (const std::runtime_error &exception) {
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

Field *LevelParser::createField() {
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
        shape = getShape(position, shapeString, "FIELD");
    } catch (const std::exception &exception) {
        throw;
    }

    try {
        identifierCheck("mobile");
    } catch (const std::exception& exception) {
        throw;
    }

    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");

    bool mobile;
    std::string mobileString;

    levelStream >> mobileString;

    if (mobileString == "FALSE" || mobileString == "0")
        mobile = false;
    else if (mobileString == "TRUE" || mobileString == "1")
        mobile = true;
    else
       throw LevelLoadFail("Expected 'FALSE' / 'TRUE'. Got '" + mobileString + "' instead."); 

    try {
        identifierCheck("type");
    } catch (const std::exception& exception) {
        throw;
    }

    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");

    std::string fieldType;
    levelStream >> fieldType;

    if (fieldType == "FORCE") {
        try {
            identifierCheck("force");
        } catch (const std::exception& exception) {
            throw;
        }

        if (levelStream.good() == false)
            throw LevelLoadFail("Failed to read from stream.");

        ofVec2f force;

        levelStream >> force.x;

        if (levelStream.good() == false)
            throw LevelLoadFail("Failed to read from stream.");

        levelStream >> force.y;

        return new ForceField(shape, force, mobile);
    } 

    if (fieldType == "COLOR") {
        try {
            identifierCheck("color");
        } catch (const std::exception& exception) {
            throw;
        }

        if (levelStream.good() == false)
            throw LevelLoadFail("Failed to read from stream.");

        std::string colorString;
        levelStream >> colorString;

        ofColor color;

        try {
            color = getColor(colorString);
        } catch (const std::exception& exception) {
            throw;
        }

        return new ColorField(shape, color, mobile);
    }

    throw LevelLoadFail("Unknown field type : " + fieldType);
}

Target *LevelParser::createTarget() {
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

    const ofRectangle zone(position, TARGET_SIZE, TARGET_SIZE);

    try {
        identifierCheck("flowRate");
    } catch (const std::exception& exception) {
        throw;
    }

    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");

    float flowRate;
    levelStream >> flowRate;

    try {
        identifierCheck("color");
    } catch (const std::exception& exception) {
        throw;
    }

    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");

    std::string colorString;
    levelStream >> colorString;

    ofColor color;

    try {
        color = getColor(colorString);
    } catch (const std::exception& exception) {
        throw;
    }

    try {
        identifierCheck("trackPath");
    } catch (const std::exception& exception) {
        throw;
    }

    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");

    std::string path;
    levelStream >> path;

    return new Target(zone, flowRate, color, path);
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

    if (type == ObjectType::FieldType) {
        std::variant<Emitter *, Target *, Field *> field;

        try {
            field = createField();
        } catch (const std::exception &exception) {
            throw;
        }

        return field;
    }

    if (type == ObjectType::TargetType) {
        std::variant<Emitter *, Target *, Field *> target;

        try {
            target = createTarget();
        } catch (const std::exception &exception) {
            throw;
        }

        return target;
    }

    throw UnknownType("createObject : Unknown object type");
}

enum ObjectType LevelParser::getObjectType() {
    std::string objectString;

    if (levelStream.good() == false)
        throw LevelLoadFail("Failed to read from stream.");

    levelStream >> objectString;

    if (levelStream.eof())
        throw EOFReached("Reached EOF");

    if (objectString == "EMITTER")
        return ObjectType::EmitterType;

    if (objectString == "TARGET")
        return ObjectType::TargetType;

    if (objectString == "FIELD")
        return ObjectType::FieldType;

    throw UnknownType("getObjectType -> Unknown object type : " + objectString);
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
        throw;
    }

    return object;
}

LevelLoadFail::LevelLoadFail(const std::string& message) :
    std::runtime_error(message) {}

const char *LevelLoadFail::what() const noexcept {
    return std::runtime_error::what();
}

LevelIdentifierFail::LevelIdentifierFail(const std::string& message) :
    std::runtime_error(message) {}

const char *LevelIdentifierFail::what() const noexcept {
    return std::runtime_error::what();
}

EOFReached::EOFReached(const std::string& message) :
    std::runtime_error(message) {}

const char *EOFReached::what() const noexcept {
    return std::runtime_error::what();
}

UnknownType::UnknownType(const std::string& message) :
    std::runtime_error(message) {}

const char *UnknownType::what() const noexcept {
    return std::runtime_error::what();
}
