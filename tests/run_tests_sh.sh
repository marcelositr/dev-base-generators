#!/bin/bash
# run_tests_sh.sh - Testes rápidos Shell

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
BIN="../dev-gen"

report() {
    if [ $1 -eq 0 ]; then echo -e "${GREEN}[PASS]${NC} $2"; else echo -e "${RED}[FAIL]${NC} $2"; exit 1; fi
}

cleanup() { rm -rf test-sh config_test.txt; }
trap cleanup EXIT

echo "--- Testando Shell ---"

cat <<EOF > config_test.txt
name: test-sh
author: Tester
email: t@t.com
homepage: http://t.com
version: 1.0.0
license: MIT
description: Test
EOF

$BIN sh config_test.txt > /dev/null 2>&1
report $? "Geração Shell"
[ -x test-sh/bin/main.sh ] && bash -n test-sh/bin/main.sh
report $? "Sintaxe e Execução Shell"
