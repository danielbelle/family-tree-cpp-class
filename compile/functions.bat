@echo off
:: ================================================
:: FUNÇÕES AUXILIARES
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