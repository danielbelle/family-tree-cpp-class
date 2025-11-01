#!/bin/bash

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Função para mostrar menu
show_menu() {
    echo -e "${BLUE}=== MENU DE COMPILAÇÃO ===${NC}"
    echo -e "${GREEN}1${NC} - mb   (Apenas compilar)"
    echo -e "${GREEN}2${NC} - mbr  (Compilar e executar)" 
    echo -e "${GREEN}3${NC} - rec  (Reconfigurar e compilar)"
    echo -e "${GREEN}4${NC} - recr (Reconfigurar, compilar e executar)"
    echo -e "${GREEN}0${NC} - Sair"
    echo -n -e "${YELLOW}Escolha uma opção [0-4]: ${NC}"
}

# Função para compilar apenas
mb() {
    echo -e "${BLUE}=== COMPILANDO ===${NC}"
    cd build
    if mingw32-make; then
        echo -e "${GREEN}✅ Compilação bem-sucedida!${NC}"
    else
        echo -e "${RED}❌ Erro na compilação!${NC}"
        return 1
    fi
}

# Função para compilar e executar
mbr() {
    echo -e "${BLUE}=== COMPILANDO E EXECUTANDO ===${NC}"
    cd build
    if mingw32-make; then
        echo -e "${GREEN}✅ Compilação bem-sucedida!${NC}"
        echo -e "${BLUE}=== EXECUTANDO PROGRAMA ===${NC}"
        ./trabalho_cpp.exe
    else
        echo -e "${RED}❌ Erro na compilação!${NC}"
        return 1
    fi
}

# Função para reconfigurar e compilar
rec() {
    echo -e "${BLUE}=== RECONFIGURANDO E COMPILANDO ===${NC}"
    cd build
    if cmake -G "MinGW Makefiles" .. && mingw32-make; then
        echo -e "${GREEN}✅ Reconfiguração e compilação bem-sucedidas!${NC}"
    else
        echo -e "${RED}❌ Erro na reconfiguração/compilação!${NC}"
        return 1
    fi
}

# Função para reconfigurar, compilar e executar
recr() {
    echo -e "${BLUE}=== RECONFIGURANDO, COMPILANDO E EXECUTANDO ===${NC}"
    cd build
    if cmake -G "MinGW Makefiles" .. && mingw32-make; then
        echo -e "${GREEN}✅ Reconfiguração e compilação bem-sucedidas!${NC}"
        echo -e "${BLUE}=== EXECUTANDO PROGRAMA ===${NC}"
        ./trabalho_cpp.exe
    else
        echo -e "${RED}❌ Erro na reconfiguração/compilação!${NC}"
        return 1
    fi
}

# Verificar se pasta build existe
check_build_dir() {
    if [ ! -d "build" ]; then
        echo -e "${YELLOW}⚠️  Pasta 'build' não encontrada. Criando...${NC}"
        mkdir build
    fi
}

# Main
main() {
    # Verificar diretório
    check_build_dir
    
    while true; do
        show_menu
        read choice
        
        case $choice in
            1)
                mb
                ;;
            2)
                mbr
                ;;
            3)
                rec
                ;;
            4)
                recr
                ;;
            0)
                echo -e "${BLUE}👋 Saindo...${NC}"
                exit 0
                ;;
            *)
                echo -e "${RED}❌ Opção inválida! Escolha entre 0-4.${NC}"
                ;;
        esac
        
        echo
        echo -n -e "${YELLOW}Pressione Enter para continuar...${NC}"
        read
        clear
    done
}

# Executar main
main