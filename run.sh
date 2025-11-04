#!/bin/bash

# Configurar encoding para UTF-8 Português Brasil
export LANG=pt_BR.UTF-8
export LC_ALL=pt_BR.UTF-8

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# NOVA FUNÇÃO: Verificar se já existe uma instância em execução
check_running_instance() {
    echo -e "${BLUE}🔍 Verificando instâncias em execução...${NC}"
    
    # Verificar processos do family_tree
    if pgrep -f "family_tree.exe" > /dev/null; then
        echo -e "${RED}❌ Já existe uma instância do Sistema de Árvore Genealógica em execução!${NC}"
        echo -e "${YELLOW}📋 Processos encontrados:${NC}"
        
        # Mostrar processos em execução
        pgrep -f "family_tree.exe" | while read pid; do
            echo -e "   PID: $pid - $(ps -p $pid -o command= | head -1)"
        done
        
        echo -e "${YELLOW}💡 Feche a janela anterior antes de abrir uma nova instância.${NC}"
        echo -e "${YELLOW}⏳ Aguardando 3 segundos...${NC}"
        sleep 3
        return 1
    fi
    
    # Verificar se o arquivo executável existe e está em uso
    if [ -f "build/family_tree.exe" ] && fuser "build/family_tree.exe" 2>/dev/null; then
        echo -e "${RED}❌ O executável está sendo usado por outro processo!${NC}"
        echo -e "${YELLOW}💡 Feche a janela anterior antes de abrir uma nova instância.${NC}"
        sleep 3
        return 1
    fi
    
    echo -e "${GREEN}✅ Nenhuma instância em execução encontrada.${NC}"
    return 0
}

# NOVA FUNÇÃO: Matar instâncias existentes (opcional)
kill_existing_instances() {
    echo -e "${YELLOW}⚡ Encerrando instâncias existentes...${NC}"
    pkill -f "family_tree.exe" 2>/dev/null
    
    # Esperar um pouco para os processos terminarem
    sleep 2
    
    # Verificar se ainda há processos
    if pgrep -f "family_tree.exe" > /dev/null; then
        echo -e "${RED}❌ Não foi possível encerrar todas as instâncias.${NC}"
        return 1
    else
        echo -e "${GREEN}✅ Todas as instâncias anteriores foram encerradas.${NC}"
        return 0
    fi
}

# Função para mostrar menu
show_menu() {
    echo -e "${BLUE}=== SISTEMA DE ÁRVORE GENEALÓGICA ===${NC}"
    echo -e "${GREEN}1${NC} - mb   (Apenas compilar)"
    echo -e "${GREEN}2${NC} - run  (Apenas executar)" 
    echo -e "${GREEN}3${NC} - mbr  (Compilar e executar)" 
    echo -e "${GREEN}4${NC} - rec  (Reconfigurar e compilar)"
    echo -e "${GREEN}5${NC} - recr (Reconfigurar, compilar e executar)"
    echo -e "${GREEN}6${NC} - rmvbuild (Remover pasta build)"
    echo -e "${GREEN}7${NC} - kill (Encerrar instâncias em execução)"
    echo -e "${GREEN}9${NC} - exp  (Exportar código)"
    echo -e "${GREEN}0${NC} - Sair"
    echo -n -e "${YELLOW}Escolha uma opção [0-9]: ${NC}"
}

# Função para compilar apenas
mb() {
    echo -e "${BLUE}=== COMPILANDO ===${NC}"
    if [ ! -d "build" ]; then
        mkdir build
    fi
    cd build
    if mingw32-make; then
        echo -e "${GREEN}✅ Compilação bem-sucedida!${NC}"
    else
        echo -e "${RED}❌ Erro na compilação!${NC}"
        return 1
    fi
    cd ..
}

# Função para executar apenas
run() {
    echo -e "${BLUE}=== EXECUTANDO EM NOVO TERMINAL ===${NC}"
    
    # VERIFICAR SE JÁ EXISTE INSTÂNCIA EM EXECUÇÃO - BLOQUEIO RIGOROSO
    if ! check_running_instance; then
        echo -e "${YELLOW}❓ Deseja encerrar as instâncias existentes e executar? (s/N): ${NC}"
        read -r resposta
        if [[ "$resposta" =~ ^[Ss]$ ]]; then
            if ! kill_existing_instances; then
                echo -e "${RED}❌ Não foi possível executar. Tente novamente.${NC}"
                return 1
            fi
        else
            echo -e "${YELLOW}🚫 Execução cancelada.${NC}"
            return 1
        fi
    fi
    
    if [ ! -f "build/family_tree.exe" ]; then
        echo -e "${RED}❌ Executável não encontrado! Compile primeiro.${NC}"
        return 1
    fi
    
    # BLOQUEIO FINAL: Verificar uma última vez antes de executar
    if tasklist //FI "IMAGENAME eq family_tree.exe" 2>/dev/null | grep -q "family_tree.exe"; then
        echo -e "${RED}❌ Instância detectada no último momento! Abortando...${NC}"
        return 1
    fi
    
    # Abrir em novo terminal bash
    echo -e "${YELLOW}🔄 Abrindo novo terminal...${NC}"
    cd build
    
    # NOVO: Usar um título único e verificar durante a execução
    start bash -c "echo '=== SISTEMA DE ÁRVORE GENEALÓGICA ==='; echo 'Executando: ./family_tree.exe'; echo ''; echo '⚠️  INSTÂNCIA ÚNICA - Feche antes de abrir outra'; echo ''; ./family_tree.exe; echo ''; echo '⏹️  Programa finalizado. Pressione Enter para fechar...'"
    
    cd ..
    echo -e "${GREEN}✅ Programa executado em novo terminal!${NC}"
    echo -e "${YELLOW}💡 Lembre-se: feche esta instância antes de abrir outra.${NC}"
}

# Função para compilar e executar
mbr() {
    echo -e "${BLUE}=== COMPILANDO E EXECUTANDO ===${NC}"
    if mb; then
        sleep 1
        run
    fi
}

# Função para reconfigurar e compilar
rec() {
    echo -e "${BLUE}=== RECONFIGURANDO E COMPILANDO ===${NC}"
    if [ ! -d "build" ]; then
        mkdir build
    fi
    cd build
    if cmake -G "MinGW Makefiles" .. && mingw32-make; then
        echo -e "${GREEN}✅ Reconfiguração e compilação bem-sucedidas!${NC}"
    else
        echo -e "${RED}❌ Erro na reconfiguração/compilação!${NC}"
        return 1
    fi
    cd ..
}

# Função para reconfigurar, compilar e executar
recr() {
    echo -e "${BLUE}=== RECONFIGURANDO, COMPILANDO E EXECUTANDO ===${NC}"
    if rec; then
        sleep 1
        run
    fi
}

# Função para remover pasta build
rmvbuild() {
    echo -e "${BLUE}=== REMOVENDO PASTA BUILD ===${NC}"
    
    # Verificar se há instâncias em execução antes de remover (COMPATÍVEL WINDOWS)
    if tasklist //FI "IMAGENAME eq family_tree.exe" 2>/dev/null | grep -q "family_tree.exe"; then
        echo -e "${RED}❌ Existem instâncias em execução!${NC}"
        echo -e "${YELLOW}💡 Encerre as instâncias primeiro com a opção 7.${NC}"
        return 1
    fi
    
    if [ -d "build" ]; then
        rm -rf build
        echo -e "${GREEN}✅ Pasta 'build' removida com sucesso!${NC}"
    else
        echo -e "${YELLOW}ℹ️  Pasta 'build' não existe.${NC}"
    fi
}

# Encerrar instâncias
kill_instances() {
    if ! kill_existing_instances; then
        echo -e "${YELLOW}💡 Você pode tentar encerrar manualmente os processos.${NC}"
    fi
}

# Verificar se já existe uma instância em execução (COMPATÍVEL COM WINDOWS)
check_running_instance() {
    echo -e "${BLUE}🔍 Verificando instâncias em execução...${NC}"
    
    # Verificar processos do family_tree - COMPATÍVEL COM WINDOWS
    if tasklist //FI "IMAGENAME eq family_tree.exe" 2>/dev/null | grep -q "family_tree.exe"; then
        echo -e "${RED}❌ Já existe uma instância do Sistema de Árvore Genealógica em execução!${NC}"
        echo -e "${YELLOW}📋 Processos encontrados:${NC}"
        
        # Mostrar processos em execução
        tasklist //FI "IMAGENAME eq family_tree.exe" 2>/dev/null | grep "family_tree.exe"
        
        echo -e "${YELLOW}💡 Feche a janela anterior antes de abrir uma nova instância.${NC}"
        echo -e "${YELLOW}⏳ Aguardando 3 segundos...${NC}"
        sleep 3
        return 1
    fi
    
    # Verificação alternativa usando PowerShell para mais robustez
    if powershell -Command "Get-Process -Name 'family_tree' -ErrorAction SilentlyContinue" 2>/dev/null | grep -q "family_tree"; then
        echo -e "${RED}❌ Já existe uma instância em execução (verificação PowerShell)!${NC}"
        sleep 3
        return 1
    fi
    
    echo -e "${GREEN}✅ Nenhuma instância em execução encontrada.${NC}"
    return 0
}

