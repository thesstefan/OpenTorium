#pragma once

#include "ofMain.h"

class Emitter {
    private:
        ofPoint center;
        ofPoint direction;

        float maxVelocity;
        float lifeTime;

        float size;

    public:
        void setup();

        ofPoint getCenter() const;
        ofPoint getDirection() const;

        float getMaxVelocity() const;
        float getLifeTime() const;

        float getSize() const;
};
