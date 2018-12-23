#include <sstream>

#include "ofAppRunner.h"

#include "misc.h"
#include "exceptions.h"

bool getBool(const std::string &boolString) {
    if (boolString == "TRUE" || boolString == "true" || boolString == "1")
        return true;

    if (boolString == "FALSE" || boolString == "false" || boolString == "0")
        return false;

    throw ExtractError("Could not extract 'bool' from 'string' : " + boolString);
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

    throw UnknownType("Unknown color  : " + colorString);
}

ofVec2f getVec2f(const std::string &vecString) {
    std::stringstream stream(vecString);

    ofVec2f vec2f;

    stream >> vec2f.x >> vec2f.y;

    return vec2f;
}

ofPoint scaleToScreen(const ofPoint& toScale) {
    return toScale * ofPoint(ofGetWidth(), ofGetHeight());
}
