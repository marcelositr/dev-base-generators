#ifndef GENERATOR_FACTORY_HPP
#define GENERATOR_FACTORY_HPP

#include <memory>
#include <string>
#include "../generators/CGenerator.hpp"
#include "../generators/CppGenerator.hpp"
#include "../generators/PythonGenerator.hpp"
#include "../generators/ShellGenerator.hpp"

enum class Language {
    C,
    CPP,
    PYTHON,
    SHELL
};

class GeneratorFactory {
public:
    static std::unique_ptr<Generator> createGenerator(Language lang, ProjectConfig config) {
        switch (lang) {
            case Language::C:
                return std::make_unique<CGenerator>(std::move(config));
            case Language::CPP:
                return std::make_unique<CppGenerator>(std::move(config));
            case Language::PYTHON:
                return std::make_unique<PythonGenerator>(std::move(config));
            case Language::SHELL:
                return std::make_unique<ShellGenerator>(std::move(config));
            default:
                return nullptr;
        }
    }

    static Language stringToLanguage(const std::string& langStr) {
        if (langStr == "c") return Language::C;
        if (langStr == "cpp") return Language::CPP;
        if (langStr == "python" || langStr == "py") return Language::PYTHON;
        if (langStr == "shell" || langStr == "sh") return Language::SHELL;
        throw std::invalid_argument("Linguagem não suportada: " + langStr);
    }
};

#endif
