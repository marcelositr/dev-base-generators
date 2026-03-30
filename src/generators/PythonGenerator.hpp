#ifndef PYTHON_GENERATOR_HPP
#define PYTHON_GENERATOR_HPP

#include "../core/Generator.hpp"

class PythonGenerator : public Generator {
public:
    using Generator::Generator;

protected:
    void generateDirectories() override {
        FileUtils::create_directory(config.name + "/src");
        FileUtils::create_directory(config.name + "/tests");
    }

    void generateMain() override {
        std::string main_py = "# -*- coding: utf-8 -*-\n"
                             "\"\"\"\n"
                             "Autor: " + config.author + " <" + config.email + ">\n"
                             "Homepage: " + config.homepage + "\n"
                             "Data de criação: " + config.creation_date + "\n"
                             "Programa: " + config.name + "\n"
                             "Versão: " + config.version + "\n"
                             "Licença: " + config.license + "\n"
                             "Descrição: " + config.description + "\n"
                             "ChangeLog: " + config.creation_date + " - Criado pelo generator moderno\n"
                             "\"\"\"\n\n"
                             "import sys\n"
                             "import os\n\n"
                             "def dicas():\n"
                             "    print(\"Dicas de programação vão aqui...\")\n\n"
                             "def ajuda():\n"
                             "    print(\"Opções de ajuda vão aqui...\")\n\n"
                             "def check_root():\n"
                             "    if hasattr(os, 'geteuid') and os.geteuid() != 0:\n"
                             "        print(\"Execute como root!\")\n"
                             "        sys.exit(1)\n\n"
                             "def main():\n"
                             "    check_root()\n"
                             "    print(f\"=== Projeto {os.path.basename(sys.argv[0])} iniciado ===\")\n"
                             "    dicas()\n"
                             "    ajuda()\n\n"
                             "if __name__ == '__main__':\n"
                             "    main()\n";
        FileUtils::write_file(config.name + "/src/main.py", main_py);
    }

    void generateExtraFiles() override {
        FileUtils::write_file(config.name + "/src/__init__.py", "# Pacote Python\n");
        FileUtils::write_file(config.name + "/requirements.txt", "# Adicione dependências do projeto aqui\n");
    }
};

#endif
