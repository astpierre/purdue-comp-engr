# Makefile

TARGET = shuf
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS = -DTEST_MAIN -DTEST_SHUF -DTEST_INTER -DTEST_DIV -DTEST_COMB -DTEST_RSHUF

SRCS =  main.c utility.c shuffle.c
OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose --log-file=memcheck.txt --leak-check=full

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testall: test1 test2 test3 test4 testmemory

testadd: $(TARGET)
	test1
	test2
	test3
	test4
	testmemory

testmemory:	$(TARGET)
	$(VALGRIND) ./shuf 2 2 | sort > output1.txt
	$(VALGRIND) ./shuf 4 3 | sort > output2.txt
	$(VALGRIND) ./shuf 7 2 | sort > output3.txt

test1: $(TARGET)
	./shuf 2 2 | sort > output1.txt
	diff -i -w output1.txt expected/expected1
	
test2: $(TARGET)
	./shuf 4 3 | sort > output2.txt
	diff -i -w output2.txt expected/expected2

test3: $(TARGET)
	./shuf 7 2 | sort > output3.txt
	diff -i -w output3.txt expected/expected3

test4: $(TARGET)
	./shuf 4 6 | sort > output4.txt

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt
