set PROGRAM=substraction.exe

REM ������ ��������� � 1-� ������� � 1-� �������
%PROGRAM% input1.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT1.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � 1-� ������� � 1-� �������
%PROGRAM% input2.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT2.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � 1-� ������� � 1-� �������
%PROGRAM% input3.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT3.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � 1-� ������� � 1-� �������
%PROGRAM% input4.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT4.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � 1-� ������� � 1-� �������
%PROGRAM% input5.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT5.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � 1-� ������� � 1-� �������
%PROGRAM% input6.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT6.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � 1-� ������� � 1-� �������
%PROGRAM% input7.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT7.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � 1-� ������� � 1-� �������
%PROGRAM% input8.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT8.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � 1-� ������� � 1-� �������
%PROGRAM% input9.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT9.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � 1-� ������� � 1-� �������
%PROGRAM% input10.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt OUTPUT10.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT