#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "../core/ProjectConfig.hpp"
#include "../utils/FileUtils.hpp"
#include <vector>

class Generator {
protected:
    ProjectConfig config;

    virtual void generateDirectories() = 0;
    virtual void generateMain() = 0;
    virtual void generateReadme() {
        std::string readme = "# " + config.name + "\n\n" +
                             "Autor: " + config.author + " <" + config.email + ">\n" +
                             "Homepage: " + config.homepage + "\n" +
                             "Descrição: " + config.description + "\n" +
                             "Versão: " + config.version + "\n" +
                             "Licença: " + config.license + "\n";
        FileUtils::write_file(config.name + "/README.md", readme);
    }
    virtual void generateExtraFiles() {}

public:
    explicit Generator(ProjectConfig config) : config(std::move(config)) {}
    virtual ~Generator() = default;

    void generate() {
        FileUtils::create_directory(config.name);
        generateDirectories();
        generateMain();
        generateReadme();
        generateExtraFiles();
        std::cout << "Projeto " << config.name << " criado com sucesso!" << std::endl;
    }
};

#endif
