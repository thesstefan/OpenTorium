/**
 * @file ofApp.h
 *
 * @brief This file provides the interface of ofApp.
 */

#pragma once

#include <memory>
#include <list>

#include "ofMain.h"

#include "zone_map.h"
#include "level_parser.h"

#include "emitter.h"
#include "field.h"
#include "target.h"

#include "constants.h"
#include "exceptions.h"

#include "ofxBlur.h"

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
        /** @brief The dimensions of the screen. **/
        ofVec2f screenBounds;

        /** 
         * @brief If END is true, the game ends (the end message is the only 
         * one rendered).
         *
         * That happens when all the Target objectives are achieved.
         */
        bool END = false;

        bool UNSUPPORTED_RES = false;

        /** @brief The Target instances, encapsulated by a ZoneMap. **/
        ZoneMap<Target> targetMap;

        /** @brief The static Field instances, encapsulated by a ZoneMap. **/
        ZoneMap<Field> fieldMap;

        /** @brief The Emitter used to create Particle instances. **/
        std::vector<std::unique_ptr<Emitter>> emitters;

        /** @brief The Field instances which can be modified by the user. **/
        std::vector<std::unique_ptr<Field>> fields;

        /** @brief The std::list used to store the Particle instances used. **/
        std::list<std::unique_ptr<Particle>> particles;

        /** @brief The time that has passed since the beginning of the program. **/
        float timePassed;

        /** @brief The position of the cursor at the last mouseDragged call. **/
        LevelParser parser;

        /** @brief The position of the last drag event. */
        ofPoint lastDragPosition;
        /** @brief The iterator of the last dragged Field. */
        std::vector<std::unique_ptr<Field>>::iterator lastDragField;

        /** @brief Adds an object to the game environment. **/
        void addObject(const std::variant<Emitter *, Field *, Target *> &object);

        /** @brief Loads a level file, given the path. */
        void loadLevel(const std::string &path);

        /** @brief Draws an overlay when the resolution is to small. */
        void drawLowResOverlay();

        /** @brief Blur shader which creates a glow effect. */
        ofxBlur blur;

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

        /** @brief Called when the mouse is pressed. **/
        void mousePressed(int x, int y, int button);

        /** @brief Called when the mouse is releasde. **/
        void mouseReleased(int x, int y, int button);

        /** @brief Called when the mouse is dragged. **/
        void mouseDragged(int x, int y, int button);

        /** @brief Called when the mouse is scrolled. **/
        void mouseScrolled(int x, int y, float scrollX, float scrollY);

        /** @brief Called when the window is resized. **/
        void windowResized(int w, int h);
};
