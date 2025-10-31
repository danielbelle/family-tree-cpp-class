@echo off
:: ================================================
:: CRIAR ESTRUTURA DE DIRETÓRIOS
:: ================================================

if not exist "build" mkdir build
if not exist "build\o" mkdir build\o
if not exist "build\md5" mkdir build\md5
if not exist "data" mkdir data

:: ================================================
:: VERIFICAR SE A BIBLIOTECA JSON EXISTE
:: ================================================

if not exist "include\json\json.hpp" (
    echo.
    echo ❌ ERRO: Biblioteca JSON não encontrada!
    echo.
    echo 📥 Faça o download do json.hpp:
    echo 1. Crie a pasta: include\json\
    echo 2. Baixe de: https://github.com/nlohmann/json/releases
    echo 3. Coloque o arquivo json.hpp em include\json\
    echo.
    pause
    exit /b 1
)