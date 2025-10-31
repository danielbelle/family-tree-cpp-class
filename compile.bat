@echo off
chcp 65001 > nul
echo Compilando projeto com PCH...

:: ================================================
:: CONFIGURAÇÃO INICIAL E VARIÁVEIS GLOBAIS
:: ================================================

set NEED_COMPILE=0
set NEED_LINK=0
set COMPILE_COUNT=0

:: Executar etapas em sequência
echo Etapa 1: Verificando programas em execução...
call compile\01_check_running.bat

echo Etapa 2: Verificando dependências...
call compile\02_check_dependencies.bat

echo Etapa 3: Detectando mudanças...
call compile\03_detect_changes.bat

echo Etapa 4: Compilando arquivos...
call compile\04_compile_files.bat

echo Etapa 5: Executando programa...
call compile\05_run_program.bat