# Dev Base Generators

Coleção de generators em C para criar projetos iniciais em diferentes linguagens, com estrutura pronta estilo Shell-Base.

## Generators disponíveis

- `c-gen.c` → Gera projetos em **C**
- `cpp-gen.cpp` → Gera projetos em **C++**
- `py-gen.c` → Gera projetos em **Python**
- `sh-gen.c` → Gera projetos em **Shell Script (Bash)**

Cada generator cria a estrutura básica do projeto, incluindo:

- Diretórios (`src`, `tests`, etc.)
- Arquivos principais (`main`, `__init__.py` para Python, README.md, requirements.txt, etc.)
- Cabeçalho com informações de autor, licença, versão e data

---

## Como usar

1. Compile o generator desejado:

```bash
gcc -o c-gen c-gen.c        # Para C
g++ -o cpp-gen cpp-gen.cpp  # Para C++
gcc -o py-gen py-gen.c      # Para Python
gcc -o sh-gen sh-gen.c      # Para Shell Script
```

2. Execute o generator:

```bash
./c-gen        # ou cpp-gen / py-gen / sh-gen
```

3. Preencha as informações solicitadas (nome do projeto, autor, email, versão, licença, etc.)

O generator vai criar a **estrutura completa do projeto** no diretório atual.

---

## Licença

Este projeto está licenciado sob a **MIT License**.  
Veja o arquivo `LICENSE` para mais detalhes.