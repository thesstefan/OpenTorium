/**
 * @file field_map.h
 *
 * This module provides the FieldMap interface.
 */

#pragma once

#include "ofMain.h"

#include "field.h"

/**
 * @class FieldMap
 *
 * The class is used to create a map of static fields to avoid
 * checking multiple times if a position is in a field.
 *
 * The map also works as a Field manager, being able
 * to draw the fields and using them to update a Particle.
 */
class FieldMap {
    private:
        /**
         * @brief The bounds of the field map
         */
        const ofRectangle bounds;

        /** @brief The Field instances used. **/
        std::vector<std::unique_ptr<const Field>> fields;

        /** 
         * @brief The pseudo-map used.
         *
         * It consists of various ids for each pixel based of
         * in which Fields is inside.
         */
        std::vector<std::vector<uint8_t>> map;

    public:
        /** 
         * @brief Constructs the FieldMap.
         *
         * @param width -> The width of the FieldMap.
         * @param height -> The height of the FieldMap.
         */
        FieldMap(unsigned int width, unsigned int height);

        /**
         * @brief Adds a Field to the FieldMap.
         */
        void addField(const Field *field);

        /** 
         * @brief Draws the Field instances contained by the FieldMap.
         */
        void draw() const;

        /**
         * @brief Recalculates the static field map, based on the currently
         *        available fields.
         */
        void update();

        /**
         * @brief Applies the effects of the fields on a particle.
         *
         * Checks if the particle is in a field, then applies its effect on
         * the particle.
         *
         * @param particle -> The Particle to be updated.
         */
        void updateParticle(Particle &particle) const;
};
