#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//----------------- HEADER -----------------
// AUTOR             : Tester <t@t.com>
// HOMEPAGE          : http://t.com
// DATA-DE-CRIAÇÃO   : 30/03/2026 às 09:59
// PROGRAMA          : nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
// VERSÃO            : 1.0.0
// LICENÇA           : MIT
// DESCRIÇÃO         : Test
// CHANGELOG         :
//   30/03/2026 às 09:59 - Criado pelo generator moderno
//-----------------------------------------

void dicas() { printf("Dicas de programação vão aqui...\n"); }
void ajuda() { printf("Opções de ajuda vão aqui...\n"); }
void check_root() {
    if (geteuid() != 0) {
        printf("Execute como root!\n");
        exit(1);
    }
}

int main() {
    check_root();
    printf("=== Projeto nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn iniciado ===\n");
    dicas();
    ajuda();
    return 0;
}
