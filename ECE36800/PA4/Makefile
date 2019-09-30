# Makefile
# -fsanitize=leak -fsanitize=address
TARGET = pa4
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla #-fsanitize=address -fsanitize=leak
GCC = gcc -std=c99 -O3 $(WARNING) $(ERROR) -lm

SRCS = pa4.c avl_tree.c
OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose --log-file=memcheck.txt --leak-check=full

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) -c $*.c

run: $(TARGET)
	./pa4 -b examples/ops2.b output/tree2.txt

test0: $(TARGET)
	$(VALGRIND) ./pa4 -b examples/ops0.b output/tree0.b
	diff examples/tree0.b output/tree0.b

test1: $(TARGET)
	$(VALGRIND) ./pa4 -b examples/ops1.b output/tree1.b
	diff examples/tree1.b output/tree1.b

test2: $(TARGET)
	$(VALGRIND) ./pa4 -b examples/ops2.b output/tree2.b
	diff examples/tree2.b output/tree2.b

test3: $(TARGET)
	$(VALGRIND) ./pa4 -b examples/ops3.b output/tree3.b
	diff examples/tree3.b output/tree3.b

teste0: $(TARGET)
	./pa4 -e examples/tree0.b

teste1: $(TARGET)
	$(VALGRIND) ./pa4 -e examples/invalidtree1.b

teste2: $(TARGET)
	$(VALGRIND) ./pa4 -e examples/invalidtree2.b

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt
	rm -f *out
	rm -f output/*.b
	rm -f output/*.txt
