# Makefile

TARGET = shuf
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS = -DTEST_MAIN -DTEST_SHUF -DTEST_INTER -DTEST_DIV

SRCS =  main.c utility.c shuffle.c
OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose --log-file=memcheck.txt --leak-check=full

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testall: test1 test2 test3

testadd: $(TARGET)
	test1
	test2
	test3

testmemory:	$(TARGET)
	$(VALGRIND) ./shuf 4 | sort > output1.txt
	$(VALGRIND) ./shuf 8 | sort > output2.txt
	$(VALGRIND) ./shuf 11 | sort > output3.txt


test1: $(TARGET)
	./shuf 4 | sort > output1.txt
	diff -i -w output1.txt expected/expected1.txt
	
test2: $(TARGET)
	./shuf 8 | sort > output2.txt
	diff -i -w output2.txt expected/expected2.txt

test3: $(TARGET)
	./shuf 11 | sort > output3.txt
	diff -i -w output3.txt expected/expected3.txt

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt
