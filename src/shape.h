/**
 * @file shape.h
 *
 * @brief This module provides the interface of Shape.
 */

#pragma once

#include "ofMain.h"

/**
 * @class Shape
 *
 * This object encapsulates necessary capabilities for every concrete Shape :
 *
 * - Drawing the shape;
 * - Getting a random ofPoint inside the Shape.
 * - Seeing if a ofPoint is inside the Shape.
 */
class Shape {
    public:
        /** @brief Constructs the Shape. **/
        Shape();

        /** @brief Draws the Shape. **/
        virtual void draw() const = 0;

        /** @brief Returns a random ofPoint inside the Shape. **/
        virtual ofPoint getRandomPoint() const = 0;

        /** @brief Returns if an ofPoint is inside the Shape. **/
        virtual bool inside(const ofPoint& point) const = 0;
};

/** 
 * @class Rectangle
 *
 * This concrete class provides a simple Rectangle implementation, coupled
 * with some extra functions inherited from the Shape interface.
 */
class Rectangle : public Shape {
    private:
        /** @brief The top left corner of the Rectangle. **/
        const ofPoint origin;

        /** @brief The width of the Rectangle. **/
        const float width;
        /** @brief The height of the Rectangle. **/
        const float height;

    public:
        /** 
         * @brief Constructs the Rectangle.
         *
         * @param origin -> The top left corner of the Rectangle.
         *
         * @param width -> The width of the Rectangle.
         *
         * @parma height -> The height of the Rectangle.
         */
        Rectangle(const ofPoint& origin, float width, float height);

        /** @brief Draws the Rectangle. **/
        void draw() const;

        /** @brief Returns a random point inside the Rectangle. **/
        ofPoint getRandomPoint() const;

        /** 
         * @brief Checks if a point is inside the Rectangle.
         *
         * @param point -> The point to be checked.
         */
        bool inside(const ofPoint& point) const;
};

/** 
 * @class Ellipse
 *
 * This concrete class provides a simple Ellipse implementation, coupled
 * with some extra functions inherited from the Shape interface.
 */
class Ellipse : public Shape {
    private:
        /** @brief The center of the Ellipse. **/
        const ofPoint center;

        /** @brief The width of the Ellipse. **/
        const float width;
        /** @brief The height of the Ellipse. **/
        const float height;

    public:
        /**
         * @brief Constructs the Ellipse. 
         *
         * @param center -> The center of the Ellipse.
         *
         * @param width -> The width of the Ellipse.
         *
         * @param height -> The height of the Ellipse.
         */
        Ellipse(const ofPoint& center, float width, float height);

        /** @brief Draws the Ellipse. **/
        void draw() const;

        /** @brief Returns a random point inside the Ellipse. **/
        ofPoint getRandomPoint() const;

        /** 
         * @brief Checks if a point is inside the Ellipse. 
         *
         * @param point -> The point to be checked.
         */
        bool inside(const ofPoint& point) const;
};

/**
 * @class PolylineShape
 *
 * This class provides the coupling between the ofPolyline and Shape 
 * interfaces.
 */
class PolylineShape : public ofPolyline, public Shape {
    public:
        /** @brief Constructs the PolylineShapes. */
        PolylineShape();

        /** @brief Draws the PolylineShape. */
        void draw() const;

        /** @brief Returns a random point inside the PolylineShape. **/
        ofPoint getRandomPoint() const;

        /** 
         * @brief Checks if a random point is inside the PolylineShape.
         *
         * @param point -> The point to be checked.
         */
        bool inside(const ofPoint& point) const;
};
