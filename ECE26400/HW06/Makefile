# ***
# *** Please modify this file as required
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS = -DTEST_MAIN -DTEST_COMP -DTEST_FILL -DTEST_WRITE -DTEST_COUNT

SRCS = main.c vector.c
OBJS = $(SRCS:%.c=%.o)

hw06: $(OBJS) 
	$(GCC) $(TESTFALGS) $(OBJS) -o hw06
	
testmemory: $(TARGET)
	$(VAL) ./hw06 inputs/test1.bin output1.bin
	$(VAL) ./hw06 inputs/test2.bin output2.bin
	$(VAL) ./hw06 inputs/test3.bin output3.bin

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

testall: test1 test2 test3

testadd: sort
	test1
	test2
	test3

test1: hw06
	./hw06 inputs/test1.bin output1.bin
	diff output1.bin expected/expected1.bin

test2: hw06
	./hw06 inputs/test2.bin output2.bin
	diff output2.bin expected/expected2.bin

test3: hw06
	./hw06 inputs/test3.bin output3.bin
	diff output3.bin expected/expected3.bin

clean: # remove all machine generated files
	rm -f hw06 *.o output?
	rm -f *.bin
