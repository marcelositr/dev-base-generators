#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define MAX 256

//--------------------- CRIA PASTA ---------------------//
void criar_pasta(const char *pasta) {
    if (mkdir(pasta, 0755) != 0) {
        perror("Erro criando pasta");
        exit(1);
    }
}

//--------------------- CRIA ARQUIVO -------------------//
void criar_arquivo(const char *arquivo, const char *conteudo) {
    FILE *f = fopen(arquivo, "w");
    if (!f) {
        perror("Erro ao criar arquivo");
        exit(1);
    }
    fprintf(f, "%s", conteudo);
    fclose(f);
}

//--------------------- CHECAGEM ROOT -----------------//
void check_root() {
    if (geteuid() != 0) {
        printf("Execute como root!\n");
        exit(1);
    }
}

//--------------------- MAIN GENERATOR -----------------//
int main() {
    char nome_projeto[MAX], autor[MAX], email[MAX], homepage[MAX], versao[MAX], licenca[MAX], descricao[MAX];
    char caminho[MAX];
    time_t t;
    struct tm *tm_info;
    char data[MAX];

    t = time(NULL);
    tm_info = localtime(&t);
    strftime(data, MAX, "%d/%m/%Y às %H:%M", tm_info);

    printf("=== Gerador de projeto C++ ===\n");
    printf("Nome do projeto: "); fgets(nome_projeto, MAX, stdin); nome_projeto[strcspn(nome_projeto, "\n")] = 0;
    printf("Autor: "); fgets(autor, MAX, stdin); autor[strcspn(autor, "\n")] = 0;
    printf("Email: "); fgets(email, MAX, stdin); email[strcspn(email, "\n")] = 0;
    printf("Homepage: "); fgets(homepage, MAX, stdin); homepage[strcspn(homepage, "\n")] = 0;
    printf("Versão: "); fgets(versao, MAX, stdin); versao[strcspn(versao, "\n")] = 0;
    printf("Licença: "); fgets(licenca, MAX, stdin); licenca[strcspn(licenca, "\n")] = 0;
    printf("Descrição: "); fgets(descricao, MAX, stdin); descricao[strcspn(descricao, "\n")] = 0;

    // cria pasta raiz
    criar_pasta(nome_projeto);
    criar_pasta(strcat(strcpy(caminho, nome_projeto), "/src"));
    criar_pasta(strcat(strcpy(caminho, nome_projeto), "/include"));

    // --- main.cpp com header estilo Shell-Base ---
    char main_cpp[MAX*20];
    snprintf(main_cpp, sizeof(main_cpp),
"#include <iostream>\n"
"#include <cstdlib>\n\n"
"//----------------- HEADER -----------------\n"
"// AUTOR             : %s <%s>\n"
"// HOMEPAGE          : %s\n"
"// DATA-DE-CRIAÇÃO   : %s\n"
"// PROGRAMA          : %s\n"
"// VERSÃO            : %s\n"
"// LICENÇA           : %s\n"
"// DESCRIÇÃO         : %s\n"
"// CHANGELOG         :\n"
"//   %s - Criado pelo generator C estilo Shell-Base para C++\n"
"//-----------------------------------------\n\n"
"//---------------- FUNÇÕES BASE ----------------\n"
"void dicas() {\n"
"    std::cout << \"Dicas de programação vão aqui...\\n\";\n"
"}\n\n"
"void ajuda() {\n"
"    std::cout << \"Opções de ajuda vão aqui...\\n\";\n"
"}\n\n"
"void check_root() {\n"
"    if (geteuid() != 0) {\n"
"        std::cout << \"Execute como root!\\n\";\n"
"        std::exit(1);\n"
"    }\n"
"}\n\n"
"//------------------- MAIN -------------------\n"
"int main() {\n"
"    check_root();\n"
"    std::cout << \"=== Projeto %s iniciado ===\\n\";\n"
"    dicas();\n"
"    ajuda();\n"
"    return 0;\n"
"}\n",
autor, email, homepage, data, nome_projeto, versao, licenca, descricao, data, nome_projeto
    );

    snprintf(caminho, MAX, "%s/src/main.cpp", nome_projeto);
    criar_arquivo(caminho, main_cpp);

    // README.md
    char readme[MAX*10];
    snprintf(readme, sizeof(readme),
"# %s\n\n"
"Autor: %s <%s>\n"
"Homepage: %s\n"
"Descrição: %s\n"
"Versão: %s\n"
"Licença: %s\n", nome_projeto, autor, email, homepage, descricao, versao, licenca);
    snprintf(caminho, MAX, "%s/README.md", nome_projeto);
    criar_arquivo(caminho, readme);

    // Makefile
    char makefile[MAX*10];
    snprintf(makefile, sizeof(makefile),
"CC=g++\n"
"CFLAGS=-Wall -Wextra -O2\n"
"SRC=src/main.cpp\n"
"BIN=%s\n\n"
"all: $(BIN)\n\n"
"$(BIN): $(SRC)\n"
"\t$(CC) $(CFLAGS) -o $(BIN) $(SRC)\n\n"
"clean:\n"
"\trm -f $(BIN)\n", nome_projeto);
    snprintf(caminho, MAX, "%s/Makefile", nome_projeto);
    criar_arquivo(caminho, makefile);

    printf("Projeto %s criado com sucesso com estilo Shell-Base C++!\n", nome_projeto);
    return 0;
}