# Matar instâncias existentes (COMPATÍVEL COM WINDOWS)
kill_existing_instances() {
    echo -e "${YELLOW}⚡ Encerrando instâncias existentes...${NC}"
    
    # Usar taskkill para Windows
    taskkill //F //IM "family_tree.exe" 2>/dev/null
    
    # Tentativa alternativa com PowerShell
    powershell -Command "Stop-Process -Name 'family_tree' -ErrorAction SilentlyContinue" 2>/dev/null
    
    # Esperar um pouco para os processos terminarem
    sleep 2
    
    # Verificar se ainda há processos
    if tasklist //FI "IMAGENAME eq family_tree.exe" 2>/dev/null | grep -q "family_tree.exe"; then
        echo -e "${RED}❌ Não foi possível encerrar todas as instâncias.${NC}"
        return 1
    else
        echo -e "${GREEN}✅ Todas as instâncias anteriores foram encerradas.${NC}"
        return 0
    fi
}

# Função de exportar codigo
exp() {
    echo -e "${BLUE}=== EXPORTANDO CÓDIGO ===${NC}"
    
    # Verificar se o arquivo shell script existe em doc/
    if [ ! -f "doc/export.sh" ]; then
        echo -e "${RED}❌ ERRO: Arquivo doc/export.sh não encontrado!${NC}"
        return 1
    fi

    # Verificar se o script tem permissão de execução
    if [ ! -x "doc/export.sh" ]; then
        echo -e "${YELLOW}⚠️  Dando permissão de execução para doc/export.sh...${NC}"
        chmod +x "doc/export.sh"
    fi

    # Executar o script shell da pasta doc
    echo -e "${YELLOW}Executando script de exportação de doc/export.sh...${NC}"
    
    if ./doc/export.sh; then
        # Verificar se o arquivo foi criado em build/
        if [ -f "build/export.txt" ]; then
            echo -e "${GREEN}✅ Exportação concluída com sucesso!${NC}"
            echo -e "${GREEN}📄 Arquivo export.txt gerado em build/export.txt${NC}"
        else
            echo -e "${RED}❌ ERRO: build/export.txt não foi criado!${NC}"
            return 1
        fi
    else
        echo -e "${RED}❌ ERRO: Falha na execução do script de exportação${NC}"
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
    # Configurar terminal para UTF-8
    echo -e "🔧 Configurando terminal para UTF-8 Português Brasil..."
    
    # Verificar diretório
    check_build_dir
    
    # MOSTRAR STATUS INICIAL
    echo -e "${BLUE}=== STATUS DO SISTEMA ===${NC}"
    check_running_instance
    
    while true; do
        show_menu
        read choice
        
        case $choice in
            1)
                mb
                ;;
            2)
                run
                ;;
            3)
                mbr
                ;;
            4)
                rec
                ;;
            5)
                recr
                ;;
            6)
                rmvbuild
                ;;
            7)
                kill_instances
                ;;
            9)
                exp
                ;;
            0)
                echo -e "${BLUE}👋 Saindo...${NC}"
                # Verificar se há instâncias em execução antes de sair (WINDOWS)
                if tasklist //FI "IMAGENAME eq family_tree.exe" 2>/dev/null | grep -q "family_tree.exe"; then
                    echo -e "${YELLOW}⚠️  Aviso: Existem instâncias do programa em execução.${NC}"
                fi
                clear
                exit 0
                ;;
            clear)
                clear
                ;;
            *)
                echo -e "${RED}❌ Opção inválida! Escolha entre 0-9.${NC}"
                ;;
        esac
    done
}

# Executar main
main