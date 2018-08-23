#pragma once

#include "ofMain.h"

class Shape {
    public:
        Shape();

        virtual void draw() const = 0;

        virtual ofPoint getRandomPoint() const = 0;
        virtual bool inside(const ofPoint& point) const = 0;
};

class Rectangle : public Shape {
    private:
        // The top left point of the Rectangle.
        const ofPoint origin;

        const float width;
        const float height;

    public:
        Rectangle(const ofPoint& origin, float width, float height);

        void draw() const;

        ofPoint getRandomPoint() const;
        bool inside(const ofPoint& point) const;
};

class Ellipse : public Shape {
    private:
        const ofPoint center;

        const float width;
        const float height;

    public:
        Ellipse(const ofPoint& center, float width, float height);

        void draw() const;

        ofPoint getRandomPoint() const;
        bool inside(const ofPoint& point) const;
};

class PolylineShape : public ofPolyline, public Shape {
    public:
        PolylineShape();

        void draw() const;

        ofPoint getRandomPoint() const;
        bool inside(const ofPoint& point) const;
};
