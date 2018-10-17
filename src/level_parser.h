#pragma once

#include "emitter.h"
#include "target.h"
#include "field.h"

#include <fstream>
#include <variant>
#include <exception>

enum ObjectType { EmitterType, FieldType, TargetType };

class ObjectParser {
    private:
        std::ifstream& stream;
        enum ObjectType type;

        std::map<const std::string, std::string> data;

    public:
        ObjectParser(const std::vector<std::string>& identifiers,
                     std::ifstream &stream,
                     const enum ObjectType type);

        void addValue(const std::string& identifier,
                      const std::string& value);

        bool ready() const;

        const std::map<const std::string, std::string>& parse();
};

class LevelParser {
    private:
        std::ifstream levelStream;

    public:
        LevelParser();

        void load(const std::string &path);

        std::variant<Emitter *, Field *, Target *> 
            getObject();
};
