#ifndef CPP_GENERATOR_HPP
#define CPP_GENERATOR_HPP

#include "../core/Generator.hpp"

class CppGenerator : public Generator {
public:
    using Generator::Generator;

protected:
    void generateDirectories() override {
        FileUtils::create_directory(config.name + "/src");
        FileUtils::create_directory(config.name + "/include");
    }

    void generateMain() override {
        std::string main_cpp = "#include <iostream>\n"
                               "#include <cstdlib>\n"
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
                               "void dicas() { std::cout << \"Dicas de programação vão aqui...\\n\"; }\n"
                               "void ajuda() { std::cout << \"Opções de ajuda vão aqui...\\n\"; }\n"
                               "void check_root() {\n"
                               "    if (geteuid() != 0) {\n"
                               "        std::cout << \"Execute como root!\\n\";\n"
                               "        std::exit(1);\n"
                               "    }\n"
                               "}\n\n"
                               "int main() {\n"
                               "    check_root();\n"
                               "    std::cout << \"=== Projeto " + config.name + " iniciado ===\\n\";\n"
                               "    dicas();\n"
                               "    ajuda();\n"
                               "    return 0;\n"
                               "}\n";
        FileUtils::write_file(config.name + "/src/main.cpp", main_cpp);
    }

    void generateExtraFiles() override {
        std::string makefile = "CC=g++\n"
                               "CFLAGS=-Wall -Wextra -O2\n"
                               "SRC=src/main.cpp\n"
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
