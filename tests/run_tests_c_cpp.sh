#!/bin/bash
# run_tests_c_cpp.sh - Testes rápidos e não-interativos

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
BIN="../dev-gen"

report() {
    if [ $1 -eq 0 ]; then echo -e "${GREEN}[PASS]${NC} $2"; else echo -e "${RED}[FAIL]${NC} $2"; exit 1; fi
}

cleanup() { rm -rf test-c test-cpp n1 n100 config_test.txt; }
trap cleanup EXIT

echo "--- Testando C/C++ ---"

# Config completa para evitar prompts
cat <<EOF > config_test.txt
name: test-proj
author: Tester
email: t@t.com
homepage: http://t.com
version: 1.0.0
license: MIT
description: Test
EOF

# Teste C
$BIN c config_test.txt > /dev/null 2>&1
report $? "Geração C"
(cd test-proj && make > /dev/null 2>&1)
report $? "Compilação C"
rm -rf test-proj

# Teste C++
$BIN cpp config_test.txt > /dev/null 2>&1
report $? "Geração C++"
(cd test-proj && make > /dev/null 2>&1)
report $? "Compilação C++"
rm -rf test-proj

# Limites n=1 e n=100
sed -i 's/name: .*/name: n1/' config_test.txt
$BIN c config_test.txt > /dev/null 2>&1
report $? "Limite n=1"

sed -i 's/name: .*/name: nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn/' config_test.txt
$BIN c config_test.txt > /dev/null 2>&1
report $? "Limite n=100"
