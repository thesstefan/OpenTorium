#pragma once

#include "ofMain.h"

#include "particle.h"

class Field {
    private:
        ofPoint center;

        int size;

    public:
        Field(const ofPoint& center, int size);

        void update(std::list<std::unique_ptr<Particle>>& particles);

        void draw() const;
};
