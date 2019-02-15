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

/** @brief Returns the given vector scaled by the dimensions of the screen. **/
ofVec2f getScreenScaled(const ofVec2f& toScale);

/** @brief Returns the given vector scaled by a given scaling matrix represented as an
 *         ofVec2f(a, b), where the real scaling matrix is [[a, 0], [0, b]].
 */
ofVec2f getScaled(const ofVec2f& toScale, const ofVec2f& scalingMatrix);

/** @brief Extracts a PolylineShape from a @b std::string. **/
PolylineShape *getPolyline(const std::string& polylineString);
