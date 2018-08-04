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
    for (unsigned int height_index = 0; height_index < height; height_index++)
        for (unsigned int width_index = 0; width_index < width; width_index++)
            map[height_index][width_index] = 0;

    int field_index = 0;

    for (auto& it : fields) {
        for (unsigned int height_index = 0; height_index < height; height_index++)
            for (unsigned int width_index = 0; width_index < width; width_index++) 
                if (it->getShape().inside(ofPoint(width_index, height_index))) { 
                    if (map[height_index][width_index] == 0)
                        map[height_index][width_index] = 1;

                    map[height_index][width_index] = map[height_index][width_index] << field_index;
                }

        field_index++;
    }
}

void FieldMap::updateParticle(std::unique_ptr<Particle>& particle) const {
    if (particle->getPosition().y < height && particle->getPosition().x < width) {
        unsigned char id = map.at(static_cast<int>(particle->getPosition().y)).at(static_cast<int>(particle->getPosition().x));

        int field_index = fields.size() - 1;

        while (id && field_index != -1) {
            if (id && 1)
                fields[field_index]->updateParticle(particle);

            id = id >> 1;

            field_index--;
        }
    }
}
