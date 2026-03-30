#ifndef SHELL_GENERATOR_HPP
#define SHELL_GENERATOR_HPP

#include "../core/Generator.hpp"

class ShellGenerator : public Generator {
public:
    using Generator::Generator;

protected:
    void generateDirectories() override {
        FileUtils::create_directory(config.name + "/bin");
        FileUtils::create_directory(config.name + "/lib");
    }

    void generateMain() override {
        std::string main_sh = "#!/usr/bin/env bash\n"
                             "#----------------- HEADER -----------------\n"
                             "# AUTOR             : " + config.author + " <" + config.email + ">\n"
                             "# HOMEPAGE          : " + config.homepage + "\n"
                             "# DATA-DE-CRIAÇÃO   : " + config.creation_date + "\n"
                             "# PROGRAMA          : " + config.name + "\n"
                             "# VERSÃO            : " + config.version + "\n"
                             "# LICENÇA           : " + config.license + "\n"
                             "# DESCRIÇÃO         : " + config.description + "\n"
                             "# CHANGELOG         : " + config.creation_date + " - Criado pelo generator moderno\n"
                             "#-----------------------------------------\n\n"
                             "dicas() { printf \"Dicas de Shell Script vão aqui...\\n\"; }\n"
                             "ajuda() { printf \"Opções de ajuda vão aqui...\\n\"; }\n"
                             "check_root() {\n"
                             "    if [[ $UID -ne 0 ]]; then\n"
                             "        printf \"Execute como root!\\n\"\n"
                             "        exit 1\n"
                             "    fi\n"
                             "}\n\n"
                             "check_root\n"
                             "printf \"=== Projeto " + config.name + " iniciado ===\\n\"\n"
                             "dicas\n"
                             "ajuda\n";
        std::string path = config.name + "/bin/main.sh";
        FileUtils::write_file(path, main_sh);
        FileUtils::set_executable(path);
    }

    void generateExtraFiles() override {
        std::string run_sh = "#!/usr/bin/env bash\n"
                             "bin/main.sh\n";
        std::string path = config.name + "/run.sh";
        FileUtils::write_file(path, run_sh);
        FileUtils::set_executable(path);
    }
};

#endif
