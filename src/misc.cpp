#include <sstream>

#include "ofAppRunner.h"

#include "misc.h"
#include "exceptions.h"

ofVec2f getScaled(const ofVec2f& toScale, const ofVec2f& scalingMatrix) {
    return toScale * scalingMatrix;
}

ofVec2f getScreenScaled(const ofVec2f& toScale) {
    return getScaled(toScale, ofVec2f(ofGetWidth(), ofGetHeight()));
}

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

ofVec2f getVec2f(const ofXml& xml) {
    auto x_data = xml.getChild("x");
    auto y_data = xml.getChild("y");

    if (x_data && y_data == false)
        throw ExtractError("Could not extract ofVec2f from ofXml.");

    return ofVec2f(x_data.getFloatValue(),
                   y_data.getFloatValue());
}

PolylineShape *getPolyline(const std::string &polylineString) {
    std::stringstream stream(polylineString);

    PolylineShape *shape = new PolylineShape();

    while (stream.eof() == false) {
        ofPoint point;

        stream >> point.x;
        
        if (stream.bad())
            throw ExtractError("Could not create PolylineShape from 'string' : " + polylineString);

        if (stream.eof())
            break;

        stream >> point.y;

        /*
        if (stream.bad() || stream.eof());
            throw ExtractError("Could not create PolylineShape from 'string' : " + polylineString);
        */

        shape->addVertex(ofPoint(getScreenScaled(point)));
    }

    return shape;
}
