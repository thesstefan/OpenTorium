#pragma once

#include "emitter.h"
#include "target.h"
#include "field.h"

#include <fstream>
#include <variant>

enum ObjectType { Emitter, Target, Field };

class LevelParser {
    private:
        std::ifstream levelStream;

        enum ObjectType getObjectType();

        std::variant<Emitter *, Target *, Field *> 
            createObject(const enum ObjectType &type);

        void identifierCheck(const std::string &identifier);

        Emitter *createEmitter();

    public:
        LevelParser(const std::string &path);

        std::variant<Emitter *, Target *, Field *> 
            getObject();
};
