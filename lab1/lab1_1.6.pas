PROGRAM SumDominos(INPUT, OUTPUT);
{ 
1.6. Домино (7)
Имеется N костей игры домино. На каждой кости имеется два числа (каждое от 0 до 6). 
Требуется написать программу, которая будет определять максимальное число, 
составленное из цифр на костях цепочки, составленной по правилам домино из имеющихся костей.
Ввод. 
  Первая строка входного файла содержит целое число N - количество костей (2   N   20).
  Следующие N строк содержат два целых числа X и Y (0   X, Y   6), разделенные пробелом.
Вывод. 
  В выходной файл необходимо вывести максимальное целое число, цифры 
  которого соответствуют значению костей в цепочке.

Выполнил студент группы ПС-21 Протасов Илья
Среда разработки Dev+Gnu Pascal 1.9.4.13
}
CONST
  FOutName = 'OUTPUT.txt';
  FInName = 'INPUT.txt';
  maxDCount = 20;
  minDCount = 2;
 
TYPE
  NodePtr = ^Node;
  Node = RECORD         
           LD, RD: INTEGER;
           Use: BOOLEAN;
           Next: INTEGER;
           Untaken, Taken: INTEGER;
           Lvl: INTEGER;
         END;

VAR
  FIn, FOut: TEXT;
  InitSucces: BOOLEAN;
  N: INTEGER; 
   
  FUNCTION InitializeFiles(VAR FIn, FOut: TEXT): BOOLEAN;
  { Инициализация файлов ввода вывода }
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

  PROCEDURE WorkWithData(VAR FIn, FOut: TEXT; VAR N: INTEGER);   
  TYPE
    TStr = STRING[N * 2];
    DominosArr = ARRAY [1 .. N] OF Node;
    MaxPath = RECORD         
                MaxSum: INTEGER;
                MaxStr: TStr;
                MaxLvl: INTEGER;
              END; 
    
  VAR
    i, maxSize: INTEGER;
    MaxValues: MaxPath; 
    DArr: DominosArr;
    CreateSucces: BOOLEAN;
  
    FUNCTION CreateArr(VAR N: INTEGER; VAR DArr: DominosArr): BOOLEAN;
    VAR
      Num1, Num2, ArrLen: INTEGER;
      Checker: BOOLEAN;
  
      PROCEDURE InitArrCase(VAR Domino: Node; NumL, NumR: INTEGER);
      BEGIN {InitArrCase}
        Domino.LD := NumL;
        Domino.RD := NumR;
        Domino.Use := FALSE;
        Domino.Next := -1;
        Domino.Lvl := 0
      END; {InitArrCase}            
  
    BEGIN {CreateArr}
      Checker := TRUE;
      ArrLen := 1;
      WHILE (NOT(EOF(FIn)) AND (ArrLen <= N) AND Checker)
      DO
        BEGIN
          READ(FIn, Num1);
          IF ((Num1 >= 0) AND (Num1 <= 6))
          THEN
            BEGIN
              IF NOT(EOLN(FIn))
              THEN
                BEGIN
                  READ(FIn, Num2);
                  IF ((Num2 >= 0) AND (Num2 <= 6))
                  THEN
                    InitArrCase(DArr[ArrLen], Num1, Num2)
                  ELSE
                    Checker := FALSE;
                END
              ELSE
                Checker := FALSE;
            END
          ELSE
            Checker := FALSE; 
          ArrLen := ArrLen + 1;
          READLN(FIn)    
        END;
      IF (ArrLen <> N + 1)
      THEN
        Checker := FALSE;
      CreateArr := Checker         
    END; {CreateArr}
    
    PROCEDURE CompPath(First, LastNode: INTEGER; VAR MaxValues: MaxPath; VAR DArr: DominosArr);            
      VAR
        NextNode, Sum: INTEGER;
        S, SBuf: TStr;
        
      BEGIN {CompPath}
        S := '';
        Sum := 0;
        NextNode := First;
        WHILE (NextNode <> -1)
        DO
          BEGIN
            Sum := DArr[NextNode].Taken + DArr[NextNode].Untaken;
            NextNode := DArr[NextNode].Next
          END;
        IF (DArr[LastNode].Lvl >= MaxValues.MaxLvl)
        THEN
          BEGIN
            NextNode := First;
            WHILE (NextNode <> -1)
            DO
              BEGIN
                Str(DArr[NextNode].Untaken, SBuf);
                S := S + SBuf;
                Str(DArr[NextNode].Taken, SBuf);
                S := S + SBuf;
                NextNode := DArr[NextNode].Next
              END;
            IF ((S > MaxValues.MaxStr) AND (length(S) >= length(MaxValues.MaxStr))) OR ((S = MaxValues.MaxStr) AND (length(S) > length(MaxValues.MaxStr)))   
            THEN
              BEGIN
                MaxValues.MaxSum := Sum;
                MaxValues.MaxStr := S;
                MaxValues.MaxLvl := DArr[LastNode].Lvl                
              END  
          END;
          
      END; {CompPath}  

    PROCEDURE FindPath(N: INTEGER; VAR DArr: DominosArr);
    VAR
      First, CurrD, NextD, CurrN, CurrLvl, Buf: INTEGER;
  
      PROCEDURE FindNextNode(PrevD, CurrD: INTEGER; VAR Tn, Utn: INTEGER);
      BEGIN {FindNextNode}
        DArr[CurrD].Lvl := DArr[PrevD].Lvl + 1;
        DArr[CurrD].Taken := Tn;
        DArr[CurrD].Untaken := Utn;
        DArr[CurrD].Use := TRUE;
        IF (CurrD = N)
        THEN
          NextD := 1
        ELSE
          NextD := CurrD + 1;
        WHILE (NextD <> CurrD)
        DO
          BEGIN
            IF DArr[NextD].Use = FALSE
            THEN
              BEGIN
                IF (DArr[NextD].LD = DArr[CurrD].Taken)
                THEN
                  BEGIN
                    DArr[CurrD].Next := NextD;
                    FindNextNode(CurrD, NextD, DArr[NextD].RD, DArr[NextD].LD)
                  END;
                IF (DArr[NextD].RD = DArr[CurrD].Taken) AND (DArr[NextD].LD <> DArr[NextD].RD)
                THEN
                  BEGIN
                    DArr[CurrD].Next := NextD;
                    FindNextNode(CurrD, NextD, DArr[NextD].LD, DArr[NextD].RD)
                  END
              END;          
            NextD := NextD + 1;
            IF (NextD > N)
            THEN
              NextD := 1   
          END;
        DArr[CurrD].Next := -1;
        CompPath(First, CurrD, MaxValues, DArr);
        DArr[CurrD].Use := FALSE; 
        DArr[CurrD].Lvl := DArr[CurrD].Lvl - 1     
      END; {FindNextNode}
  
    BEGIN {FindPath}
      CurrD := 1;
      WHILE CurrD <= N
      DO
        BEGIN
          First := CurrD;
          IF (DArr[CurrD].RD <> 0)
          THEN 
            FindNextNode(CurrD, CurrD, DArr[CurrD].LD, DArr[CurrD].RD);
          IF ((DArr[CurrD].LD <> DArr[CurrD].RD) AND (DArr[CurrD].LD <> 0))
          THEN
            FindNextNode(CurrD, CurrD, DArr[CurrD].RD, DArr[CurrD].LD);
          CurrD := CurrD + 1
        END                                   
    END; {FindPath}     
  
  BEGIN {WorkWithData}
    maxSize := N * 2;
    MaxValues.MaxSum := -1;
    MaxValues.MaxLvl := 0;
    MaxValues.MaxStr := '';
    CreateSucces := CreateArr(N, DArr); 
    IF (CreateSucces)
    THEN
      BEGIN
        FindPath(N, DArr);
        IF (MaxValues.MaxSum <> -1)
        THEN
          BEGIN
            WRITE(FOut, MaxValues.MaxStr);
          END  
        ELSE
          WRITE(FOut, 0)   
      END
  END; {WorkWithData} 

BEGIN {SumDominos}
  InitSucces := InitializeFiles(FIn, FOut);
  IF (InitSucces)
  THEN
    BEGIN
      READLN(FIn, N);
      IF (N >= minDCount)
      THEN
        WorkWithData(FIn, FOut, N)
    END;
  CLOSE(FIn);
  CLOSE(FOut);     
END. {SumDominos}
