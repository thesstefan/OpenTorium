/**
 * @file particle.h
 *
 * @brief This module provides the interface of a Particle.
 */

#pragma once

#include "ofMain.h"

/** @brief Defines the existing Particle types. */
enum ParticleType { 
    /** @brief The type of CircleParticle. */
    Circle 
};

/**
 * @class Particle
 *
 * @brief This class encapsulates the properties and the behaviour of a small
 * object, usually used to create bigger ones.
 *
 * The Particle has a known @b position and @b velocity, used to create a motion pattern.
 *
 * The object also has a maximum @b lifeTime. When its @b time of living equals the maximum @b lifeTime,
 * the Particle is said to be @b dead (until then being @b alive).
 *
 * When a Particle is @b dead, it can't pe updated and drawn.
 *
 * The Particle can be @b updated every frame, its @b position being modified using the @b velocity 
 * and the <b>time between frames</b>. When the object is updated, its time of living is updated.
 * If the new time exceeds the maximum lifeTime, the Particle is marked as @b dead.
 *
 * The Particle also has a color and a size.
 */
class Particle {
    protected:
        /** @brief The position of the Particle. **/
        ofPoint position;
        /** @brief The velocity of the Particle. **/
        ofPoint velocity;

        /** @brief The size of the Particle. **/
        const int size;
        /** @brief The color of the Particle. **/
        const ofColor color;

        /** @brief The time passed since the Particle was created. **/
        float time;
        /** @brief The time at which the Particle is marked as @b dead. **/
        const float lifeTime;

        /** @brief The alive / dead marker. **/
        bool live;

    public:
        /** 
         * @brief Constructs the Particle, using several properties.
         *
         * @param size -> The size of the Particle.
         *
         * @param color -> The color of the Particle.
         *
         * @param position -> The position of the Particle.
         *
         * @param velocity -> The velocity of the Particle.
         *
         * @param lifeTime -> The maximum lifeTime of the Particle.
         */
        Particle(int size, const ofColor& color, const ofPoint& position, const ofPoint& velocity, float lifeTime);

        /** @brief Updates the Particle.
         *
         * The @b position is updated using the @b velocity of the Particle and @p deltaTime.
         *
         * The @b living time of the Particle is updated. The Particle is marked as @b dead
         * if the living time exceeds the maximum @b lifeTime.
         *
         * @param deltaTime -> The time passed since the last update.
         */
        void update(float deltaTime);

        /** @brief Draws the Particle. **/
        virtual void draw() const = 0;

        /** 
         * @brief Checks if the Particle is @b alive.
         *
         * @return @b true if the Paticle is @b alive, false otherwise.
         */
        bool isAlive() const;
};

/**
 * @class CircleParticle
 *
 * @brief This class represents a circle-shaped Particle.
 */
class CircleParticle : public Particle {
    public:
        /** 
         * @brief Constructs the CircleParticle, using several properties.
         *
         * @param size -> The size of the Particle.
         *
         * @param color -> The color of the Particle.
         *
         * @param position -> The position of the Particle.
         *
         * @param velocity -> The velocity of the Particle.
         *
         * @param lifeTime -> The maximum lifeTime of the Particle.
         */
        CircleParticle(int size, const ofColor& color, const ofPoint& position, const ofPoint& velocity, int lifeTime);

        /**
         * @brief Draws the CircleParticle.
         *
         * The Particle is drawn as a circle, using the size, color and position of the CircleParticle.
         */
        void draw() const;
};
