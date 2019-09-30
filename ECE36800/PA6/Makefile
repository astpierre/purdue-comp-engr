# Makefile
TARGET = pa6
WARNING =  -Wshadow --pedantic -Wall
ERROR = -Wvla #-fsanitize=address -fsanitize=leak
GCC = gcc -std=c99 -O3 $(WARNING) $(ERROR)

SRCS = pa6.c seqpair.c
OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose --log-file=memcheck.txt --leak-check=full

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) -c $*.c

run: $(TARGET)
	./pa6 examples/r8.sp r8_o.pck

test1: $(TARGET)
	./pa6 examples/r8.sp r8_o.pck
	diff examples/r8.pck r8_o.pck

test2: $(TARGET)
	./pa6 examples/r100.sp r100_o.pck
	diff examples/r100.pck r100_o.pck

test3: $(TARGET)
	./pa6 examples/r100h.sp r100h_o.pck
	diff examples/r100h.pck r100h_o.pck

test4: $(TARGET)
	./pa6 examples/r100v.sp r100v_o.pck
	diff examples/r100v.pck r100v_o.pck

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *o.pck
	rm -f memcheck.txt
	rm -f output/*.b
