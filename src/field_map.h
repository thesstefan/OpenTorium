#pragma once

#include "ofMain.h"

#include "field.h"

class FieldMap {
    private:
        const unsigned int width;
        const unsigned int height;

        std::vector<std::unique_ptr<Field>> fields;

        std::vector<std::vector<char>> map;

    public:
        FieldMap(unsigned int width, unsigned int height);

        void addField(Field *field);

        void draw() const;

        void update();

        void updateParticle(std::unique_ptr<Particle> &particle) const;
};
