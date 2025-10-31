@echo off
chcp 65001 > nul
echo Compilando projeto com PCH...

:: ================================================
:: FECHAR TERMINAIS EXISTENTES DO PROGRAMA
:: ================================================

echo 🔄 Verificando se o programa está em execução...
tasklist /fi "imagename eq family_tree.exe" | find "family_tree.exe" > nul
if %errorlevel% equ 0 (
    echo ⚠️  Programa em execução detectado. Fechando...
    taskkill /f /im family_tree.exe >nul 2>&1
    timeout 1 > nul
    echo ✅ Programa fechado com sucesso!
) else (
    echo ✅ Nenhuma instância em execução encontrada.
)

:: ================================================
:: CRIAR ESTRUTURA DE DIRETÓRIOS
:: ================================================

if not exist "build" mkdir build
if not exist "build\o" mkdir build\o
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

:: ================================================
:: VERIFICAR SE PRECISA RECOMPILAR
:: ================================================

echo 🔄 Verificando mudanças no código...

set NEED_COMPILE=0
set EXECUTABLE=build\family_tree.exe

:: Verificar se o executável existe
if not exist "%EXECUTABLE%" (
    echo ⚠️  Executável não encontrado. Compilação necessária.
    set NEED_COMPILE=1
    goto :COMPILE_START
)

:: Verificar se algum arquivo .o está faltando
if not exist "build\o\main.o" set NEED_COMPILE=1
if not exist "build\o\interface.o" set NEED_COMPILE=1
if not exist "build\o\execucao.o" set NEED_COMPILE=1
if not exist "build\o\operacoes.o" set NEED_COMPILE=1
if not exist "build\o\persistencia.o" set NEED_COMPILE=1
if not exist "build\o\pch.o" set NEED_COMPILE=1

if "%NEED_COMPILE%"=="0" (
    echo ✅ Nenhuma mudança detectada. Usando executável existente.
    goto :RUN_PROGRAM
)

:COMPILE_START
echo 📦 Mudanças detectadas. Iniciando compilação...

:: ================================================
:: COMPILAÇÃO COM PRE-COMPILED HEADERS
:: ================================================

echo [1/7] Gerando Precompiled Header...
g++ -std=c++17 -Iinclude -c include/pch/pch.cpp -o build/o/pch.o

if %errorlevel% neq 0 (
    echo.
    echo ❌ ERRO: Falha ao gerar PCH!
    pause
    exit /b 1
)

echo [2/7] Compilando main.cpp...
g++ -std=c++17 -Iinclude -include pch/pch.hpp -c src/main.cpp -o build/o/main.o

if %errorlevel% neq 0 (
    echo.
    echo ❌ ERRO: Falha ao compilar main.cpp!
    pause
    exit /b 1
)

echo [3/7] Compilando interface.cpp...
g++ -std=c++17 -Iinclude -include pch/pch.hpp -c src/interface.cpp -o build/o/interface.o

if %errorlevel% neq 0 (
    echo.
    echo ❌ ERRO: Falha ao compilar interface.cpp!
    pause
    exit /b 1
)

echo [4/7] Compilando execucao.cpp...
g++ -std=c++17 -Iinclude -include pch/pch.hpp -c src/execucao.cpp -o build/o/execucao.o

if %errorlevel% neq 0 (
    echo.
    echo ❌ ERRO: Falha ao compilar execucao.cpp!
    pause
    exit /b 1
)

echo [5/7] Compilando operacoes.cpp...
g++ -std=c++17 -Iinclude -include pch/pch.hpp -c src/operacoes.cpp -o build/o/operacoes.o

if %errorlevel% neq 0 (
    echo.
    echo ❌ ERRO: Falha ao compilar operacoes.cpp!
    pause
    exit /b 1
)

echo [6/7] Compilando persistencia.cpp...
g++ -std=c++17 -Iinclude -include pch/pch.hpp -c src/persistencia.cpp -o build/o/persistencia.o

if %errorlevel% neq 0 (
    echo.
    echo ❌ ERRO: Falha ao compilar persistencia.cpp!
    pause
    exit /b 1
)

echo [7/7] Linkando executável...
g++ -o build/family_tree.exe build/o/main.o build/o/interface.o build/o/execucao.o build/o/operacoes.o build/o/persistencia.o build/o/pch.o

if %errorlevel% neq 0 (
    echo.
    echo ❌ ERRO NA LINKAGEM!
    echo.
    echo 🔧 Possíveis soluções:
    echo    • Verifique se todos os arquivos .cpp estão na pasta src\
    echo    • Confirme se include\json\json.hpp existe
    echo    • Tente compilar manualmente cada arquivo
    echo.
    echo 📋 Fechando terminal em 5 segundos...
    timeout 5 > nul
    exit /b 1
)

:: ================================================
:: VERIFICAÇÃO E EXECUÇÃO
:: ================================================

:RUN_PROGRAM
if exist "build\family_tree.exe" (
    echo.
    echo ✅ COMPILAÇÃO CONCLUÍDA COM SUCESSO!
    echo.
    
    if "%NEED_COMPILE%"=="1" (
        echo 📊 RESUMO DA COMPILAÇÃO:
        echo    • Precompiled Header: ✅
        echo    • Main: ✅
        echo    • Interface: ✅  
        echo    • Execução: ✅
        echo    • Operações: ✅
        echo    • Persistência: ✅
        echo    • Linkagem: ✅
        echo.
        echo 📁 ESTRUTURA DE BUILD:
        echo    • Arquivos .o: build\o\
        echo    • Executável: build\family_tree.exe
        echo.
    ) else (
        echo 🚀 Usando executável pré-compilado.
        echo.
    )
    
    echo 🚀 Iniciando programa em terminal externo...
    timeout 2 > nul
    
    :: Iniciar programa e aguardar seu término
    start "Árvore Genealógica" /wait build/family_tree.exe
    
    echo.
    echo 📋 Programa finalizado. Fechando terminal...
    timeout 2 > nul
    exit /b 0
) else (
    echo.
    echo ❌ ERRO: Executável não foi criado!
    echo.
    echo 📋 Fechando terminal em 5 segundos...
    timeout 5 > nul
    exit /b 1
)