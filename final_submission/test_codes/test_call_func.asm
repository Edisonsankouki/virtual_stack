FUNC LABEL 0(000)
    MOV STK A VAL 0(00000000000000010000)
    REF STK B STK A(00000100000110011)
    MOV REG 0 STK B(000011000001000)
    CAL VAL 1(0000000100001)
    PRINT STK A(0000010101)
    RET(010)
(00110)
FUNC LABEL 1(001)
    MOV STK A RER 0(000010000010000)
    MOV PTR A VAL 1(00000001000000011000)
    RET(010)
(00011)


reuslt 1



