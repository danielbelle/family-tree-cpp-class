@echo off
echo 🔄 Verificando se o programa está em execução...
tasklist /fi "imagename eq family_tree.exe" | find /i "family_tree.exe" > nul
if %errorlevel% equ 0 (
    echo ⚠️  Programa em execução detectado. Fechando...
    
    :: Tentar fechar graciosamente primeiro
    taskkill /im family_tree.exe >nul 2>&1
    timeout 2 > nul
    
    :: Verificar se ainda está rodando e forçar se necessário
    tasklist /fi "imagename eq family_tree.exe" | find /i "family_tree.exe" > nul
    if %errorlevel% equ 0 (
        echo ⚠️  Forçando fechamento...
        taskkill /f /im family_tree.exe >nul 2>&1
        timeout 1 > nul
    )
    
    echo ✅ Programa fechado com sucesso!
) else (
    echo ✅ Nenhuma instância em execução encontrada.
)