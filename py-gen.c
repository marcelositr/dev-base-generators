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

    printf("=== Gerador de projeto Python estilo Shell-Base ===\n");
    printf("Nome do projeto: "); fgets(nome_projeto, MAX, stdin); nome_projeto[strcspn(nome_projeto, "\n")] = 0;
    printf("Autor: "); fgets(autor, MAX, stdin); autor[strcspn(autor, "\n")] = 0;
    printf("Email: "); fgets(email, MAX, stdin); email[strcspn(email, "\n")] = 0;
    printf("Homepage: "); fgets(homepage, MAX, stdin); homepage[strcspn(homepage, "\n")] = 0;
    printf("Versão: "); fgets(versao, MAX, stdin); versao[strcspn(versao, "\n")] = 0;
    printf("Licença: "); fgets(licenca, MAX, stdin); licenca[strcspn(licenca, "\n")] = 0;
    printf("Descrição: "); fgets(descricao, MAX, stdin); descricao[strcspn(descricao, "\n")] = 0;

    // cria pastas
    criar_pasta(nome_projeto);
    criar_pasta(strcat(strcpy(caminho, nome_projeto), "/src"));
    criar_pasta(strcat(strcpy(caminho, nome_projeto), "/tests"));

    // main.py
    char main_py[MAX*20];
    snprintf(main_py, sizeof(main_py),
"# -*- coding: utf-8 -*-\n"
"\"\"\"\n"
"Autor: %s <%s>\n"
"Homepage: %s\n"
"Data de criação: %s\n"
"Programa: %s\n"
"Versão: %s\n"
"Licença: %s\n"
"Descrição: %s\n"
"ChangeLog: %s - Criado pelo generator C estilo Shell-Base para Python\n"
"\"\"\"\n\n"
"import sys\n\n"
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
"    print(\"=== Projeto %s iniciado ===\")\n"
"    dicas()\n"
"    ajuda()\n\n"
"if __name__ == '__main__':\n"
"    main()\n",
autor, email, homepage, data, nome_projeto, versao, licenca, descricao, data, nome_projeto
    );

    snprintf(caminho, MAX, "%s/src/main.py", nome_projeto);
    criar_arquivo(caminho, main_py);

    // __init__.py
    snprintf(caminho, MAX, "%s/src/__init__.py", nome_projeto);
    criar_arquivo(caminho, "# Pacote Python\n");

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

    // requirements.txt
    snprintf(caminho, MAX, "%s/requirements.txt", nome_projeto);
    criar_arquivo(caminho, "# Adicione dependências do projeto aqui\n");

    printf("Projeto %s (Python) criado com sucesso com estilo Shell-Base!\n", nome_projeto);
    return 0;
}
