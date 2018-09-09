/**
 * @file target.h
 */

#pragma once

#include "ofMain.h"

#include "particle.h"

/**
 * @class Target
 *
 * Each Target needs a number of Particles to arrive in its area
 * for the objective to be achieved.
 *
 * The time of the last arrival of a Particle in the Target
 * must be less than the Target's required time between Particle arrivals
 * for the progress towards the objective to increase, otherwise decreasing.
 *
 * The Target object is shaped as an Rectangle and it's filling 
 * according to the progress towards the objective.
 *
 * Each Target requires the Particles which arrive in it to have a certain
 * color.
 */
class Target {
    private:
        /** 
         * @brief The area of the Target in which the Particles
         *        must arrive.
         */
        const ofRectangle targetZone;

        /** @brief Current progress towards the objective. **/
        float progress;

        /** 
         * @brief The needed flow rate for the progress to not
         *        decrease
         */
        const float neededFlowRate;

        /** @brief The needed color of the Particles needed by the Target. **/
        const ofColor color;

        /** @brief The time when the last Particle reached the Target. **/
        float lastParticleTime;

    public:
        /**
         * @brief Constructs the Target.
         *
         * @param zone -> The zone of the Target.
         *
         * @param neededFlowRate -> The period of time between Particle arrivals
         *                          in the Target zone needed to keep the progress
         *                          raising.
         *
         * @param color -> The color of the needed Particles.
         */
        Target(const ofRectangle &zone, float neededFlowrate, const ofColor &color);

        /**
         * @brief Checks if a point is inside the Target.
         *
         * @param point -> The point to be checked.
         */
        bool inside(const ofPoint& point) const;

        /**
         * @brief Kills the Particle and registers its time of arrival.
         *
         * @param particle -> The particle to be handled.
         */
        void updateParticle(Particle &particle);

        /** @brief Updates the progress towards the objective. */
        void update();

        /** @brief Checks if the Target objective was achieved. */
        bool ready() const;

        /** 
         * @brief Draws the contour of the rectangle shaped Target
         *        and the progress filling.
         */
        void draw() const;
};
