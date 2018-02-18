PROGRAM Ferz(INPUT, OUTPUT);
CONST
  FInName = 'input.txt';
  FOutName = 'output.txt';
  
VAR
  FIn, FOut: TEXT;
  InitSucces: BOOLEAN;
  N, M, nN, nM: INTEGER; 

  FUNCTION InitializeFiles(VAR FIn, FOut: TEXT): BOOLEAN;
  VAR
    Checker: BOOLEAN;
  
  BEGIN {InitializeFiles}
    Checker := FALSE;
    ASSIGN(FIn, FInName);
    {$I-}
    RESET(FIn);
    {$I+};
    IF IOResult <> 0
    THEN
      WRITELN('Error! This file not found...')
    ELSE
      IF EOF(FIn)
      THEN
        WRITELN('File ', FInName, ' is empty!')
      ELSE
        Checker := TRUE;
    ASSIGN(FOut, FOutName);
    REWRITE(FOut);             
    InitializeFiles := Checker
  END; {InitializeFiles}
  
  PROCEDURE FindFerz(VAR N, M: INTEGER);
  TYPE
    PoleArr = ARRAY [1 .. N, 1 .. M] OF CHAR;
  VAR
    Ch: CHAR;
    Arr: PoleArr;
    Counter, I, J, rM, rN: INTEGER;
    
    Procedure Metka (i, j: integer);
   {окраска (пометка грядки) символами '.'}
   Begin
     if Arr[i,j] = '#' then
       begin
         Arr[i,j] := '.';  {пометка клетки (i,j) как пройденной}
         Metka(i+1, j+1);
         Metka(i-1, j-1);
         Metka(i+1, j-1);
         Metka(i-1, j+1); 
         Metka(i+1, j);
         Metka(i-1, j);
         Metka(i, j+1);
         Metka(i, j-1);
       end;
  END;

  BEGIN
    Counter := 0;
    FOR I := 1 TO N
    DO
      BEGIN
        Arr[I, 1] := '.';
        Arr[I, M] := '.';
      END;
    FOR J := 1 TO M
    DO
      BEGIN
        Arr[1, J] := '.';  
        Arr[N, J] := '.';
      END;
    rN := N - 2;
    rM := M - 2;    
    FOR I := 1 TO rN
    DO
      BEGIN
        FOR J := 1 TO rM
        DO
          BEGIN
            READ(FIn, Ch);
            Arr[I + 1, J + 1] := Ch;
          END;
        READLN(FIn);
      END;
    FOR I := 1 TO N
    DO
      BEGIN
        FOR J := 1 TO M
        DO
          BEGIN
            IF (Arr[I, J] = '#')
            THEN
              BEGIN
                Counter := Counter + 1;
                Metka(I, J);
              END  
          END;
      END;
    WRITE(FOut, Counter);
  END;

BEGIN
  InitSucces := InitializeFiles(FIn, FOut);
  IF (InitSucces)
  THEN
    BEGIN
      READ(FIn, N);
      READLN(FIn, M);
      nN := N + 2;
      nM := M + 2;
      FindFerz(nN, nM);
    END
END.
