set PROGRAM="%~1"

REM input00.txt
%PROGRAM% input00.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt output00.txt
IF ERRORLEVEL 1 GOTO err

REM input0.txt
%PROGRAM% input0.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt output0.txt
IF ERRORLEVEL 1 GOTO err

REM input1.txt
%PROGRAM% input1.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt output1.txt
IF ERRORLEVEL 1 GOTO err

REM input2.txt
%PROGRAM% input2.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt output2.txt
IF ERRORLEVEL 1 GOTO err

REM input3.txt
%PROGRAM% input3.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt output3.txt
IF ERRORLEVEL 1 GOTO err

REM input4.txt
%PROGRAM% input4.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt output4.txt
IF ERRORLEVEL 1 GOTO err

REM input5.txt
%PROGRAM% input5.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt output5.txt
IF ERRORLEVEL 1 GOTO err

REM input6.txt
%PROGRAM% input6.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt output6.txt
IF ERRORLEVEL 1 GOTO err

REM input7.txt
%PROGRAM% input7.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt output7.txt
IF ERRORLEVEL 1 GOTO err

REM input8.txt
%PROGRAM% input8.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt output8.txt
IF ERRORLEVEL 1 GOTO err

REM input9.txt
%PROGRAM% input9.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt output9.txt
IF ERRORLEVEL 1 GOTO err

REM input10.txt
%PROGRAM% input10.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt output10.txt
IF ERRORLEVEL 1 GOTO err

REM input11.txt
%PROGRAM% input11.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt output11.txt
IF ERRORLEVEL 1 GOTO err

REM input12.txt
%PROGRAM% input12.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt output12.txt
IF ERRORLEVEL 1 GOTO err

REM input13.txt
%PROGRAM% input13.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt output13.txt
IF ERRORLEVEL 1 GOTO err

REM input14.txt
%PROGRAM% input14.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt output14.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT

:err
ECHO Program testing failed :-(
EXIT