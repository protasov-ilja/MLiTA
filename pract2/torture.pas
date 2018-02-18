PROGRAM Torture(INPUT, OUTPUT);


CONST
  MaxN = 100;
  FInName = 'input.txt';
  FOutName = 'output.txt';
    
VAR 
  N, M: INTEGER;
  FIn, FOut: TEXT;
  IsInit: BOOLEAN;
  
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
  
  PROCEDURE FindPath(N, M: INTEGER);
  TYPE
    Actions = (GoDown, GoRight, NoPath);
    Cell = RECORD
             Key: INTEGER;
             Sum: INTEGER;
             Act: Actions;
           END;
    ArrP = ARRAY [1 .. N, 1 .. M] OF Cell;
  VAR
    Arr: ArrP;
    Ch, M1, N1, i, j, MoveDown, MoveRight: INTEGER;
    RightPath, DownPath: BOOLEAN;
        
  BEGIN
    FOR i := 1 TO N
    DO
      BEGIN
        FOR j := 1 TO M
        DO
          BEGIN
            READ(FIn, Ch);
            Arr[i, j].Key := Ch;
            Arr[i, j].Sum := Ch;
            Arr[i, j].Act := NoPath;
          END;
        READLN(FIn);  
      END;
    M1 := M - 1;
    N1 := N - 1;   
    FOR j := M1 DOWNTO 1
    DO
      BEGIN
        Arr[N, j].Sum := Arr[N, j].Key + Arr[N, j + 1].Sum;
        Arr[N, j].Act := GoRight;
      END;
    FOR i := N1 DOWNTO 1
    DO
      BEGIN
        FOR j := M DOWNTO 1
        DO
          BEGIN
            RightPath := FALSE;
            DownPath := FALSE;
            MoveRight := 0;
            MoveDown := 0;
            IF ((i + 1) <= N)
            THEN
              BEGIN
                MoveRight := Arr[i, j].Key + Arr[i + 1, j].Sum;
                RightPath := TRUE;
              END;
            IF ((j + 1) <= M)
            THEN
              BEGIN  
                MoveDown := Arr[i, j].Key + Arr[i, j + 1].Sum;
                DownPath := TRUE;
              END;
            IF (RightPath) AND (DownPath)
            THEN
              BEGIN
                IF (MoveDown > MoveRight)
                THEN
                  BEGIN
                    Arr[i, j].Sum := MoveRight;
                    
                    Arr[i, j].Act := GoRight;
                  END
                ELSE
                  BEGIN
                    Arr[i, j].Sum := MoveDown;
                    
                    Arr[i, j].Act := GoDown;
                  END   
              END
            ELSE
              IF (RightPath)
              THEN
                BEGIN
                  Arr[i, j].Sum := MoveRight;
                  
                  Arr[i, j].Act := GoRight;
                END  
              ELSE
                IF (DownPath)
                THEN
                  BEGIN
                    Arr[i, j].Sum := MoveDown;
                    
                    Arr[i, j].Act := GoDown;
                  END 
          END
      END;
    i := 1;
    j := 1;
    WRITELN(' i');
    WRITELN(FOut, Arr[i, i].Sum); 
    WHILE (Arr[i, i].Key <> Arr[N, M].Key)
    DO
      BEGIN
        WRITELN(FOut, ' Sum ', Arr[i, j].Sum, ' Key ', Arr[i, j].Key, ' ', i, ' ', j);
        IF (Arr[i, j].Act = GoRight)
        THEN
          j := j + 1
        ELSE
          i := i + 1;
            
        IF i > N
        THEN
          i := 1;
        IF j > M
        THEN
          j := 1      
      END;      
  END;
  
BEGIN
  IsInit := InitializeFiles(FIn, FOut);
  IF (IsInit)
  THEN
    BEGIN
      READLN(FIn, N, M);
      FindPath(N, M);
    END;
  CLOSE(FIn);
  CLOSE(FOut);
END.
