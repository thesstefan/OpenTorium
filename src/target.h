/**
 * @file target.h
 *
 * This module provides the inteface of Target.
 */

#pragma once

#include "ofMain.h"

#include "particle.h"

/**
 * @class Target
 *
 * This class encapsulates the object in which the Particle
 * instances must be for the game objective to be achieved.
 *
 * The Particles must get to the Target in a constant time 
 * period, or its progress decreases.
 *
 * The Target object is shaped as an Rectangle and it's using
 * progress render.
 *
 * When the progress is maximized, the game is won.
 */
class Target {
    private:
        /** @brief The area of the Target. **/
        const ofRectangle targetZone;

        /** 
         * @brief The needed flow rate for the progress to not
         *        decrease
         */
        const float neededFlowRate;

        /** @brief The time when the last Particle reached the Target. **/
        float lastParticleTime;

        /** @brief The completion rate. **/
        float progress;

    public:
        /**
         * @brief Constructs the Target.
         *
         * @param zone -> The zone of the Target.
         */
        Target(const ofRectangle& zone);

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

        /** @brief Updates the progress and its render. */
        void update();

        /** 
         * @brief Draws the contour of the rectangle shaped Target
         *        and the progress render.
         */
        void draw() const;
};
