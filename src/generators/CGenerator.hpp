#ifndef C_GENERATOR_HPP
#define C_GENERATOR_HPP

#include "../core/Generator.hpp"

class CGenerator : public Generator {
public:
    using Generator::Generator;

protected:
    void generateDirectories() override {
        FileUtils::create_directory(config.name + "/src");
        FileUtils::create_directory(config.name + "/include");
    }

    void generateMain() override {
        std::string main_c = "#include <stdio.h>\n"
                             "#include <stdlib.h>\n"
                             "#include <unistd.h>\n\n"
                             "//----------------- HEADER -----------------\n"
                             "// AUTOR             : " + config.author + " <" + config.email + ">\n"
                             "// HOMEPAGE          : " + config.homepage + "\n"
                             "// DATA-DE-CRIAÇÃO   : " + config.creation_date + "\n"
                             "// PROGRAMA          : " + config.name + "\n"
                             "// VERSÃO            : " + config.version + "\n"
                             "// LICENÇA           : " + config.license + "\n"
                             "// DESCRIÇÃO         : " + config.description + "\n"
                             "// CHANGELOG         :\n"
                             "//   " + config.creation_date + " - Criado pelo generator moderno\n"
                             "//-----------------------------------------\n\n"
                             "void dicas() { printf(\"Dicas de programação vão aqui...\\n\"); }\n"
                             "void ajuda() { printf(\"Opções de ajuda vão aqui...\\n\"); }\n"
                             "void check_root() {\n"
                             "    if (geteuid() != 0) {\n"
                             "        printf(\"Execute como root!\\n\");\n"
                             "        exit(1);\n"
                             "    }\n"
                             "}\n\n"
                             "int main() {\n"
                             "    check_root();\n"
                             "    printf(\"=== Projeto " + config.name + " iniciado ===\\n\");\n"
                             "    dicas();\n"
                             "    ajuda();\n"
                             "    return 0;\n"
                             "}\n";
        FileUtils::write_file(config.name + "/src/main.c", main_c);
    }

    void generateExtraFiles() override {
        std::string makefile = "CC=gcc\n"
                               "CFLAGS=-Wall -Wextra -O2\n"
                               "SRC=src/main.c\n"
                               "BIN=" + config.name + "\n\n"
                               "all: $(BIN)\n\n"
                               "$(BIN): $(SRC)\n"
                               "\t$(CC) $(CFLAGS) -o $(BIN) $(SRC)\n\n"
                               "clean:\n"
                               "\trm -f $(BIN)\n";
        FileUtils::write_file(config.name + "/Makefile", makefile);
    }
};

#endif
