#include "field_map.h"

FieldMap::FieldMap(unsigned int width, unsigned int height) 
    : width(width), height(height), map(width, std::vector<char>(height)) {}

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

    for (auto& it : fields)
        for (unsigned int height_index = 0; height_index < height; height_index++)
            for (unsigned int width_index = 0; width_index < width; width_index++)
                if (it->getShape().inside(ofPoint(width_index, height_index)))
                    map[height_index][width_index] >> 1;
}

void FieldMap::updateParticle(std::unique_ptr<Particle>& particle) const {
    char id = map[particle->getPosition().x][particle->getPosition().y];

    int field_index = 0;

    while (id != char(-1)) {
        if (id && 1)
            fields[field_index]->updateParticle(particle);

        id = id >> 1;

        field_index++;
    }
}
