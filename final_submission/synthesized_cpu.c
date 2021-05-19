#include "synthesized_cpu.h"
//this function is for reading the binary data.
struct bin_data get_bin_data(char* filename){
    FILE* f1 = fopen(filename,"rb");


   

    struct bin_data result;



    unsigned char* x;


    int y;

    //go to end of file first
    fseek(f1,0,SEEK_END);

    int size  = ftell(f1);
   


    x = (unsigned char*)malloc(sizeof(unsigned char)*256);



    int i = 1;
    //read 1 by 1 from end to start
    while(i <= size){
        fseek(f1,-i,SEEK_END);
        fread(&y,1,1,f1);

        

        x[i-1] = y;

        i++;
    }

    fclose(f1);


    result.data = x;
    result.len = size;


    return result;

}

//this function will give the last few bits you want in a byte.
int fetchbit(int num,int in){

    int u = 255;

    u = u>>(8-num);

    int item = u&in;

    return item;



}
//this function is for moving a whole byte array rightwards.
unsigned char* add_bit(unsigned char* a,int shift_num,int len){
    for(int i = 0; i < len-1;i++){
        a[i] = a[i]|(a[i+1]<<(8-shift_num));
        a[i+1] = a[i+1]>> shift_num;
    }


    return a;



}
//this will give the few bits you want and shift to right to fill the position.
int read_bit(unsigned char* a,int len,int shift){
    int x = fetchbit(shift,a[0]);


    a[0] = a[0]>>shift;

    a = add_bit(a,shift,len);

    return x;

    
}

// test if the file is valid and return error if not detected file 
int test_file_exist(char* filename){
    FILE* ft;
    ft = fopen(filename,"r");
    if(ft==NULL){
        return 1;
    }else{
        return 0;
    }
}


//rendering the codes.
int render_program_code(struct cpu* vm,unsigned char* a,int len)
{
int total_bit = len*8;

    while(1){
        

        int operations_num = read_bit(a,len,5); total_bit-=5;





        
        int operator_num;

        for(int i = 0;i < operations_num;i++){
            operator_num = read_bit(a,len,3);total_bit-=3;
            
            if(vm->GE_R[7]<0){
                printf("too many operations, can't store\n");
                return 1;
            }
            switch(operator_num){
                case 0:{
                   

                    //MOV

                    int command = MOV;

                    int type_code1;

                    int address1;

                    int type_code2;

                    int address2;
                    
                
                    int type1 = read_bit(a,len,2);total_bit-=2;

                    
                    

                    if (type1 == 1){
                       
                        type_code1 = REG;
                        
                        address1 = read_bit(a,len,3);total_bit-=3;
 
                
                    }
                    else if (type1 == 2){

                        type_code1 = STK;
                        

                        address1 = read_bit(a,len,5);total_bit-=5;

               

                
                    }else if(type1 == 0){
                        return 1;// syntax error, MOV VAL is wrong.
                    }
                    else if(type1 ==3){
                        type_code1 = PTR;

                        address1 = read_bit(a,len,5);total_bit-=5;
                    }

                    int type2 = read_bit(a,len,2);total_bit-=2;
    

                    if(type2==0){
                     

                        type_code2 = VAL;

                        int value = read_bit(a,len,8);total_bit-=8;

                        address2 = value;

                        

              


                    }
                    else if(type2 == 1){
                   
                        type_code2 = REG;
                        
                        int address = read_bit(a,len,3);total_bit-=3;

                        address2 = address;
 
                        


                    }
                    else if(type2 == 2){
            

                        type_code2= STK;

                        
                        int address = read_bit(a,len,5);total_bit-=5;

                        address2 = address;

                      
                    }
                    else if(type2 == 3){
                        type_code2 = PTR;
                        
                        int address = read_bit(a,len,5);total_bit-=5;

                        address2 = address;
                        
                    }






                    vm->pro_mem[vm->GE_R[7]][0] = command;
                    vm->pro_mem[vm->GE_R[7]][1] = type_code1;
                    vm->pro_mem[vm->GE_R[7]][2] = address1;
                    vm->pro_mem[vm->GE_R[7]][3] = type_code2;
                    vm->pro_mem[vm->GE_R[7]][4] = address2;
                    


                    

       
                   vm->GE_R[7]--;
                    

                   

                    continue;

                }
                    


                case 1:{
                    
                    read_bit(a,len,2);total_bit-=2;
    
                    int func_label_num = read_bit(a,len,8);total_bit-=8;

               

                    vm->pro_mem[vm->GE_R[7]][0] = CAL;

                    vm->pro_mem[vm->GE_R[7]][1] = func_label_num;

                    vm->GE_R[7]--;

                    
                    continue;




                }


                case 2:{
                   
                   
                    vm->pro_mem[vm->GE_R[7]][0] = RET;
                    vm->pro_mem[vm->GE_R[7]][1] = 0;
                    vm->pro_mem[vm->GE_R[7]][2] = 0;
                    vm->pro_mem[vm->GE_R[7]][3] = 0;
                    vm->pro_mem[vm->GE_R[7]][4] = 0;



                    vm->GE_R[7]--;
                                     
                    continue;
                }
                case 3:
                    {
                        int command = REF;


                        
                        int type = read_bit(a,len,2);total_bit-=2;
                        
                        int type_num;
                        int address1;
                   

                        if(type==1){
                            type_num = REG;
                        
                            address1 = read_bit(a,len,3);total_bit-=3;

                            

                           

                        }
                        else if (type ==2){
                            type_num = STK;
                        
                            address1 = read_bit(a,len,5);total_bit-=5;

                           


                        }
                        else if (type == 3){
                            type_num = PTR;
                        
                            address1 = read_bit(a,len,5);total_bit-=5;



                        }else if (type == 0){
                            return 1;
                        }

                    int second_type_num =read_bit(a,len,2);total_bit-=2;

                    int stack_code;

                    int stack_address;

                    if(second_type_num==2){
                        stack_code = STK;
                        stack_address = read_bit(a,len,5);total_bit-=5;
                    }else if(second_type_num==3){
                        stack_code = PTR;
                        stack_address = read_bit(a,len,5);total_bit-=5;
                    }else if(second_type_num==0){
                        stack_code = VAL;
                        stack_address = read_bit(a,len,8);total_bit-=8;
                    }

                    

                    



                        

                    

                    


                    

                    

   

                    vm->pro_mem[vm->GE_R[7]][0] = command;

                    vm->pro_mem[vm->GE_R[7]][1] = type_num;

                    vm->pro_mem[vm->GE_R[7]][2] = address1;

                    vm->pro_mem[vm->GE_R[7]][3] = stack_code;

                    vm->pro_mem[vm->GE_R[7]][4] = stack_address;

                    vm->GE_R[7]--;
                    

                    

                    continue;

                    }
                case 4:{
                  
          
                    

                    
                  
                    int r1 = read_bit(a,len,2);total_bit-=2;
                    if(r1!=1){
                        return 1;
                    }
                    r1 = read_bit(a,len,3);total_bit-=3;
                                   

                    int r2 = read_bit(a,len,2);total_bit-=2;
                    if(r2!=1){
                        return 1;
                    }
                    r2 = read_bit(a,len,3);total_bit-=3;

                    
                    
                    vm->pro_mem[vm->GE_R[7]][0] = ADD;
                    vm->pro_mem[vm->GE_R[7]][1] = r1;
                    vm->pro_mem[vm->GE_R[7]][2] = r2;
                    vm->pro_mem[vm->GE_R[7]][3] = 0;
                    vm->pro_mem[vm->GE_R[7]][4] = 0;
                    vm->GE_R[7]--;

                  

       

                   


              
                    continue;
                    
                }

                case 5:
                
                    {
                         
            
                       

                        int command = PRINT;

                       


                        int type = read_bit(a,len,2);total_bit-=2;

                        int address;

                        int type_name;


                        if(type == 0){
                            type_name = VAL;
                        
                            address = read_bit(a,len,8);total_bit-=8;

                            

                         
                            

                        }
                        else if(type == 1){
                            
                            type_name = REG;
                        
                            address = read_bit(a,len,3);total_bit-=3;

                         

                            

                        }
                        else if(type==2){
                            type_name = STK;
                        
                            address = read_bit(a,len,5);total_bit-=5;

                            
                            
                           
                            

                       

                        }
                        else if(type==3){
                            type_name = PTR;
                        
                            address = read_bit(a,len,5);total_bit-=5;

                            

                    

                        }

                        
                        
                        vm->pro_mem[vm->GE_R[7]][0] = command;
                        vm->pro_mem[vm->GE_R[7]][1] = type_name;
                        vm->pro_mem[vm->GE_R[7]][2] = address;
                        vm->pro_mem[vm->GE_R[7]][3] = 0;
                        vm->pro_mem[vm->GE_R[7]][4] = 0;

                        vm->GE_R[7]--;


                    continue;




                        
                    

                    }
                case 6:
                    {
           
                        
                        int test = read_bit(a,len,2);total_bit-=2;
                        if(test!=1){
                            return 1;
                        }
                       
                        
                        int register_address = read_bit(a,len,3);total_bit-=3;
                        
                        
                        vm->pro_mem[vm->GE_R[7]][0] = NOT;
                        vm->pro_mem[vm->GE_R[7]][1] = REG;
                        vm->pro_mem[vm->GE_R[7]][2] = register_address;        
                        vm->pro_mem[vm->GE_R[7]][3] = 0;
                        vm->pro_mem[vm->GE_R[7]][4] = 0;


                        vm->GE_R[7]--;

                       
                        continue;
                    }
                    
                case 7:
                    {
                        
                        int test = read_bit(a,len,2);total_bit-=2;
                        if(test!=1){
                           
                            return 1;
                        }
                        
                    
                        int register_address = read_bit(a,len,3);total_bit-=3;
                        vm->pro_mem[vm->GE_R[7]][0] = EQU;
                        vm->pro_mem[vm->GE_R[7]][1] = REG;
                        vm->pro_mem[vm->GE_R[7]][2] = register_address;        
                        vm->pro_mem[vm->GE_R[7]][3] = 0;
                        vm->pro_mem[vm->GE_R[7]][4] = 0;


                        vm->GE_R[7]--;

                        continue;
                        

                    }
                
                


            }

            



        }

  
        int label_num = read_bit(a,len,3);total_bit-=3;

        vm->pro_mem[vm->GE_R[7]][0] = FUNC;

        vm->pro_mem[vm->GE_R[7]][1] = label_num;

        vm->pro_mem[vm->GE_R[7]][2] = 0;

        vm->pro_mem[vm->GE_R[7]][3] = 0;

        vm->pro_mem[vm->GE_R[7]][4] = 0;

        vm->ram[vm->GE_R[4]+label_num] = vm->GE_R[7];

        vm->GE_R[7]--;
        
        



    

        if(total_bit<=8){
            
            return 0;
        }






     }

     vm->GE_R[7]+=1;

   
};


//the struct to store len and data.



void initialize(struct cpu* vm){
    vm->GE_R[7]=0xFF;
    vm->GE_R[6]=0x00;  
    vm->GE_R[4] = 0xF8;
    vm->GE_R[5]=0x00+33;

    for(int k = 0; k < 4;k++){
        vm->GE_R[k] = 0;
    }
    

    for(int i= 0; i<255;i++){
        vm->ram[i]=0;
    }

}


/*
MOV 0
CAL 1
RET 2
REF 3
ADD 4
PRINT 5
NOT 6
EQU 7
VAL 8
REG 9
STK 10
PTR 11

*/


//a function to guide the oc to the function 0 while execution starts.
void guide_me_to_entry(struct cpu* vm){
    for(int i = vm->GE_R[7];i<=0xFF;i++){
        if(vm->pro_mem[i][0]==FUNC && vm->pro_mem[i][1]==0){
            vm->GE_R[7]=i;
            break;
        }
    }
}


//main function for execute the program
int execute_cpu(struct cpu* vm){
    Byte end = 0xFF;

    while(vm->GE_R[7]<=end){
        Byte opcode = vm->pro_mem[vm->GE_R[7]][0];
       
        switch(opcode){
            case MOV:{
                //execute MOV operation

                int first_type = vm->pro_mem[vm->GE_R[7]][1];
                int first_num = vm->pro_mem[vm->GE_R[7]][2];
                int second_type = vm->pro_mem[vm->GE_R[7]][3];
                int second_num = vm->pro_mem[vm->GE_R[7]][4];


                if(first_type==REG){
                    if(second_type==REG){
                        vm->GE_R[first_num] = vm->GE_R[second_num]; 

                    }else if(second_type==STK){

                        vm->GE_R[first_num] = vm->ram[vm->GE_R[6]+1+second_num];
                    }else if(second_type==PTR){

                        vm->GE_R[first_num] = vm->ram[vm->ram[vm->GE_R[6]+1+second_num]];
    

                    }else if (second_type==VAL){

                        vm->GE_R[first_num] = second_num; 
                    }

                }else if(first_type==STK){
                    if(second_type==REG){
                        vm->ram[vm->GE_R[6]+1+first_num] = vm->GE_R[second_num];


                    }else if(second_type==STK){
                        vm->ram[vm->GE_R[6]+1+first_num] = vm->ram[vm->GE_R[6]+1+second_num];


                    }else if(second_type==PTR){
                        vm->ram[vm->GE_R[6]+1+first_num] = vm->ram[vm->ram[vm->GE_R[6]+1+second_num]];

                    }else if (second_type==VAL){
                        vm->ram[vm->GE_R[6]+1+first_num] = second_num;
                        
                    }

                }else if(first_type==PTR){
                    if(second_type==REG){
                        vm->ram[vm->ram[vm->GE_R[6]+1+first_num]]= vm->GE_R[second_num];

                    }else if(second_type==STK){
                        vm->ram[vm->ram[vm->GE_R[6]+1+first_num]]= vm->ram[vm->GE_R[6]+1+second_num];


                    }else if(second_type==PTR){
                        vm->ram[vm->ram[vm->GE_R[6]+1+first_num]]= vm->ram[vm->ram[vm->GE_R[6]+1+second_num]];

                    }else if (second_type==VAL){
                        vm->ram[vm->ram[vm->GE_R[6]+1+first_num]]= second_num;
                        
                    }

                }


                vm->GE_R[7]++;
                
                

                continue;


            }
            case CAL:{                
                
                //execute CAL operation
               
                vm->GE_R[6] = vm->GE_R[5];
                //allocate frame for the next function

                int compare = vm->GE_R[5];


                // if reach the maximum of the stack, raise overflow error.
                if(compare == 247){
                    printf("stack overflow!\n");
                    return 1;
                }

                vm->GE_R[5]+=33;
                if(vm->GE_R[5]<compare){
                    vm->GE_R[5] = 247;
                }
                

                

                


                vm->ram[vm->GE_R[6]] = vm->GE_R[7]+1;

                int funcname = vm->pro_mem[vm->GE_R[7]][1];

                

                vm->GE_R[7] = vm->ram[vm->GE_R[4]+funcname];


                
                continue;



            }
            case RET:{
                 

                //execute RET operation
   
                if(vm->GE_R[6]==0x00){
                    return 0;
                }
                int return_address = vm->ram[vm->GE_R[6]];

                if(vm->GE_R[6]==231){
                    vm->GE_R[6]-=33;
                    vm->GE_R[7] = return_address;
                    continue;
                    
                }
             
                //Clear stack
                for(int i=0;i<=32;i++){
                    vm->ram[vm->GE_R[6]+i] = 0;

                }
                vm->GE_R[6]-=33;
                
                vm->GE_R[5]-=33;
                




                vm->GE_R[7] = return_address;
                
                
                continue;

            }
            case REF:{

                //execute REF operation

                int get_first_type = vm->pro_mem[vm->GE_R[7]][1];
                int get_first_num = vm->pro_mem[vm->GE_R[7]][2];
                int get_stack_type = vm->pro_mem[vm->GE_R[7]][3];
                int get_stack_num = vm->pro_mem[vm->GE_R[7]][4];

                int the_corresponding_address;
                if(get_stack_type==STK){
                    the_corresponding_address = get_stack_num+1+vm->GE_R[6];
                }else if(get_stack_type==PTR){
                    the_corresponding_address = vm->ram[get_stack_num+1+vm->GE_R[6]];
    
                }else if(get_stack_type == VAL){

                    the_corresponding_address = get_stack_num;

                }
               
                if(get_first_type==STK){
                    vm->ram[get_first_num+1+vm->GE_R[6]] = the_corresponding_address;


                }else if(get_first_type==REG){
                    vm->GE_R[get_first_num] = the_corresponding_address;

                }else if(get_first_type==PTR){
                    //the value in A is a adrress of the position
                    vm->ram[vm->ram[get_first_num+1+vm->GE_R[6]]] = the_corresponding_address;


                }
                vm->GE_R[7]++;

                continue;





            }
            case ADD:{

                //execute ADD operation

                int reg_des_address= vm->pro_mem[vm->GE_R[7]][1];
                int reg_add_num_address = vm->pro_mem[vm->GE_R[7]][2];
                int the_des_num = vm->GE_R[reg_des_address];
                int the_add_num = vm->GE_R[reg_add_num_address];
                int the_result = the_add_num+the_des_num;
                if(the_result>255){
                    the_result-=256;
                }
                vm->GE_R[reg_des_address] = the_result;

                

                
                vm->GE_R[7]++;

                continue;

            }
            case PRINT:{

                //execute PRINT operation

                int next_type = vm->pro_mem[vm->GE_R[7]][1];
                int value = vm->pro_mem[vm->GE_R[7]][2];
                if(next_type==VAL){
                    printf("%d\n",value);
                }else if(next_type==REG){
                    printf("%d\n",vm->GE_R[value]);

                }else if(next_type==PTR){
                    printf("%d\n",vm->ram[vm->ram[value+1+vm->GE_R[6]]]);

                }else if(next_type==STK){
                    printf("%d\n",vm->ram[value+1+vm->GE_R[6]]);
                }
                vm->GE_R[7]++;

                continue;



            }
            case NOT:{

                //execute NOT operation
                int reg_name = vm->pro_mem[vm->GE_R[7]][2];
                
                int old_value = vm->GE_R[reg_name];

                int new_value = ~old_value;

                vm->GE_R[reg_name] = new_value;

                vm->GE_R[7]++;


                continue;

                
            }
            case EQU:{

                //execute EQU operation
                int reg_name = vm->pro_mem[vm->GE_R[7]][2];
                int old_value = vm->GE_R[reg_name];

                int new_value;

                if(old_value==0){
                    new_value=1;

                }else{
                    new_value=0;
                }

                vm->GE_R[reg_name] = new_value;

                


            }

            case FUNC:{
                //what to do when read func label.
                int label_num = vm->pro_mem[vm->GE_R[7]][1];

                if(label_num==0){
                    vm->ram[vm->GE_R[6]] = vm->GE_R[7];
                }

                vm->GE_R[7]++;

                
                
                continue;

            }
            default:{
                continue;
            }
        }

    }

}





//tanslator for objdump

void translator(struct cpu* vm){
    int stk_search[32] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};// this is for counting apperance of each stack symbol.
    int stk_count = 0;
    while(vm->GE_R[7] <= 0xff){
 

        
        Byte opcode = vm->pro_mem[vm->GE_R[7]][0];
        switch(opcode){
            case MOV:{
                printf("    MOV ");
                if(vm->pro_mem[vm->GE_R[7]][1]==STK){
                    printf("STK ");
                    int stk_index = -1;
                    for(int i = 0;i<32;i++){
                        if(stk_search[i]==vm->pro_mem[vm->GE_R[7]][2]){
                            stk_index=i;
                        }
                    }
                    if(stk_index==-1){
                        stk_index=stk_count;
                        stk_search[stk_count]=vm->pro_mem[vm->GE_R[7]][2];
                        stk_count++;
                    }
                    printf("%s ",stack_name[stk_index]);

                } 
                if(vm->pro_mem[vm->GE_R[7]][1]==REG){
                    printf("REG ");
                    printf("%d ",vm->pro_mem[vm->GE_R[7]][2]);

                }
                if(vm->pro_mem[vm->GE_R[7]][1]==PTR){
                    printf("PTR ");
                    int stk_index = -1;
                    for(int i = 0;i<32;i++){
                        if(stk_search[i]==vm->pro_mem[vm->GE_R[7]][2]){
                            stk_index=i;
                        }
                    }
                    if(stk_index==-1){
                        stk_index=stk_count;
                        stk_search[stk_count]=vm->pro_mem[vm->GE_R[7]][2];
                        stk_count++;
                    }
                    printf("%s ",stack_name[stk_index]);

                }

             if(vm->pro_mem[vm->GE_R[7]][3]==STK){
                    printf("STK ");
                    int stk_index = -1;
                    for(int i = 0;i<32;i++){
                        if(stk_search[i]==vm->pro_mem[vm->GE_R[7]][4]){
                            stk_index=i;
                        }
                    }
                    if(stk_index==-1){
                        stk_index=stk_count;
                        stk_search[stk_count]=vm->pro_mem[vm->GE_R[7]][4];
                        stk_count++;
                    }
                    printf("%s\n",stack_name[stk_index]);
                }
                
                 if(vm->pro_mem[vm->GE_R[7]][3]==VAL){
                    printf("VAL ");
                    printf("%d\n",vm->pro_mem[vm->GE_R[7]][4]);

                }
             if(vm->pro_mem[vm->GE_R[7]][3]==REG){
                    printf("REG ");
                    printf("%d\n",vm->pro_mem[vm->GE_R[7]][4]);


                }
                if(vm->pro_mem[vm->GE_R[7]][3]==PTR){  
                    printf("PTR ");
                    int stk_index = -1;
                    for(int i = 0;i<32;i++){
                        if(stk_search[i]==vm->pro_mem[vm->GE_R[7]][4]){
                            stk_index=i;
                        }
                    }
                    if(stk_index==-1){
                        stk_index=stk_count;
                        stk_search[stk_count]=vm->pro_mem[vm->GE_R[7]][4];
                        stk_count++;
                    }
                    printf("%s\n",stack_name[stk_index]);

                }
                vm->GE_R[7]+=1;
                break;
            }

            case CAL:{
                printf("    CAL ");
                printf("VAL ");
                printf("%d\n",vm->pro_mem[vm->GE_R[7]][1]);
                vm->GE_R[7]+=1;
                break; 

                }
            case RET:{
                printf("    RET\n");
                if(vm->GE_R[7]==255){
                    return;
                }
                vm->GE_R[7]+=1;
                for(int i = 0; i < 32;i++){
                    stk_search[i] = -1;
                }
                stk_count=0;
             
                break;

                }
            case REF:{
                printf("    REF ");
                if(vm->pro_mem[vm->GE_R[7]][1]==STK){
                    printf("STK ");
                   int stk_index = -1;
                    for(int i = 0;i<32;i++){
                        if(stk_search[i]==vm->pro_mem[vm->GE_R[7]][2]){
                            stk_index=i;
                        }
                    }
                    if(stk_index==-1){
                        stk_index=stk_count;
                        stk_search[stk_count]=vm->pro_mem[vm->GE_R[7]][2];
                        stk_count++;
                    }
                    printf("%s ",stack_name[stk_index]);

                }else if(vm->pro_mem[vm->GE_R[7]][1]==PTR){
                    printf("PTR ");
                    int stk_index = -1;
                    for(int i = 0;i<32;i++){
                        if(stk_search[i]==vm->pro_mem[vm->GE_R[7]][2]){
                            stk_index=i;
                        }
                    }
                    if(stk_index==-1){
                        stk_index=stk_count;
                        stk_search[stk_count]=vm->pro_mem[vm->GE_R[7]][2];
                        stk_count++;
                    }
                    printf("%s ",stack_name[stk_index]);

                }else if(vm->pro_mem[vm->GE_R[7]][1]==REG){
                    printf("REG ");
                    printf("%d ",vm->pro_mem[vm->GE_R[7]][2]);

                   
                    
                }

                if(vm->pro_mem[vm->GE_R[7]][3]==STK){
                    printf("STK ");

                }else if(vm->pro_mem[vm->GE_R[7]][3]==PTR){
                    printf("PTR ");
                }else if(vm->pro_mem[vm->GE_R[7]][3]==VAL){
                    printf("VAL ");
                }

                
                int stk_index = -1;
                    for(int i = 0;i<32;i++){
                        if(stk_search[i]==vm->pro_mem[vm->GE_R[7]][4]){
                            stk_index=i;
                        }
                    }
                    if(stk_index==-1){
                        stk_index=stk_count;
                        stk_search[stk_count]=vm->pro_mem[vm->GE_R[7]][4];
                        stk_count++;
                    }
                    printf("%s\n",stack_name[stk_index]);
                vm->GE_R[7]+=1;
                break;

            }
            case ADD:{
                printf("    ADD ");
                printf("REG ");
                printf("%d ",vm->pro_mem[vm->GE_R[7]][1]);
                printf("REG ");
                printf("%d\n",vm->pro_mem[vm->GE_R[7]][2]);
                vm->GE_R[7]+=1;
                break;

            }
            case PRINT:{
                printf("    PRINT ");
                if(vm->pro_mem[vm->GE_R[7]][1]==PTR){
                    printf("PTR ");
                    int stk_index = -1;
                    for(int i = 0;i<32;i++){
                        if(stk_search[i]==vm->pro_mem[vm->GE_R[7]][2]){
                            stk_index=i;
                        }
                    }
                    if(stk_index==-1){
                        stk_index=stk_count;
                        stk_search[stk_count]=vm->pro_mem[vm->GE_R[7]][2];
                        stk_count++;
                    }
                    printf("%s\n",stack_name[stk_index]);

                }else if(vm->pro_mem[vm->GE_R[7]][1]==STK){
                    printf("STK ");
                    int stk_index = -1;
                    for(int i = 0;i<32;i++){
                        if(stk_search[i]==vm->pro_mem[vm->GE_R[7]][2]){
                            stk_index=i;
                        }
                    }
                    if(stk_index==-1){
                        stk_index=stk_count;
                        stk_search[stk_count]=vm->pro_mem[vm->GE_R[7]][2];
                        stk_count++;
                    }
                    printf("%s\n",stack_name[stk_index]);
                }else if(vm->pro_mem[vm->GE_R[7]][1]==VAL){
                    printf("VAL ");
                    printf("%d\n",vm->pro_mem[vm->GE_R[7]][2]);
                }else if(vm->pro_mem[vm->GE_R[7]][1]==REG){
                    printf("REG ");
                    printf("%d\n",vm->pro_mem[vm->GE_R[7]][2]);
                }
                vm->GE_R[7]+=1;

                break;

            }
            case NOT:{
                printf("    NOT ");
                printf("REG ");
                printf("%d\n",vm->pro_mem[vm->GE_R[7]][2]);
                vm->GE_R[7]+=1;
                break;

            }
            case EQU:{

                printf("    EQU ");
                printf("REG ");
                printf("%d\n",vm->pro_mem[vm->GE_R[7]][2]);
                vm->GE_R[7]+=1;
                break;

            }
            case FUNC:{
                printf("FUNC LABEL ");
                printf("%d\n",vm->pro_mem[vm->GE_R[7]][1]);

                vm->GE_R[7]+=1;
                break;
            }
        }


        

 

        

    }
}














