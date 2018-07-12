/**
 * @file emitter.h
 *
 * @brief This module provides the interface of Emitter.
 */

#pragma once

#include "ofMain.h"

#include "particle.h"

/**
 * @class Emitter
 *
 * This objects creates Particle objects with some common properties at a specified rate.
 *
 * For now, the common properties passed to the Particle instances are the @b direction and 
 * the @b lifeTime.
 *
 * The Emitter is shaped as a square and every Particle object created has the initial
 * @b position inside the square.
 *
 * The Emitter can be updated every frame, creating new Particle instances.
 */
class Emitter {
    private:
        /** @brief The shape of the Emitter. **/
        const ofPolyline shape;

        /** @brief The bounding box of the @b shape of the Emitter. **/
        const ofRectangle boundingBox;

        /** @brief The direction of the Particle motion. **/
        ofPoint direction;

        /** @brief The maximum value of the @b velocity possesed by a Particle. **/
        float maxVelocity;
        /** @brief The maximum @b lifeTime of a Particle. **/
        float lifeTime;

        /** @brief The size of the square-shaped Emitter. **/
        float size;

        /** @brief The rate of Particle spawning. (Particle / second) **/
        float spawnRate;
        /** @brief The remaining part of the number of Particles to create in many
         * update calls.
         *
         * When it reaches 1, a new Particle is born. 
         */
        float spawnCount;

    public:
        /** @brief Constructs the Emitter. */
        Emitter(const ofPolyline& shape);

        /** @brief Creates a Particle.
         *
         * @return std::unique_ptr to the created Particle. 
         */
        std::unique_ptr<Particle> createParticle(const enum ParticleType& type) const;

        /**
         * @brief Updates the Emitter.
         *
         * The Emitter creates more Particles based on how much time has been since 
         * the last update call.
         *
         * @param deltaTime -> The time that has passed since the last update call.
         *
         * @param particles -> The container of Particles used in the app.
         */
        void update(float deltaTime, std::list<std::unique_ptr<Particle>>& particles);
};
