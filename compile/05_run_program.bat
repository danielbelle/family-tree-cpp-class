@echo off
:: ================================================
:: VERIFICAÇÃO E EXECUÇÃO
:: ================================================

if exist "build\family_tree.exe" (
    echo.
    echo ✅ COMPILAÇÃO CONCLUÍDA COM SUCESSO!
    echo.
    
    if "%NEED_COMPILE%"=="1" (
        if "%COMPILE_COUNT%"=="0" (
            echo 📊 Apenas linkagem realizada
        ) else (
            echo 📊 Compilados: %COMPILE_COUNT% arquivo(s)
        )
        echo.
    ) else (
        echo 🚀 Usando executável pré-compilado.
        echo.
    )
    
    echo 🚀 Iniciando programa em terminal externo...
    timeout 2 > nul
    
    :: Iniciar programa SEM /wait para evitar problemas de redirecionamento
    start "Árvore Genealógica" build\family_tree.exe
    
    echo.
    echo 📋 Programa iniciado em nova janela. Esta janela pode ser fechada.
    echo.
    pause
    exit /b 0
) else (
    echo.
    echo ❌ ERRO: Executável não foi criado!
    echo.
    pause
    exit /b 1
)