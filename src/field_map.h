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
        /** @brief The width of the FieldMap. **/
        const unsigned int width;
        /** @brief The height of the FieldMap. **/
        const unsigned int height;

        /** @brief The Field instances used. **/
        std::vector<std::unique_ptr<Field>> fields;

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
         *
         * @param field -> The Field to be added.
         */
        void addField(Field *field);

        /** 
         * @brief Draws the Field instances contained by the FieldMap.
         */
        void draw() const;

        /**
         * @brief Updates the FieldMap pixel ids.
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
