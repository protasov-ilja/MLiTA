PROGRAM Kavadrat(INPUT, OUTPUT);
VAR
  FIn, FOut: TEXT;
  InitSucces: BOOLEAN;
  N: INTEGER; 
   
  FUNCTION InitializeFiles(VAR FIn, FOut: TEXT): BOOLEAN;
  { ????????????? ?????? ????? ?????? }
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
  
  PROCEDURE FindMinSquears(VAR FIn, FOut: TEXT; VAR N: INTEGER);
  TYPE
    ArrK = ARRAY [1 .. N] OF INTEGER;
  VAR
    C: ARRAY [1 .. N] OF INTEGER; 
    Arr: ArrK;
    Beg, I: INTEGER;
      
  BEGIN
    FOR I := 1 TO N
    DO
      BEGIN
        IF C 
        THEN
          BEGIN
          END
      END
  END;
  
  
BEGIN {Kavadrat}
  InitSucces := InitializeFiles(FIn, FOut);
  IF (InitSucces)
  THEN
    BEGIN
      READLN(FIn, N);
      WorkWithData(FIn, FOut, N)
    END;
  CLOSE(FIn);
  CLOSE(FOut);     
END. {Kavadrat}
