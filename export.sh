#!/bin/bash

# Script para exportar projeto via PowerShell
echo "🔧 Iniciando exportação do projeto..."

# Executar script PowerShell
powershell -ExecutionPolicy Bypass -File "./build/export.ps1"

# Verificar se executou com sucesso
if [ $? -eq 0 ]; then
    echo "✅ Exportação concluída com sucesso!"
else
    echo "❌ Erro na exportação!"
    exit 1
fi