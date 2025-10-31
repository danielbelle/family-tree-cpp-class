@echo off
chcp 65001 > nul
echo Compilando projeto com PCH...

if not exist "build" mkdir build
taskkill /f /im family_tree.exe >nul 2>&1

:: ================================================
:: COMPILAÇÃO COM PRE-COMPILED HEADERS
:: ================================================

echo [1/4] Gerando Precompiled Header...
g++ -std=c++17 -Iinclude -c include/pch/pch.cpp -o build/pch.o

if %errorlevel% neq 0 (
    echo ERRO: Falha ao gerar PCH!
    pause
    exit /b 1
)

echo [2/4] Compilando main.cpp...
g++ -std=c++17 -Iinclude -include pch/pch.hpp -c src/main.cpp -o build/main.o

if %errorlevel% neq 0 (
    echo ERRO: Falha ao compilar main.cpp!
    pause
    exit /b 1
)

echo [3/4] Compilando interface.cpp...
g++ -std=c++17 -Iinclude -include pch/pch.hpp -c src/interface.cpp -o build/interface.o

if %errorlevel% neq 0 (
    echo ERRO: Falha ao compilar interface.cpp!
    pause
    exit /b 1
)

echo [4/4] Linkando executável...
g++ -o build/family_tree.exe build/main.o build/interface.o build/pch.o

:: ================================================
:: VERIFICAÇÃO E EXECUÇÃO
:: ================================================

if %errorlevel% equ 0 (
    echo.
    echo ✅ Compilacao concluida com sucesso!
    echo.
    echo Iniciando programa em terminal externo...
    start "Árvore Genealógica" build/family_tree.exe
    timeout 1 > nul
    exit
) else (
    echo.
    echo ❌ Erro na linkagem!
    pause
)