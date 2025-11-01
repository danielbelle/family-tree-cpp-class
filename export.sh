#!/bin/bash

# Configurar encoding para UTF-8
export LANG=en_US.UTF-8
export LC_ALL=en_US.UTF-8

# Verificar se a pasta build existe
if [ ! -d "build" ]; then
    echo "Criando pasta build..."
    mkdir build
fi

# Verificar se o arquivo PowerShell existe
if [ ! -f "build/export.ps1" ]; then
    echo "ERRO: Arquivo build/export.ps1 nao encontrado!"
    exit 1
fi

# Executar o script PowerShell
cd build

# Executar PowerShell de forma que aceite o script completo
powershell -ExecutionPolicy Bypass -Command "& '.\export.ps1'"

# Verificar se o arquivo foi criado
if [ -f "export.txt" ]; then
    grep -E "(PROJETO:|Data:|Total de arquivos)" export.txt
else
    echo "ERRO: export.txt nao foi criado!"
    exit 1
fi