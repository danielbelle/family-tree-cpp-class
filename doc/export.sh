#!/bin/bash

# Script de exportação para o projeto Family Tree
# Local: doc/export.sh
# Saída: build/export.txt

# Obter diretório raiz do projeto (onde o script foi chamado)
PROJECT_ROOT="$(pwd)"
echo "Diretório raiz do projeto: $PROJECT_ROOT"

# Configurações
OUTPUT_FILE="$PROJECT_ROOT/build/export.txt"
PROJECT_NAME="family_tree"

# Obter data atual
DATA_ATUAL=$(date +"%d/%m/%Y %H:%M:%S")

echo "=== EXPORTAÇÃO DO PROJETO ==="
echo ""

# Verificar se a pasta build existe
BUILD_DIR="$PROJECT_ROOT/build"
if [ ! -d "$BUILD_DIR" ]; then
    echo "⚠️  Criando pasta build..."
    mkdir -p "$BUILD_DIR"
fi

# Iniciar arquivo de exportação
echo "PROJETO: $PROJECT_NAME" > "$OUTPUT_FILE"
echo "Data: $DATA_ATUAL" >> "$OUTPUT_FILE"
echo "" >> "$OUTPUT_FILE"

# Estrutura do projeto
echo "ESTRUTURA DO PROJETO" >> "$OUTPUT_FILE"
echo "====================" >> "$OUTPUT_FILE"
echo "" >> "$OUTPUT_FILE"

# Lista de arquivos com caminhos absolutos
declare -A ARQUIVOS=(
    ["$PROJECT_ROOT/run.sh"]="[RAIZ]"
    ["$PROJECT_ROOT/CMakeLists.txt"]="[RAIZ]"
    ["$PROJECT_ROOT/doc/export.sh"]="[PASTA] doc"
    ["$PROJECT_ROOT/include/estruturas.hpp"]="[PASTA] include"
    ["$PROJECT_ROOT/include/includes.hpp"]="[PASTA] include"
    ["$PROJECT_ROOT/include/main.hpp"]="[PASTA] include"
    ["$PROJECT_ROOT/include/menu_criar.hpp"]="[PASTA] include"
    ["$PROJECT_ROOT/include/menu_exibir.hpp"]="[PASTA] include"
    ["$PROJECT_ROOT/include/menu_import_export.hpp"]="[PASTA] include"
    ["$PROJECT_ROOT/include/menu_funcoes.hpp"]="[PASTA] include"
    ["$PROJECT_ROOT/include/menu_principal.hpp"]="[PASTA] include"
    ["$PROJECT_ROOT/include/processo.hpp"]="[PASTA] include"
    ["$PROJECT_ROOT/src/main.cpp"]="[PASTA] src"
    ["$PROJECT_ROOT/src/menu_criar.cpp"]="[PASTA] src"
    ["$PROJECT_ROOT/src/menu_exibir.cpp"]="[PASTA] src"
    ["$PROJECT_ROOT/src/menu_import_export.cpp"]="[PASTA] src"
    ["$PROJECT_ROOT/src/menu_funcoes.cpp"]="[PASTA] src"
    ["$PROJECT_ROOT/src/menu_principal.cpp"]="[PASTA] src"
    ["$PROJECT_ROOT/src/processo.cpp"]="[PASTA] src"
)

TOTAL_ARQUIVOS=0
declare -A CATEGORIAS_ADICIONADAS

# Adicionar estrutura do projeto
for CAMINHO in "${!ARQUIVOS[@]}"; do
    CATEGORIA="${ARQUIVOS[$CAMINHO]}"
    CAMINHO_RELATIVO="${CAMINHO#$PROJECT_ROOT/}"
    
    if [ -f "$CAMINHO" ]; then
        # Adicionar categoria se ainda não foi adicionada
        if [ -z "${CATEGORIAS_ADICIONADAS[$CATEGORIA]}" ]; then
            if [ ${#CATEGORIAS_ADICIONADAS[@]} -gt 0 ]; then
                echo "" >> "$OUTPUT_FILE"
            fi
            echo "$CATEGORIA" >> "$OUTPUT_FILE"
            CATEGORIAS_ADICIONADAS["$CATEGORIA"]=1
        fi
        
        NOME_ARQUIVO=$(basename "$CAMINHO_RELATIVO")
        echo "  --> $NOME_ARQUIVO" >> "$OUTPUT_FILE"
        ((TOTAL_ARQUIVOS++))
        echo "✓ Encontrado: $CAMINHO_RELATIVO"
    else
        echo "✗ Não encontrado: $CAMINHO_RELATIVO"
    fi
done

echo "" >> "$OUTPUT_FILE"
echo "CONTEUDO DOS ARQUIVOS" >> "$OUTPUT_FILE"
echo "=====================" >> "$OUTPUT_FILE"
echo "" >> "$OUTPUT_FILE"

# Adicionar conteúdo de cada arquivo
for CAMINHO in "${!ARQUIVOS[@]}"; do
    CAMINHO_RELATIVO="${CAMINHO#$PROJECT_ROOT/}"
    
    if [ -f "$CAMINHO" ]; then
        echo "Processando: $CAMINHO_RELATIVO"
        
        echo "ARQUIVO: $CAMINHO_RELATIVO" >> "$OUTPUT_FILE"
        echo "----------------------------------------" >> "$OUTPUT_FILE"
        
        # Ler e adicionar conteúdo do arquivo
        if [ -r "$CAMINHO" ]; then
            cat "$CAMINHO" >> "$OUTPUT_FILE"
        else
            echo "❌ ERRO: Não foi possível ler o arquivo" >> "$OUTPUT_FILE"
        fi
        
        echo "" >> "$OUTPUT_FILE"
        echo "" >> "$OUTPUT_FILE"
    fi
done

# Adicionar resumo
echo "Total de arquivos processados: $TOTAL_ARQUIVOS" >> "$OUTPUT_FILE"

echo ""
echo "✅ EXPORTAÇÃO CONCLUÍDA!"
echo "Total de arquivos exportados: $TOTAL_ARQUIVOS"
echo "Arquivo gerado: $OUTPUT_FILE"