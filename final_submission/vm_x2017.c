#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "synthesized_cpu.h"






int main(int argc,char** argv){
    struct bin_data a;

    unsigned char* the_bicodes;

    int size;

    //deal not enough arguments
    if(argc!=2){
        printf("not enough arguments!\n");
        return 1;
    }
    //deal file not exist

    if(test_file_exist(argv[1])==1){
        printf("file not exist!\n");
        return 1;
    }
    






    a = get_bin_data(argv[1]);

    the_bicodes=a.data;size = a.len;


    

    if(size>256){
      
        return 1;
    }

    struct cpu vm;
    //set pc tp start
    initialize(&vm);


    int render_result = render_program_code(&vm,the_bicodes,size);
    //deal render syntax error.
    if(render_result==1){
        printf("Syntax error\n");
        return 1;
    }



    


    vm.GE_R[7]+=1;

    //execute from func 0
    guide_me_to_entry(&vm);


    int t = execute_cpu(&vm);
    //deal execute error.
    if (t == 1){
        return 1;
    }


    return 0;

    

    

}



