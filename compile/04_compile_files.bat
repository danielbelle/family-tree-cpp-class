@echo off
:: ================================================
:: COMPILAÇÃO INCREMENTAL
:: ================================================

if "%NEED_COMPILE%"=="0" goto :END_COMPILE

set COMPILE_COUNT=0

:: Compilar PCH se necessário
if "%COMPILE_PCH%"=="1" (
    set /a COMPILE_COUNT+=1
    echo [!COMPILE_COUNT!] Recompilando Precompiled Header...
    g++ -std=c++17 -Iinclude -c include/pch/pch.cpp -o build/o/pch.o
    if %errorlevel% neq 0 goto :COMPILE_ERROR
)

:: Compilar arquivos fonte se necessário
if "%COMPILE_MAIN%"=="1" (
    set /a COMPILE_COUNT+=1
    echo [!COMPILE_COUNT!] Recompilando main.cpp...
    g++ -std=c++17 -Iinclude -include pch/pch.hpp -c src/main.cpp -o build/o/main.o
    if %errorlevel% neq 0 goto :COMPILE_ERROR
)

if "%COMPILE_INTERFACE%"=="1" (
    set /a COMPILE_COUNT+=1
    echo [!COMPILE_COUNT!] Recompilando interface.cpp...
    g++ -std=c++17 -Iinclude -include pch/pch.hpp -c src/interface.cpp -o build/o/interface.o
    if %errorlevel% neq 0 goto :COMPILE_ERROR
)

if "%COMPILE_EXECUCAO%"=="1" (
    set /a COMPILE_COUNT+=1
    echo [!COMPILE_COUNT!] Recompilando execucao.cpp...
    g++ -std=c++17 -Iinclude -include pch/pch.hpp -c src/execucao.cpp -o build/o/execucao.o
    if %errorlevel% neq 0 goto :COMPILE_ERROR
)

if "%COMPILE_OPERACOES%"=="1" (
    set /a COMPILE_COUNT+=1
    echo [!COMPILE_COUNT!] Recompilando operacoes.cpp...
    g++ -std=c++17 -Iinclude -include pch/pch.hpp -c src/operacoes.cpp -o build/o/operacoes.o
    if %errorlevel% neq 0 goto :COMPILE_ERROR
)

if "%COMPILE_PERSISTENCIA%"=="1" (
    set /a COMPILE_COUNT+=1
    echo [!COMPILE_COUNT!] Recompilando persistencia.cpp...
    g++ -std=c++17 -Iinclude -include pch/pch.hpp -c src/persistencia.cpp -o build/o/persistencia.o
    if %errorlevel% neq 0 goto :COMPILE_ERROR
)

:: Linkar se necessário
if "%NEED_LINK%"=="1" (
    echo 🔗 Linkando executável...
    g++ -o build/family_tree.exe build/o/main.o build/o/interface.o build/o/execucao.o build/o/operacoes.o build/o/persistencia.o build/o/pch.o
    if %errorlevel% neq 0 goto :LINK_ERROR
)

goto :END_COMPILE

:COMPILE_ERROR
echo.
echo ❌ ERRO: Falha na compilação!
pause
exit /b 1

:LINK_ERROR
echo.
echo ❌ ERRO NA LINKAGEM!
echo.
echo 🔧 Possíveis soluções:
echo    • Verifique se todos os arquivos .cpp estão na pasta src\
echo    • Confirme se include\json\json.hpp existe
echo    • Tente compilar manualmente cada arquivo
echo.
pause
exit /b 1

:END_COMPILE