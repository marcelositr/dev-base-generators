#!/usr/bin/env python3
import os
import subprocess
import shutil
import sys

# Cores para saída
GREEN = '\033[0;32m'
RED = '\033[0;31m'
NC = '\033[0m'

BIN = "../dev-gen"

def report(success, message, detail=""):
    if success:
        print(f"{GREEN}[PASS]{NC} {message}")
    else:
        print(f"{RED}[FAIL]{NC} {message}: {detail}")
        sys.exit(1)

def cleanup():
    files = ["test-python", "n0", "n1", "n100", "config_test.txt"]
    for f in files:
        if os.path.isdir(f):
            shutil.rmtree(f)
        elif os.path.isfile(f):
            os.remove(f)

def run_tests():
    print("Iniciando testes para Python...")
    
    if not os.path.isfile(BIN):
        print(f"Erro: Binário {BIN} não encontrado.")
        sys.exit(1)

    # 1. Testar geração de projeto Python (Válido)
    with open("config_test.txt", "w") as f:
        f.write("name: test-python\nauthor: Tester\nemail: tester@example.com\n")
        f.write("homepage: http://example.com\nversion: 1.0.0\nlicense: MIT\n")
        f.write("description: Test Python project\n")

    result = subprocess.run([BIN, "python", "config_test.txt"], capture_output=True)
    report(result.returncode == 0, "Geração de projeto Python", result.stderr.decode())

    # Validar estrutura de diretórios Python
    is_valid = (os.path.isdir("test-python/src") and 
                os.path.isdir("test-python/tests") and 
                os.path.isfile("test-python/src/main.py") and 
                os.path.isfile("test-python/requirements.txt"))
    report(is_valid, "Estrutura do projeto Python", "Diretórios ou arquivos ausentes")

    # Validar sintaxe do Python gerado
    result = subprocess.run([sys.executable, "-m", "py_compile", "test-python/src/main.py"], capture_output=True)
    report(result.returncode == 0, "Sintaxe do código Python gerado", result.stderr.decode())

    # 2. Testar limites do input (n=1, n=100)
    # n=1
    with open("config_test.txt", "w") as f:
        f.write("name: n1\nauthor: Tester\n")
    result = subprocess.run([BIN, "py", "config_test.txt"], capture_output=True)
    report(result.returncode == 0, "Limite n=1 (nome curto)", result.stderr.decode())
    report(os.path.isdir("n1"), "Estrutura n=1")

    # n=100
    long_name = "n" * 100
    with open("config_test.txt", "w") as f:
        f.write(f"name: {long_name}\nauthor: Tester\n")
    result = subprocess.run([BIN, "py", "config_test.txt"], capture_output=True)
    report(result.returncode == 0, "Limite n=100 (nome longo)", result.stderr.decode())
    report(os.path.isdir(long_name), "Estrutura n=100")

    # 3. Entrada inválida (Strings ou negativos no nome do projeto são aceitos como strings, 
    # mas vamos testar uma linguagem inexistente)
    result = subprocess.run([BIN, "invalid_lang", "config_test.txt"], capture_output=True)
    report(result.returncode != 0, "Entrada inválida (Linguagem inexistente) tratada")

    print(f"\n{GREEN}Todos os testes de Python passaram!{NC}")

if __name__ == "__main__":
    try:
        run_tests()
    finally:
        cleanup()
