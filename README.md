# Dev Base Generators (Modern Edition)

Coleção de generators robusta e modular para criar projetos iniciais em diferentes linguagens. Refatorado com foco em POO, SOLID e Clean Code.

## Arquitetura

O projeto utiliza uma arquitetura modular baseada em C++17:

- **Core**: Contém a classe abstrata `Generator` com o padrão *Template Method* e as configurações base.
- **Generators**: Implementações específicas para cada linguagem (C, C++, Python, Shell).
- **Factory**: Padrão *Factory Method* para instanciar o gerador adequado via CLI.
- **Utils**: Utilitários de sistema de arquivos e manipulação de strings.
- **CLI**: Interface unificada para interação com o usuário.

## Generators Disponíveis

- `c` → Gera projetos em **C**
- `cpp` → Gera projetos em **C++**
- `python` / `py` → Gera projetos em **Python**
- `shell` / `sh` → Gera projetos em **Shell Script**

## Como Usar

### Compilação

```bash
make
```

### Execução Interativa

```bash
./dev-gen c
```

### Execução via Arquivo de Configuração

Crie um arquivo `config.txt`:

```text
name: meu-projeto
author: Seu Nome
email: seu@email.com
homepage: https://github.com/usuario/meu-projeto
version: 1.0.0
license: MIT
description: Uma breve descrição do projeto.
```

E execute:

```bash
./dev-gen python config.txt
```

---

## Estrutura do Repositório

```text
.
├── Makefile
├── README.md
├── src/
│   ├── core/           # Abstrações e Modelos
│   ├── generators/     # Implementações (C, C++, Py, Sh)
│   ├── factory/        # Factory Pattern
│   ├── utils/          # FileSystem Utils
│   └── main.cpp        # Entry Point CLI
└── tests/              # Testes (em desenvolvimento)
```

## Licença

Este projeto está licenciado sob a **MIT License**.
