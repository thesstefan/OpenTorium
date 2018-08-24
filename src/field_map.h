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
 * too many calls to Field::inside() which can be expensive.
 *
 * The map also works as a Field container-manager, being able
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
        std::vector<std::vector<char>> map;

    public:
        /** 
         * @brief Constructs the FieldMap.
         *
         * @param width -> The width of the FieldMap.
         *
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
         * @brief Draws the Field instances contained 
         *        by the FieldMap.
         */
        void draw() const;

        /**
         * @brief Updates the FieldMap pixel ids.
         */
        void update();

        /**
         * @brief Updates a Particle.
         *
         * Calls Field::update() on the Particle for each Field
         * which is inside of.
         *
         * @param particle -> The Particle to be updated.
         */
        void updateParticle(std::unique_ptr<Particle> &particle) const;
};
