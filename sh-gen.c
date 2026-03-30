#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define MAX 256

void criar_pasta(const char *pasta) {
    if (mkdir(pasta, 0755) != 0) {
        perror("Erro criando pasta");
        exit(1);
    }
}

void criar_arquivo(const char *arquivo, const char *conteudo) {
    FILE *f = fopen(arquivo, "w");
    if (!f) {
        perror("Erro ao criar arquivo");
        exit(1);
    }
    fprintf(f, "%s", conteudo);
    fclose(f);
}

void check_root() {
    if (geteuid() != 0) {
        printf("Execute como root!\n");
        exit(1);
    }
}

int main() {
    char nome_projeto[MAX], autor[MAX], email[MAX], homepage[MAX], versao[MAX], licenca[MAX], descricao[MAX];
    char caminho[MAX];
    time_t t;
    struct tm *tm_info;
    char data[MAX];

    t = time(NULL);
    tm_info = localtime(&t);
    strftime(data, MAX, "%d/%m/%Y às %H:%M", tm_info);

    printf("=== Gerador de projeto Shell ===\n");
    printf("Nome do projeto: "); fgets(nome_projeto, MAX, stdin); nome_projeto[strcspn(nome_projeto, "\n")] = 0;
    printf("Autor: "); fgets(autor, MAX, stdin); autor[strcspn(autor, "\n")] = 0;
    printf("Email: "); fgets(email, MAX, stdin); email[strcspn(email, "\n")] = 0;
    printf("Homepage: "); fgets(homepage, MAX, stdin); homepage[strcspn(homepage, "\n")] = 0;
    printf("Versão: "); fgets(versao, MAX, stdin); versao[strcspn(versao, "\n")] = 0;
    printf("Licença: "); fgets(licenca, MAX, stdin); licenca[strcspn(licenca, "\n")] = 0;
    printf("Descrição: "); fgets(descricao, MAX, stdin); descricao[strcspn(descricao, "\n")] = 0;

    // cria pastas
    criar_pasta(nome_projeto);
    criar_pasta(strcat(strcpy(caminho, nome_projeto), "/bin"));
    criar_pasta(strcat(strcpy(caminho, nome_projeto), "/lib"));

    // main.sh
    char main_sh[MAX*20];
    snprintf(main_sh, sizeof(main_sh),
"#!/usr/bin/env bash\n"
"#----------------- HEADER -----------------\n"
"# AUTOR             : %s <%s>\n"
"# HOMEPAGE          : %s\n"
"# DATA-DE-CRIAÇÃO   : %s\n"
"# PROGRAMA          : %s\n"
"# VERSÃO            : %s\n"
"# LICENÇA           : %s\n"
"# DESCRIÇÃO         : %s\n"
"# CHANGELOG         : %s - Criado pelo generator C estilo Shell-Base para Bash\n"
"#-----------------------------------------\n\n"
"# Funções base\n"
"dicas() {\n"
"    printf \"Dicas de Shell Script vão aqui...\\n\"\n"
"}\n\n"
"ajuda() {\n"
"    printf \"Opções de ajuda vão aqui...\\n\"\n"
"}\n\n"
"check_root() {\n"
"    if [[ $UID -ne 0 ]]; then\n"
"        printf \"Execute como root!\\n\"\n"
"        exit 1\n"
"    fi\n"
"}\n\n"
"# MAIN\n"
"check_root\n"
"printf \"=== Projeto %s iniciado ===\\n\"\n"
"dicas\n"
"ajuda\n",
autor, email, homepage, data, nome_projeto, versao, licenca, descricao, data, nome_projeto
    );

    snprintf(caminho, MAX, "%s/bin/main.sh", nome_projeto);
    criar_arquivo(caminho, main_sh);
    chmod(caminho, 0755); // deixa executável

    // README.md
    char readme[MAX*10];
    snprintf(readme, sizeof(readme),
"# %s\n\n"
"Autor: %s <%s>\n"
"Homepage: %s\n"
"Descrição: %s\n"
"Versão: %s\n"
"Licença: %s\n",
nome_projeto, autor, email, homepage, descricao, versao, licenca);
    snprintf(caminho, MAX, "%s/README.md", nome_projeto);
    criar_arquivo(caminho, readme);

    // run.sh opcional para facilitar execução
    char run_sh[MAX*5];
    snprintf(run_sh, sizeof(run_sh),
"#!/usr/bin/env bash\n"
"# Script para rodar %s\n"
"bin/main.sh\n", nome_projeto);
    snprintf(caminho, MAX, "%s/run.sh", nome_projeto);
    criar_arquivo(caminho, run_sh);
    chmod(caminho, 0755);

    printf("Projeto %s (Bash) criado com sucesso com estilo Shell-Base!\n", nome_projeto);
    return 0;
}
