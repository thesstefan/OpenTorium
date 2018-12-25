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
        ofRectangle targetZone;

        /**
         * @brief Current progress towards the objective.
         *
         * The progress lies between 0 and 100.
         *
         * The progress is increased / decreased according to the Particle
         * flow received by the Target.
         */
        float progress;

        /**
         * @brief The needed flow rate for the progress to not
         *        decrease
         */
        const float neededFlowRate;

        /** @brief The needed color of the Particles needed by the Target. **/
        const ofColor color;

        /** @brief The number of Particles received by the Target the last frame. **/
        int lastFrameParticles = 0;
        /** @brief The number of Particles received by the Target the current frame. **/
        int currentFrameParticles = 0;

        /** 
         * @brief The number of Particles received by the Target across frames which exceeded
         *        MAX_FRAME_DIFFERENCE.
         */
        int frameOverflow = 0;

        /** @brief The current status of the frame. The sum of differences across the frames. **/
        float flowStatus = 0;

        /** @brief The track to be played while the Target is filled. **/
        ofSoundPlayer track;

        /** @brief The width of the lines of the grid. **/
        float GRID_LINE_WIDTH = 4;
        /** @brief The width of the grid's margin line. **/
        float GRID_MARGIN_LINE_WIDTH = 5;

    public:
        /** @brief The background color of the Target. **/
        static const ofColor BACKGROUND;
        /** @brief The color of the Target's grid. **/
        static const ofColor GRID_LINE_COLOR;
    
        /** @brief The number of horizontal lines in the grid. **/
        constexpr static int GRID_HORIZONTAL_LINES = 10;

        /** 
         * @brief The percent of the needed flow rate which can't be exceeded by the difference 
         *        between two frames. If the percent is exceeded, the excess is used later for a more
         *        balanced distribution in progress changes across frames.
         */
        constexpr static float SMOOTHING_STEP = 15;
        
        /**
         * @brief The maximum number of particles between frames which can be used for the progress
         *        change in an update call. The excess is stored as overflow.
         */
        const float MAX_FRAME_DIFFERENCE;

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
        Target(const ofRectangle &zone, float neededFlowrate, const ofColor &color,
               const std::string &trackPath);

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

        void scale(const ofVec2f& screenDifferenceProportion);

        /** 
         * @brief Draws the contour of the rectangle shaped Target
         *        and the progress filling.
         */
        void draw() const;
};
