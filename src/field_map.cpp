#include "field_map.h"

#include <iostream>

FieldMap::FieldMap(unsigned int width, unsigned int height) 
    : width(width), height(height), map(height, std::vector<char>(width)) {}

void FieldMap::addField(Field *field) {
    fields.push_back(std::unique_ptr<Field>(field));
}

void FieldMap::draw() const {
    for (auto& field : fields)
        field->draw();
}

void FieldMap::update() {
    for (unsigned int heightIndex = 0; heightIndex < height; heightIndex++)
        for (unsigned int widthIndex = 0; widthIndex < width; widthIndex++)
            map[heightIndex][widthIndex] = 0;

    int fieldIndex = 0;

    for (auto& it : fields) {
        for (unsigned int heightIndex = 0; heightIndex < height; heightIndex++)
            for (unsigned int widthIndex = 0; widthIndex < width; widthIndex++) 
                if (it->inside(ofPoint(widthIndex, heightIndex))) { 
                    if (map[heightIndex][widthIndex] == 0)
                        map[heightIndex][widthIndex] = 1;

                    map[heightIndex][widthIndex] = map[heightIndex][widthIndex] << fieldIndex;
                }

        fieldIndex++;
    }
}

void FieldMap::updateParticle(Particle &particle) const {
    if (particle.getPosition().y < height && particle.getPosition().x < width) {
        unsigned char id = map.at(static_cast<int>(particle.getPosition().y))
                              .at(static_cast<int>(particle.getPosition().x));

        unsigned int fieldIndex = 0;

        while (id && fieldIndex != static_cast<unsigned int>(fields.size())) {
            if (id & 1) 
                fields[fieldIndex]->updateParticle(particle);

            id = id >> 1;

            fieldIndex++;
        }
    }
}
