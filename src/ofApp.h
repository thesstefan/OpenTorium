/**
 * @file ofApp.h
 *
 * @brief This file provides the interface of ofApp.
 */

#pragma once

#include <memory>
#include <list>

#include "ofMain.h"
#include "ofPolyline.h"

#include "emitter.h"
#include "field.h"
#include "zone_map.h"
#include "target.h"

/**
 * @class ofApp
 *
 * This class encapsulates the behaviour of the program.
 *
 * An Emitter is used to create Particle instances with various
 * trajectories and speeds which are displayed on the screen.
 */
class ofApp : public ofBaseApp {
    private:
        bool STOP = false;

        /** @brief The Target instances. **/
        ZoneMap<Target> targetMap;

        /** @brief The Emitter used to create Particle instances. **/
        Emitter emitter;

        /** @brief The std::list used to store the Particle instances used. **/
        std::list<std::unique_ptr<Particle>> particles;

        /** @brief The time that has passed since the beginning of the program. **/
        float timePassed;

    public:
        /**
         * @brief Construts ofApp.
         */
        ofApp();

        /**
         * @brief Sets initial properties of the program
         * (e.g. frame rate, background color).
         */
        void setup();

        /**
         * @brief Updates the screen / program.
         *
         * The Emitter and every Particle are updated.
         */
        void update();

        /**
         * @brief Draws the Particle instances.
         *
         * draw() is called for every Particle.
         */
        void draw() override;

        /**
         * @brief Clears out the dead particles in a container.
         *
         * The container might be resized. Iterators are invalidated.
         */
        void clearDeadParticles();

        void keyPressed(int key);
};
