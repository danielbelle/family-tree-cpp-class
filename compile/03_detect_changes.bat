@echo off
:: ================================================
:: SISTEMA DE COMPILAÇÃO INCREMENTAL
:: ================================================

set EXECUTABLE=build\family_tree.exe

:: Verificar se o executável existe
if not exist "%EXECUTABLE%" (
    echo ⚠️  Executável não encontrado. Compilação completa necessária.
    set NEED_COMPILE=1
    set NEED_LINK=1
    goto :COMPILE_START
)

:: Inicializar variáveis de compilação
set COMPILE_PCH=0
set COMPILE_MAIN=0
set COMPILE_INTERFACE=0
set COMPILE_EXECUCAO=0
set COMPILE_OPERACOES=0
set COMPILE_PERSISTENCIA=0

echo 🔄 Verificando mudanças incrementais...

:: Verificar PCH
call :CHECK_FILE "include\pch\pch.cpp" "build\o\pch.o" COMPILE_PCH

:: Verificar arquivos principais
call :CHECK_FILE "src\main.cpp" "build\o\main.o" COMPILE_MAIN
call :CHECK_FILE "src\interface.cpp" "build\o\interface.o" COMPILE_INTERFACE
call :CHECK_FILE "src\execucao.cpp" "build\o\execucao.o" COMPILE_EXECUCAO
call :CHECK_FILE "src\operacoes.cpp" "build\o\operacoes.o" COMPILE_OPERACOES
call :CHECK_FILE "src\persistencia.cpp" "build\o\persistencia.o" COMPILE_PERSISTENCIA

:: Verificar headers que podem afetar múltiplos arquivos
call :CHECK_HEADERS

:: Se algum arquivo precisa ser recompilado, setar flags
if "%COMPILE_PCH%"=="1" set NEED_COMPILE=1
if "%COMPILE_MAIN%"=="1" set NEED_COMPILE=1 & set NEED_LINK=1
if "%COMPILE_INTERFACE%"=="1" set NEED_COMPILE=1 & set NEED_LINK=1
if "%COMPILE_EXECUCAO%"=="1" set NEED_COMPILE=1 & set NEED_LINK=1
if "%COMPILE_OPERACOES%"=="1" set NEED_COMPILE=1 & set NEED_LINK=1
if "%COMPILE_PERSISTENCIA%"=="1" set NEED_COMPILE=1 & set NEED_LINK=1

if "%NEED_COMPILE%"=="0" (
    echo ✅ Nenhuma mudança detectada. Usando executável existente.
    goto :END_DETECT
)

:COMPILE_START
echo.
echo 📦 Compilação incremental necessária.

:END_DETECT
goto :EOF

:: ================================================
:: FUNÇÕES LOCAIS
:: ================================================

:CHECK_FILE
setlocal
set "SOURCE=%~1"
set "TARGET=%~2"
set "RESULT_VAR=%~3"

set "NEED_RECOMPILE=0"

:: Verificar se o arquivo objeto não existe
if not exist "%TARGET%" (
    set NEED_RECOMPILE=1
    goto :CHECK_FILE_END
)

:: Verificar timestamp do fonte vs objeto
for %%I in ("%SOURCE%") do set SOURCE_TIME=%%~tI
for %%J in ("%TARGET%") do set TARGET_TIME=%%~tJ

if "%SOURCE_TIME%" gtr "%TARGET_TIME%" (
    set NEED_RECOMPILE=1
)

:CHECK_FILE_END
endlocal & set %RESULT_VAR%=%NEED_RECOMPILE%
exit /b

:CHECK_HEADERS
setlocal enabledelayedexpansion

set HEADERS_CHANGED=0
set TEMP_MD5=build\md5\temp_header.md5

:: Verificar cada header individualmente
if exist "include\core\estruturas.hpp" (
    certutil -hashfile "include\core\estruturas.hpp" MD5 | find /v ":" | find /v "CertUtil" | find /v "MD5 hash" > "!TEMP_MD5!" 2>nul
    if exist "build\md5\header_estruturas.md5" (
        fc "build\md5\header_estruturas.md5" "!TEMP_MD5!" >nul 2>&1
        if !errorlevel! neq 0 (
            set HEADERS_CHANGED=1
            echo 📦 Header modificado: estruturas.hpp
        )
    ) else (
        set HEADERS_CHANGED=1
    )
    if exist "!TEMP_MD5!" copy "!TEMP_MD5!" "build\md5\header_estruturas.md5" >nul 2>nul
)

