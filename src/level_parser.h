#pragma once

#include "emitter.h"
#include "target.h"
#include "field.h"

#include <fstream>
#include <variant>
#include <exception>

enum ObjectType { EmitterType, TargetType, FieldType };

class LevelParser {
    private:
        std::ifstream levelStream;

        enum ObjectType getObjectType();

        std::variant<Emitter *, Target *, Field *> 
            createObject(const enum ObjectType &type);

        void identifierCheck(const std::string &identifier);

        Emitter *createEmitter();
        Field *createField();
        Target *createTarget();

    public:
        LevelParser();

        void load(const std::string &path);

        std::variant<Emitter *, Target *, Field *> 
            getObject();
};

class LevelLoadFail : public std::runtime_error {
    public:
        LevelLoadFail(const std::string& message);

        const char *what() const noexcept override;
};

class LevelIdentifierFail : public std::runtime_error {
    public:
        LevelIdentifierFail(const std::string& message);

        const char *what() const noexcept;
};

class EOFReached : public std::runtime_error {
    public:
        EOFReached(const std::string& message);

        const char *what() const noexcept override;
};

class UnknownType : public std::runtime_error {
    public:
        UnknownType(const std::string& message);

        const char *what() const noexcept override;
};
