#pragma once

#include <string>

#include "ofColor.h"
#include "ofVec2f.h"
#include "ofPoint.h"

#include "shape.h"

/** @brief Extracts a @b bool from a @b std::string. **/
bool getBool(const std::string &boolString);

/** @brief Extracts an @b ofColor from a @b std::string. **/
ofColor getColor(const std::string &colorString);

/** @brief Extracts an @b ofVec2f from a @b std::string. **/
ofVec2f getVec2f(const std::string &vecString);

/** @brief Scales a normalized point to the screen. **/
ofPoint scaleToScreen(const ofPoint& toScale);

/** @brief Extracts a PolylineShape from a @b std::string. **/
PolylineShape *getPolyline(const std::string& polylineString);
