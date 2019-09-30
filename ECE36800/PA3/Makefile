# Makefile
# -fsanitize=leak -fsanitize=address
TARGET = pa3
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -O3 $(WARNING) $(ERROR) -lm

SRCS = pa3.c delay.c
OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose --log-file=memcheck.txt --leak-check=full

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) -c $*.c

#testall: test3 test5 test10 test100 test1000

run: $(TARGET)
	./pa3 pa3_examples/3.txt output/3.pre output/3.delay.txt

test3: $(TARGET)
	$(VALGRIND) ./pa3 pa3_examples/3.txt output/3.pre output/3.delay
	diff pa3_examples/3.pre output/3.pre
	diff pa3_examples/3.delay output/3.delay

test5: $(TARGET)
	$(VALGRIND) ./pa3 pa3_examples/5.txt output/5.pre output/5.delay
	diff pa3_examples/5.pre output/5.pre
	diff pa3_examples/5.delay output/5.delay

test10: $(TARGET)
	$(VALGRIND) ./pa3 pa3_examples/10.txt output/10.pre output/10.delay.txt

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt
	rm -f *out
	rm -f pa3
	rm -f output/*.pre
	rm -f output/*.delay
