#pragma once

#include "ofMain.h"

#include "particle.h"
#include "shape.h"

class Field {
    private:
        const std::unique_ptr<Shape> shape;

    public:
        Field(Shape *shape);

        bool inside(const ofPoint &point) const;

        virtual void updateParticle(std::unique_ptr<Particle>& particle) const = 0;

        void draw() const;
};

class ColorField : public Field {
    private:
        ofColor color;

    public:
        ColorField(Shape *shape, const ofColor& color);

        void updateParticle(std::unique_ptr<Particle>& particle) const;
};

class ForceField : public Field {
    private:
        ofVec2f force;

    public:
        ForceField(Shape *shape, const ofVec2f& force);

        void updateParticle(std::unique_ptr<Particle>& particle) const;
};
