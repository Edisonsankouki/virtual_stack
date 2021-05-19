#include<stdio.h>
#include<stdlib.h>
#include "struct_bin.h"

/*functions for bite operations*/
struct bin_data get_bin_data(char* filename);
int fetchbit(int num,int in);
unsigned char* add_bit(unsigned char* a,int shift_num,int len);
int read_bit(unsigned char* a,int len,int shift);
int test_file_exist(char* filename);

/*functions for vm and objdump*/
void initialize(struct cpu* vm);
void guide_me_to_entry(struct cpu* vm);
int execute_cpu(struct cpu* vm);
void translator(struct cpu* vm);
int render_program_code(struct cpu* vm,unsigned char* a,int len);

