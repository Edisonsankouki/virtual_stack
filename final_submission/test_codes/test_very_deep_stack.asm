FUNC LABEL 0(000)
    REF REG 0 STK A(000001000001011)
    CALL VAL 1(0000000100001)
    PRINT STK A(00000 10 101)
    RET(010)
00100
FUNC LABEL 1(001)
    CAL VAL 2(0000001000001)
    RET(010)
00010
FUNC LABEL 2(010)
    CAL VAL 3(0000001100001)
    RET(010)
00010
FUNC LABEL 3(011)
    CAL VAL 4(0000010000001)
    RET(010)
00010
FUNC LABEL 4(100)
    CAL VAL 5(0000010100001)
    RET(010)
00010
FUNC LABEL 5(101)
    CAL VAL 6(0000011000001)
    RET(010)
00010
FUNC LABEL 6(110)
    CAL VAL 7(0000011100001)
    RET(010)
00010
FUNC LABEL 7(111)
    MOV STK A REG 0(000010000010000)
    MOV PTR A VAL 8(00001000 00 00000 11 000)
    RET(010)
00011
