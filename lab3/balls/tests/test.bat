set PROGRAM=balls.exe

REM 7    5
%PROGRAM% input7_7.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT7_7.txt
IF ERRORLEVEL 1 GOTO err

REM 1
%PROGRAM% input2_1.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT2_1.txt
IF ERRORLEVEL 1 GOTO err

REM 3
%PROGRAM% input4_3.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT4_3.txt
IF ERRORLEVEL 1 GOTO err

REM 0
%PROGRAM% input5_0.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT5_0.txt
IF ERRORLEVEL 1 GOTO err

REM 1
%PROGRAM% input5_1.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT5_1.txt
IF ERRORLEVEL 1 GOTO err

REM 6
%PROGRAM% input5_6.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT5_6.txt
IF ERRORLEVEL 1 GOTO err

REM 10
%PROGRAM% input8_10.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT8_10.txt
IF ERRORLEVEL 1 GOTO err

REM 17
%PROGRAM% input10_17.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT10_17.txt
IF ERRORLEVEL 1 GOTO err

REM 1249975000   1250025002/1250025002(without i+=)/1249975003(without else)
%PROGRAM% inputMAXimum.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUTMAXimum.txt
IF ERRORLEVEL 1 GOTO err

REM 1249985000   750055004/
%PROGRAM% inputMAXimum3.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUTMAXimum3.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT