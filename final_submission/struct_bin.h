struct bin_data // a struct to store binary data;
{
    unsigned char* data;
    int len;

};


#define Byte unsigned char

#define Command unsigned short int

#define MAX_PRO_SIZE 256

#define MAX_RAM_SIZE 256

struct cpu{//the struct of the virtual machine.

    Command pro_mem[MAX_PRO_SIZE][5];
    
    Byte ram[MAX_RAM_SIZE];
    

    /*Byte GE_R[7];7
   

    Byte GE_R[6];6

    Byte GE_R[5];5
    Byte GE_R[4];4
    */
    Byte GE_R[8];



};


enum op_code{
    MOV,CAL,RET,REF,ADD,PRINT,NOT,EQU,VAL,REG,STK,PTR,FUNC

};


static char stack_name[32][2] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","X","T","U","V","W","X","Y","Z","a","b","c","d","e","f"};

// this file is for basic structure storage