if exist "include\core\execucao.hpp" (
    certutil -hashfile "include\core\execucao.hpp" MD5 | find /v ":" | find /v "CertUtil" | find /v "MD5 hash" > "!TEMP_MD5!" 2>nul
    if exist "build\md5\header_execucao.md5" (
        fc "build\md5\header_execucao.md5" "!TEMP_MD5!" >nul 2>&1
        if !errorlevel! neq 0 (
            set HEADERS_CHANGED=1
            echo 📦 Header modificado: execucao.hpp
        )
    ) else (
        set HEADERS_CHANGED=1
    )
    if exist "!TEMP_MD5!" copy "!TEMP_MD5!" "build\md5\header_execucao.md5" >nul 2>nul
)

if exist "include\core\main.hpp" (
    certutil -hashfile "include\core\main.hpp" MD5 | find /v ":" | find /v "CertUtil" | find /v "MD5 hash" > "!TEMP_MD5!" 2>nul
    if exist "build\md5\header_main.md5" (
        fc "build\md5\header_main.md5" "!TEMP_MD5!" >nul 2>&1
        if !errorlevel! neq 0 (
            set HEADERS_CHANGED=1
            echo 📦 Header modificado: main.hpp
        )
    ) else (
        set HEADERS_CHANGED=1
    )
    if exist "!TEMP_MD5!" copy "!TEMP_MD5!" "build\md5\header_main.md5" >nul 2>nul
)

if exist "include\core\operacoes.hpp" (
    certutil -hashfile "include\core\operacoes.hpp" MD5 | find /v ":" | find /v "CertUtil" | find /v "MD5 hash" > "!TEMP_MD5!" 2>nul
    if exist "build\md5\header_operacoes.md5" (
        fc "build\md5\header_operacoes.md5" "!TEMP_MD5!" >nul 2>&1
        if !errorlevel! neq 0 (
            set HEADERS_CHANGED=1
            echo 📦 Header modificado: operacoes.hpp
        )
    ) else (
        set HEADERS_CHANGED=1
    )
    if exist "!TEMP_MD5!" copy "!TEMP_MD5!" "build\md5\header_operacoes.md5" >nul 2>nul
)

if exist "include\core\persistencia.hpp" (
    certutil -hashfile "include\core\persistencia.hpp" MD5 | find /v ":" | find /v "CertUtil" | find /v "MD5 hash" > "!TEMP_MD5!" 2>nul
    if exist "build\md5\header_persistencia.md5" (
        fc "build\md5\header_persistencia.md5" "!TEMP_MD5!" >nul 2>&1
        if !errorlevel! neq 0 (
            set HEADERS_CHANGED=1
            echo 📦 Header modificado: persistencia.hpp
        )
    ) else (
        set HEADERS_CHANGED=1
    )
    if exist "!TEMP_MD5!" copy "!TEMP_MD5!" "build\md5\header_persistencia.md5" >nul 2>nul
)

if exist "include\pch\pch.hpp" (
    certutil -hashfile "include\pch\pch.hpp" MD5 | find /v ":" | find /v "CertUtil" | find /v "MD5 hash" > "!TEMP_MD5!" 2>nul
    if exist "build\md5\header_pch.md5" (
        fc "build\md5\header_pch.md5" "!TEMP_MD5!" >nul 2>&1
        if !errorlevel! neq 0 (
            set HEADERS_CHANGED=1
            echo 📦 Header modificado: pch.hpp
        )
    ) else (
        set HEADERS_CHANGED=1
    )
    if exist "!TEMP_MD5!" copy "!TEMP_MD5!" "build\md5\header_pch.md5" >nul 2>nul
)

:: Limpar temporário
if exist "!TEMP_MD5!" del "!TEMP_MD5!"

:: Se headers mudaram, recompilar tudo exceto PCH
if "!HEADERS_CHANGED!"=="1" (
    echo 📦 Headers modificados - recompilando arquivos dependentes...
    set COMPILE_MAIN=1
    set COMPILE_INTERFACE=1
    set COMPILE_EXECUCAO=1
    set COMPILE_OPERACOES=1
    set COMPILE_PERSISTENCIA=1
    set NEED_LINK=1
)

endlocal & exit /b