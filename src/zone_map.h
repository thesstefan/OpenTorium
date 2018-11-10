/**
 * @file zone_map.h
 *
 * This module provides the ZoneMap interface.
 */

#pragma once

#include "ofMain.h"

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
        /**
         * @brief The bounds of the ZoneMap.
         */
        const ofRectangle bounds;

        /** @brief The zones used. **/
        std::vector<std::unique_ptr<Zone>> zones;

        /** 
         * @brief The pseudo-map used.
         *
         * It consists of various ids for each pixel based of
         * in which Zone is inside.
         */
        std::vector<std::vector<uint8_t>> map;

    public:
        /** 
         * @brief Constructs the ZoneMap.
         *
         * @param width -> The width of the ZoneMap.
         * @param height -> The height of the ZoneMap.
         */
        ZoneMap(unsigned int width, unsigned int height);

        /**
         * @brief Adds a zone to the ZoneMap.
         */
        void addZone(Zone *zone);

        /** 
         * @brief Draws the Zone instances contained by the ZoneMap.
         */
        void draw() const;

        /**
         * @brief Recalculates the static map, based on the currently
         *        available zones.
         */
        void update();

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
ZoneMap<Zone>::ZoneMap(unsigned int width, unsigned int height) 
    : bounds(0, 0, width, height), map(height, std::vector<uint8_t>(width)) {}

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
void ZoneMap<Zone>::update() {
    for (auto &row : map)
        std::fill(row.begin(), row.end(), 0);

    for (size_t zoneIndex = 0; zoneIndex < zones.size(); zoneIndex++)
        for (unsigned int heightIndex = 0; heightIndex < bounds.getHeight(); heightIndex++)
            for (unsigned int widthIndex = 0; widthIndex < bounds.getWidth(); widthIndex++) 
                if (zones[zoneIndex]->inside(ofPoint(widthIndex, heightIndex))) { 
                    if (map[heightIndex][widthIndex] == 0)
                        map[heightIndex][widthIndex] = 1;

                    map[heightIndex][widthIndex] = map[heightIndex][widthIndex] << zoneIndex;
                }

    for (auto &zone : zones)
        zone->update();
}

template <class Zone>
void ZoneMap<Zone>::updateParticle(Particle &particle) {

    const ofPoint &position = particle.getPosition();

    // Skip update if the particle is not inside the zone.
    if (!bounds.inside(position))
        return;

    auto id = map.at(position.y).at(position.x);

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
