@echo off
set /a counter=0

:numbers
set /a counter=%counter%+1
copy 00_pass.res %counter%_pass.res
if %counter% ==20 (goto :eof) else (goto :numbers)


:eof