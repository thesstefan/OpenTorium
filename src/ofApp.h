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
#include "field_map.h"

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
        /** @brief The Emitter used to create Particle instances. **/
        Emitter emitter_1;

        /** @brief The Field instances which can be modified by the user. **/
        std::vector<std::unique_ptr<Field>> userFields;

        /** @brief The std::list used to store the Particle instances used. **/
        std::list<std::unique_ptr<Particle>> particles;

        /** @brief The time that has passed since the beginning of the program. **/
        float timePassed;

    public:
        /** 
         * @brief The minimum area of a Field. It can't be shrinked if 
         *        it's already smaller.
         *
         * The field can actually have its area smaller than the limit.
         *
         * Actual limit => (MIN_FIELD_AREA + 1) * 0.9.
         */
        constexpr static float MIN_FIELD_AREA = 2500;

        /** @brief The maximum area of a Feild. It can't be enlarged 
         *         if it's already larger.
         *
         * The field can actually have its area bigger than the limit.
         *
         * Actual limit => (MAX_FIELD_AREA - 1) * 1.1;
         */
        constexpr static float MAX_FIELD_AREA = 125000;

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

        void mouseDragged(int x, int y, int button);

        void mouseScrolled(int x, int y, float scrollX, float scrollY);
};
