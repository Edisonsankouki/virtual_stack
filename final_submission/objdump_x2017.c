#include <stdio.h>

#include <stdlib.h>

#include "synthesized_cpu.h"









int main(int argc, char **argv){

    unsigned char* a;

    struct bin_data b;


    //get the binary data
    b = get_bin_data(argv[1]);

    a = b.data;
    int size = b.len;

    

    //construct a virtual machine struct
    struct cpu vm;

    //set all the parameters to original

    initialize(&vm);



    
    //render the program code into program memory
    int result = render_program_code(&vm,a,size);

    //check if the render is correct

    if(result==1){
        printf("Syntax error\n");
        return 1;
    }

   


    
    //set pc to start
    vm.GE_R[7]+=1;


    
    //print all the operations.
    translator(&vm);

  



    return 0;

}






