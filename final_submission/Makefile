CC=gcc
CFLAGS += -ffunction-sections -fdata-sections -Os -s 
LDFLAGS += -Wl,-Map=object.map,--cref,--gc-section

# fill in all your make rules

vm_x2017: 
	$(CC) $(CFLAGS) $(LDFLAGS) vm_x2017.c -o  vm_x2017 synthesized_cpu.h synthesized_cpu.c 

objdump_x2017: 
	$(CC) objdump_x2017.c -o  objdump_x2017 synthesized_cpu.h synthesized_cpu.c 

tests:
	$(CC) $(CFLAGS) vm_x2017.c -o  vm_x2017 synthesized_cpu.h synthesized_cpu.c 
	$(CC) objdump_x2017.c -o  objdump_x2017 synthesized_cpu.h synthesized_cpu.c 

run_tests:
	./test.sh

clean:
	rm vm_x2017 objdump_x2017

