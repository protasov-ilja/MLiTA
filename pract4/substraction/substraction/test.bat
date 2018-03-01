set PROGRAM=substraction.exe

REM запуск программы с 1-й строкой и 1-й заменой
%PROGRAM% input1.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT1.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с 1-й строкой и 1-й заменой
%PROGRAM% input2.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT2.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с 1-й строкой и 1-й заменой
%PROGRAM% input3.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT3.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с 1-й строкой и 1-й заменой
%PROGRAM% input4.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT4.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с 1-й строкой и 1-й заменой
%PROGRAM% input5.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT5.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с 1-й строкой и 1-й заменой
%PROGRAM% input6.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT6.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с 1-й строкой и 1-й заменой
%PROGRAM% input7.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT7.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с 1-й строкой и 1-й заменой
%PROGRAM% input8.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT8.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с 1-й строкой и 1-й заменой
%PROGRAM% input9.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT9.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с 1-й строкой и 1-й заменой
%PROGRAM% input10.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT10.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT