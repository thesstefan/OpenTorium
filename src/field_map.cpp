#include "field_map.h"

#include <iostream>

FieldMap::FieldMap(unsigned int width, unsigned int height) 
    : bounds(0, 0, width, height), map(height, std::vector<uint8_t>(width)) {}

void FieldMap::addField(const Field *field) {
    fields.push_back(std::unique_ptr<const Field>(field));
}

void FieldMap::draw() const {
    for (const auto &field : fields)
        field->draw();
}

void FieldMap::update() {
    for (auto &row : map)
        std::fill(row.begin(), row.end(), 0);

    for (size_t fieldIndex = 0; fieldIndex < fields.size(); fieldIndex++)
        for (unsigned int heightIndex = 0; heightIndex < bounds.getHeight(); heightIndex++)
            for (unsigned int widthIndex = 0; widthIndex < bounds.getWidth(); widthIndex++) 
                if (fields[fieldIndex]->inside(ofPoint(widthIndex, heightIndex))) { 
                    if (map[heightIndex][widthIndex] == 0)
                        map[heightIndex][widthIndex] = 1;

                    map[heightIndex][widthIndex] = map[heightIndex][widthIndex] << fieldIndex;
                }
}

void FieldMap::updateParticle(Particle &particle) const {

    const ofPoint &position = particle.getPosition();

    // Skip update if the particle is not inside the field
    if (!bounds.inside(position))
        return;

    auto id = map.at(position.y).at(position.x);

    for (size_t fieldIndex = 0; fieldIndex < fields.size(); fieldIndex++) {
        if (id & 1) 
            fields[fieldIndex]->updateParticle(particle);

        id = id >> 1;
    }
}
