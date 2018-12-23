/**
 * @file emitter.h
 *
 * @brief This module provides the interface of Emitter.
 */

#pragma once

#include "ofMain.h"

#include "particle.h"
#include "shape.h"

#include <iterator>

/**
 * @class Emitter
 *
 * This objects creates Particle objects with some common properties at a 
 * specified rate.
 *
 * For now, the common properties passed to the Particle instances are 
 * the @b direction, the @b color and the @b lifeTime.
 *
 * The Emitter has a shape and every Particle object 
 * created has the initial @b position inside the shape.
 *
 * The Emitter can be updated every frame, creating new Particle instances.
 */
class Emitter {
    private:
        /** @brief The shape of the Emitter. **/
        std::unique_ptr<Shape> shape;

        /** @brief The direction of the Particle motion. **/
        const ofVec2f direction;

        /** @brief The maximum value of the @b velocity possesed by a Particle. **/
        const float maxVelocity;

        /** @brief The maximum @b lifeTime of a Particle. **/
        const float lifeTime;

        /** @brief The rate of Particle spawning. (Particles / second) **/
        const float spawnRate;

        /** @brief The color of the created Particles. **/
        const ofColor color;

        /**
         * @brief The remaining part of the number of Particles to create in
         *        many update calls.
         *
         * When it reaches 1, a new Particle is born. 
         */
        float spawnCount;

    public:
        /** @brief Constructs the Emitter. */
        Emitter(Shape *shape, const ofVec2f &direction,
                float maxVelocity, float lifeTime, float spawnRate,
                const ofColor &color);

        /** 
         * @brief Creates a Particle.
         *
         * @return std::unique_ptr to the created Particle. 
         */
        std::unique_ptr<Particle> createParticle(const enum ParticleType &type) const;

        void draw() const;

        void scale(const ofVec2f& screenChangeProportion);

        /**
         * @brief Updates the Emitter.
         *
         * The Emitter creates more Particles based on how much time has been
         * since the last update call.
         *
         * @param deltaTime -> The time that has passed since the last update
         *                     call.
         *
         * @param particles -> The container of Particles used in the app.
         */
        template <class Container>
        void update(const float deltaTime, 
                    std::insert_iterator<Container> &inserter);
};

template <class Container>
void Emitter::update(const float deltaTime,
                     std::insert_iterator<Container> &inserter) {

    spawnCount += deltaTime * spawnRate;

    if (spawnCount >= 1) {
        int spawnNumber = static_cast<int>(spawnCount);

        spawnCount -= spawnNumber;

        for (int index = 0; index < spawnNumber; index++)
            inserter = createParticle(ParticleType::Circle);
    }
}

