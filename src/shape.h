#pragma once

#include "ofMain.h"

class Shape {
    public:
        Shape();

        virtual void draw() const = 0;

        virtual bool inside(const ofPoint& point) const = 0;
};

class Rectangle : public Shape {
    private:
        // The top left point of the Rectangle.
        ofPoint origin;

        float width;
        float height;

    public:
        Rectangle(const ofPoint& origin, float width, float height);

        void draw() const;

        bool inside(const ofPoint& point) const;
};

class Ellipse : public Shape {
    private:
        ofPoint center;

        float width;
        float height;

    public:
        Ellipse(const ofPoint& center, float width, float height);

        void draw() const;

        bool inside(const ofPoint& point) const;
};
