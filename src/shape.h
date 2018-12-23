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
 * - Drawing the Shape.
 * - Getting a random ofPoint inside the Shape.
 * - Seeing if a ofPoint is inside the Shape.
 * - Scaling the Shape.
 * - Moving the Shape.
 */
class Shape {
    public:
        /** @brief Constructs the Shape. **/
        Shape();

        /** @brief Draws the Shape. **/
        virtual void draw() const = 0;

        /** @brief Returns the center of the Shape. **/
        virtual ofPoint getCenter() const = 0;

        /** @brief Returns a random ofPoint inside the Shape. **/
        virtual ofPoint getRandomPoint() const = 0;

        /** @brief Returns if an ofPoint is inside the Shape. **/
        virtual bool inside(const ofPoint &point) const = 0;

        /** @brief Scales the Shape by an amount. **/
        virtual void scale(float amount) = 0;

        virtual void scale(const ofVec2f &screenChangeProportion) = 0;

        /** @brief Translates the Shape. **/
        virtual void translate(const ofPoint &amount) = 0;

        /** @brief Returns the area of the Shape. **/
        virtual float area() const = 0;
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
        ofPoint origin;

        /** @brief The width of the Rectangle. **/
        float width;
        /** @brief The height of the Rectangle. **/
        float height;

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

        /** @brief Returns the center of the Rectangle. **/
        ofPoint getCenter() const;

        /** @brief Returns a random point inside the Rectangle. **/
        ofPoint getRandomPoint() const;

        /** 
         * @brief Checks if a point is inside the Rectangle.
         *
         * @param point -> The point to be checked.
         */
        bool inside(const ofPoint& point) const;

        /** @brief Scales the Rectangle by an amount. **/
        void scale(float amount);

        void scale(const ofVec2f& screenChangeProportion);

        /** @brief Translates the Rectangle to a new position. **/
        void translate(const ofPoint &amount);

        /** @brief Returns the area of the Rectangle. **/
        float area() const;
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
        ofPoint center;

        /** @brief The width of the Ellipse. **/
        float width;
        /** @brief The height of the Ellipse. **/
        float height;

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

        /** @brief Returns the center of the Ellipse. **/
        ofPoint getCenter() const;

        /** @brief Returns a random point inside the Ellipse. **/
        ofPoint getRandomPoint() const;

        /** 
         * @brief Checks if a point is inside the Ellipse. 
         *
         * @param point -> The point to be checked.
         */
        bool inside(const ofPoint& point) const;

        /** @brief Scales the Ellipse by an amount. **/
        void scale(float amount);

        void scale(const ofVec2f& screenChangeProportion);

        /** @brief Moves the Ellipse to a new position. **/
        void translate(const ofPoint &amount);

        /** @brief Returns the area of the Rectangle. **/
        float area() const;
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

        /** @brief Returns the center of the PolylineShape. **/
        ofPoint getCenter() const;

        /** @brief Returns a random point inside the PolylineShape. **/
        ofPoint getRandomPoint() const;

        /** 
         * @brief Checks if a random point is inside the PolylineShape.
         *
         * @param point -> The point to be checked.
         */
        bool inside(const ofPoint& point) const;

        /** @brief Scales the PolylineShape by an amount. **/
        void scale(float amount);

        void scale(const ofVec2f& screenChangeProportion);

        /** @brief Translates the PolylineShape to a new position. **/
        void translate(const ofPoint &amount);

        /** @brief Returns the area of the PolylineShape. **/
        float area() const;
};
