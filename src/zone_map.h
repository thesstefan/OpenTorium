/**
 * @file zone_map.h
 *
 * This module provides the ZoneMap interface.
 */

#pragma once

#include "ofMain.h"
#include "ofPixels.h"

#include "particle.h"

/**
 * @class ZoneMap
 *
 * The class is used to create a map of static zones to avoid
 * checking multiple times if a position is in inside the zone.
 *
 * The map also works as a zone manager, being able
 * to draw the zone and exert its influence on a Particle.
 *
 * A zone is defined as an object which occupies a game space area
 * and influences a Particle if its position is inside the defined
 * area.
 */
template <class Zone>
class ZoneMap {
    private:
        /** @brief The zones used. **/
        std::vector<std::unique_ptr<Zone>> zones;

        /** @brief The map used to match the Zones and the corelated game objects. **/
        ofPixels map;

    public:
        /** 
         * @brief Constructs the ZoneMap.
         *
         * @param width -> The width of the ZoneMap.
         * @param height -> The height of the ZoneMap.
         */
        ZoneMap(unsigned int width, unsigned int height);

        /** @brief Adds a zone to the ZoneMap. */
        void addZone(Zone *zone);

        /** @brief Draws the Zone instances contained by the ZoneMap. */
        void draw() const;

        /** @brief Recalculates the zones, and updates the coresponding objects after a 
         *         window resize.
         */
        void scale(const ofVec2f& screenDifferenceProportion);

        /**
         * @brief Recalculates the static map, based on the currently
         *        available zones.
         */
        void update();

        /** @brief Updates the objects corelated with the known zones. */
        void updateObjects();

        /**
         * @brief Applies the effects of the zones on a Particle.
         *
         * Checks if the particle is in a zone, then applies its effect on
         * the particle.
         *
         * @param particle -> The Particle to be updated.
         */
        void updateParticle(Particle &particle);

        /** @brief Calls ready on each zone. Usually used for Target zones. **/
        bool ready() const;
};

template <class Zone>
ZoneMap<Zone>::ZoneMap(unsigned int width, unsigned int height) {
    update();
}

template <class Zone>
void ZoneMap<Zone>::addZone(Zone *zone) {
    zones.push_back(std::unique_ptr<Zone>(zone));
}

template <class Zone>
void ZoneMap<Zone>::draw() const {
    for (const auto &zone : zones)
        zone->draw();
}

template <class Zone>
void ZoneMap<Zone>::scale(const ofVec2f& screenDifferenceProportion) {
    for (auto &zone : zones)
        zone->scale(screenDifferenceProportion);

    map.resize(ofGetWidth(), ofGetHeight());
}

template <class Zone>
void ZoneMap<Zone>::update() {
    map.clear();

    unsigned char *pixels = new unsigned char[ofGetWidth() * ofGetHeight()];

    for (size_t zoneIndex = 0; zoneIndex < zones.size(); zoneIndex++)
        for (int heightIndex = 0; heightIndex < ofGetHeight(); heightIndex++)
            for (int widthIndex = 0; widthIndex < ofGetWidth(); widthIndex++) 
                if (zones[zoneIndex]->inside(ofPoint(widthIndex, heightIndex))) { 
                    if (pixels[heightIndex * ofGetWidth() + widthIndex] == 0)
                        pixels[heightIndex * ofGetWidth() + widthIndex] = 1;
                        
                    
                    pixels[heightIndex * ofGetWidth() + widthIndex] = pixels[heightIndex * ofGetWidth() + widthIndex] << zoneIndex;
                }

    map.setFromPixels(pixels, ofGetWidth(), ofGetHeight(), 1);
}

template<class Zone>
void ZoneMap<Zone>::updateObjects() {
    for (auto &zone : zones)
        zone->update();
}

template <class Zone>
void ZoneMap<Zone>::updateParticle(Particle &particle) {

    const ofPoint &position = particle.getPosition();

    // Skip update if the particle is not inside the zone.
    if (!position.x || !position.y || position.x > ofGetWidth() || position.y > ofGetHeight())
        return;

    auto id = map[(int)position.y * ofGetWidth() + (int)position.x];

    for (size_t zoneIndex = 0; zoneIndex < zones.size(); zoneIndex++) {
        if (id & 1) 
            zones[zoneIndex]->updateParticle(particle);

        id = id >> 1;
    }
}

template <class Zone>
bool ZoneMap<Zone>::ready() const {
    for (const auto &zone : zones)
        if (zone->ready() == false)
            return false;

    return true;
}
