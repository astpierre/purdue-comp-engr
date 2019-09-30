# Makefile
TARGET = hw19
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS = -DTEST_MAIN -DTEST_FUSE -DTEST_CLUSTER -DTEST_CENT -DTEST_DIST -DTEST_LINKEDLISTCREATE -DTEST_CREATENODE -DTEST_MIN

SRCS = main.c hw19.c
OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose --log-file=memcheck.txt --leak-check=full

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testall: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 testmem

testadd: $(TARGET)
	test1
	test2
	test3
	test4
	test5
	test6
	test7
	test8
	test9
	test10
	testmem

testmem:	$(TARGET)
	$(VALGRIND) ./hw19 inputs/test1.txt > outputs/output1.txt
test1: $(TARGET)
	./hw19 inputs/test1.txt > outputs/output1.txt
	diff -i -w expected/expected1.txt outputs/output1.txt
test2: $(TARGET)
	./hw19 inputs/test2.txt > outputs/output2.txt
	diff -i -w expected/expected2.txt outputs/output2.txt
test3: $(TARGET)
	./hw19 inputs/test3.txt > outputs/output3.txt
	diff -i -w expected/expected3.txt outputs/output3.txt
test4: $(TARGET)
	./hw19 inputs/test4.txt > outputs/output4.txt
	diff -i -w expected/expected4.txt outputs/output4.txt
test5: $(TARGET)
	./hw19 inputs/test5.txt > outputs/output5.txt
	diff -i -w expected/expected5.txt outputs/output5.txt
test6: $(TARGET)
	./hw19 inputs/test6.txt > outputs/output6.txt
	diff -i -w expected/expected6.txt outputs/output6.txt
test7: $(TARGET)
	./hw19 inputs/test7.txt > outputs/output7.txt
	diff -i -w expected/expected7.txt outputs/output7.txt
test8: $(TARGET)
	./hw19 inputs/test8.txt > outputs/output8.txt
	diff -i -w expected/expected8.txt outputs/output8.txt
test9: $(TARGET)
	./hw19 inputs/test9.txt > outputs/output9.txt
	diff -i -w expected/expected9.txt outputs/output9.txt
test10: $(TARGET)
	./hw19 inputs/test10.txt > outputs/output10.txt
	diff -i -w expected/expected10.txt outputs/output10.txt

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt
