#!/bin/bash

# Script de exportação automática para o projeto Family Tree
# Local: doc/export.sh
# Saída: build/export.txt

# Obter diretório raiz do projeto (onde o script foi chamado)
PROJECT_ROOT="$(pwd)"
echo "Diretório raiz do projeto: $PROJECT_ROOT"

# Configurações
OUTPUT_FILE="$PROJECT_ROOT/build/export.txt"
PROJECT_NAME="family_tree"

# CONFIGURAÇÕES DE EXCLUSÃO - EDITAR CONFORME NECESSÁRIO
# Pastas que serão completamente ignoradas (separadas por espaço)
EXCLUIR_PASTAS="build .git .vscode .idea"
# Arquivos específicos para excluir (separados por espaço)
EXCLUIR_ARQUIVOS="export.txt .gitignore README.md"
# Extensões de arquivo para excluir (separadas por espaço)
EXCLUIR_EXTENSOES=".tmp .log .bak"

# Obter data atual
DATA_ATUAL=$(date +"%d/%m/%Y %H:%M:%S")

echo "=== EXPORTAÇÃO AUTOMÁTICA DO PROJETO ==="
echo ""

# Verificar se a pasta build existe
BUILD_DIR="$PROJECT_ROOT/build"
if [ ! -d "$BUILD_DIR" ]; then
    echo "⚠️  Criando pasta build..."
    mkdir -p "$BUILD_DIR"
fi

# Iniciar arquivo de exportação com UTF-8
echo "PROJETO: $PROJECT_NAME" > "$OUTPUT_FILE"
echo "Data: $DATA_ATUAL" >> "$OUTPUT_FILE"
echo "" >> "$OUTPUT_FILE"

# Construir comando find com exclusões
COMANDO_FIND="find \"$PROJECT_ROOT\" -type f"

# Adicionar exclusões de pastas
for pasta in $EXCLUIR_PASTAS; do
    COMANDO_FIND="$COMANDO_FIND -not -path \"*/$pasta/*\""
done

# Adicionar exclusões de arquivos
for arquivo in $EXCLUIR_ARQUIVOS; do
    COMANDO_FIND="$COMANDO_FIND -not -name \"$arquivo\""
done

# Adicionar exclusões de extensões
for extensao in $EXCLUIR_EXTENSOES; do
    COMANDO_FIND="$COMANDO_FIND -not -name \"*$extensao\""
done

# Encontrar todos os arquivos automaticamente
echo "🔍 Procurando arquivos no projeto..."
ARQUIVOS_ENCONTRADOS=()
while IFS= read -r -d '' arquivo; do
    ARQUIVOS_ENCONTRADOS+=("$arquivo")
done < <(eval "$COMANDO_FIND -print0")

# Estrutura do projeto
echo "ESTRUTURA DO PROJETO" >> "$OUTPUT_FILE"
echo "====================" >> "$OUTPUT_FILE"
echo "" >> "$OUTPUT_FILE"

TOTAL_ARQUIVOS=0
declare -A CATEGORIAS_ADICIONADAS

# Função para obter categoria do arquivo
obter_categoria() {
    local caminho="$1"
    local pasta=$(dirname "${caminho#$PROJECT_ROOT/}")
    
    case "$pasta" in
        ".") echo "[RAIZ]" ;;
        "doc") echo "[PASTA] doc" ;;
        "include") echo "[PASTA] include" ;;
        "src") echo "[PASTA] src" ;;
        *) echo "[PASTA] $pasta" ;;
    esac
}

# Adicionar estrutura do projeto
for CAMINHO in "${ARQUIVOS_ENCONTRADOS[@]}"; do
    CATEGORIA=$(obter_categoria "$CAMINHO")
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
    fi
done

echo "" >> "$OUTPUT_FILE"
echo "CONTEUDO DOS ARQUIVOS" >> "$OUTPUT_FILE"
echo "=====================" >> "$OUTPUT_FILE"
echo "" >> "$OUTPUT_FILE"

# Adicionar conteúdo de cada arquivo com suporte a UTF-8
for CAMINHO in "${ARQUIVOS_ENCONTRADOS[@]}"; do
    CAMINHO_RELATIVO="${CAMINHO#$PROJECT_ROOT/}"
    
    if [ -f "$CAMINHO" ]; then
        echo "Processando: $CAMINHO_RELATIVO"
        
        echo "ARQUIVO: $CAMINHO_RELATIVO" >> "$OUTPUT_FILE"
        echo "----------------------------------------" >> "$OUTPUT_FILE"
        
        # Ler e adicionar conteúdo do arquivo com suporte a UTF-8
        if [ -r "$CAMINHO" ]; then
            # Usar iconv para garantir codificação UTF-8 ou cat com LANG definido
            if command -v iconv >/dev/null 2>&1; then
                # Tentar detectar a codificação e converter para UTF-8
                if file -i "$CAMINHO" | grep -q "utf-8\|us-ascii"; then
                    cat "$CAMINHO" >> "$OUTPUT_FILE"
                else
                    iconv -f "$(file -bi "$CAMINHO" | sed -e 's/.*[ ]charset=//')" -t UTF-8 "$CAMINHO" >> "$OUTPUT_FILE" 2>/dev/null || cat "$CAMINHO" >> "$OUTPUT_FILE"
                fi
            else
                # Fallback: usar cat com locale definido para UTF-8
                LANG=C.UTF-8 cat "$CAMINHO" >> "$OUTPUT_FILE" 2>/dev/null || cat "$CAMINHO" >> "$OUTPUT_FILE"
            fi
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