/**
 * @file field.h
 *
 * This module provides the implementation of the Field interface.
 */

#pragma once

#include "ofMain.h"

#include "particle.h"
#include "shape.h"

/**
 * @class Field
 *
 * This class encapsulates an area in which Particles are modified in a specific 
 * way (accelerated / colorized).
 *
 * The area has a defined Shape.
 */
class Field {
    private:
        /** @brief The Shape of the Field. **/
        std::unique_ptr<Shape> shape;

    public:
        /** 
         * @brief Constructs the Field. 
         *
         * @param shape -> The Shape of the Field.
         */
        Field(Shape *shape);

        /**
         * @brief Checks if a point is inside the Field.
         *
         * @param point -> The point to be checked.
         */
        bool inside(const ofPoint &point) const;

        /**
         * @brief Updates a Particle. (If it's inside the Field, it's affected by it).
         *
         * @param particle -> The Particle to be updated.
         */
        virtual void updateParticle(Particle &particle) const = 0;

        /** @brief Draws the Field. **/
        void draw() const;

        /** @brief Scales the Field. **/
        void scale(float amount);

        /** @brief Moves the Field. **/
        void move(const ofPoint &newPosition);

        /** @brief Returns the area of the Field. **/
        float area() const;

        /** @brief Returns the center of the Field. **/
        ofPoint getCenter() const;
};

/**
 * @class ColorField
 *
 * This class provides a Field which colorizes the Particle instances 
 * inside it's shape.
 */
class ColorField : public Field {
    private:
        /** @brief The color to colorize the Particles with. **/
        ofColor color;

    public:
        /**
         * @brief Constructs the ColorField.
         *
         * @param shape -> The Shape of the ColorField.
         *
         * @parma color -> The ofColor of the ColorField.
         */
        ColorField(Shape *shape, const ofColor &color);

        /**
         * @brief Updates a Particle.
         *
         * The Particle is colorized if it's inside the Field.
         *
         * @param particle -> The Particle to be updated.
         */
        virtual void updateParticle(Particle &particle) const override;
};

/**
 * @class ForceField
 *
 * This class provides a Field which applies a force on the
 * Particles inside it.
 */
class ForceField : public Field {
    private:
        /** @brief The force to be applied on the Particles. **/
        ofVec2f force;

    public:
        /** 
         * @brief Constructs the ForceField.
         *
         * @param shape -> The Shape of the ForceField.
         *
         * @parma force -> The force of the ForceField.
         */
        ForceField(Shape *shape, const ofVec2f &force);

        /** 
         * @brief Updates a Particle.
         *
         * The force is applied on the Particle if it's inside the Field.
         *
         * @param particle -> The Particle to be updated.
         */
        virtual void updateParticle(Particle &particle) const override;
};
