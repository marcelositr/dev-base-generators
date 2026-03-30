#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <map>
#include "core/ProjectConfig.hpp"
#include "factory/GeneratorFactory.hpp"

std::string getCurrentDate() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d/%m/%Y às %H:%M", &tstruct);
    return buf;
}

ProjectConfig loadConfig(const std::string& path) {
    ProjectConfig config;
    std::ifstream file(path);
    if (!file.is_open()) return config;

    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find(':');
        if (pos == std::string::npos) continue;
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        // trim
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        if (key == "name") config.name = value;
        else if (key == "author") config.author = value;
        else if (key == "email") config.email = value;
        else if (key == "homepage") config.homepage = value;
        else if (key == "version") config.version = value;
        else if (key == "license") config.license = value;
        else if (key == "description") config.description = value;
    }
    return config;
}

void promptConfig(ProjectConfig& config) {
    auto prompt = [](const std::string& label, std::string& field) {
        if (!field.empty()) return;
        std::cout << label << ": ";
        std::getline(std::cin, field);
    };

    prompt("Nome do projeto", config.name);
    prompt("Autor", config.author);
    prompt("Email", config.email);
    prompt("Homepage", config.homepage);
    prompt("Versão", config.version);
    prompt("Licença", config.license);
    prompt("Descrição", config.description);
}

void printHelp(const char* progName) {
    std::cout << "Gerador de Estrutura de Projetos (dev-base-generators)" << std::endl;
    std::cout << "\nUso:" << std::endl;
    std::cout << "  " << progName << " <linguagem> [config.txt]" << std::endl;
    std::cout << "  " << progName << " -h | --help" << std::endl;
    std::cout << "\nLinguagens suportadas:" << std::endl;
    std::cout << "  c       - Gera um projeto C base com Makefile" << std::endl;
    std::cout << "  cpp     - Gera um projeto C++ base com Makefile" << std::endl;
    std::cout << "  python  - Gera um projeto Python base com venv e requirements.txt" << std::endl;
    std::cout << "  shell   - Gera um script Shell base com cabeçalho de licença" << std::endl;
    std::cout << "\nArgumentos:" << std::endl;
    std::cout << "  <linguagem>  A linguagem do projeto a ser gerado." << std::endl;
    std::cout << "  [config.txt] Opcional: Caminho para um arquivo de configuração (.txt)" << std::endl;
    std::cout << "               contendo os metadados do projeto (nome, autor, etc)." << std::endl;
    std::cout << "\nExemplo:" << std::endl;
    std::cout << "  " << progName << " cpp" << std::endl;
    std::cout << "  " << progName << " python meu_projeto_config.txt" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp(argv[0]);
        return 1;
    }

    std::string arg1 = argv[1];
    if (arg1 == "-h" || arg1 == "--help") {
        printHelp(argv[0]);
        return 0;
    }

    std::string langStr = arg1;
    std::string configPath = (argc > 2) ? argv[2] : "";

    try {
        Language lang = GeneratorFactory::stringToLanguage(langStr);
        ProjectConfig config;
        
        if (!configPath.empty()) {
            config = loadConfig(configPath);
        }
        
        promptConfig(config);
        config.creation_date = getCurrentDate();

        auto generator = GeneratorFactory::createGenerator(lang, config);
        if (generator) {
            generator->generate();
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
