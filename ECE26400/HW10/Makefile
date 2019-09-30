# Makefile
TARGET = hw10
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS = -DTEST_MAINFUNC -DTEST_FUNCGIVEN -DTEST_IMGTOGRAY -DTEST_HEADERVALID -DTEST_BMPOPENFILE -DTEST_BMPWRITEFUNC -DTEST_BMPFREEFUNC

SRCS =  hw10.c bmpfunc.c bmpimage.c
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
	$(VALGRIND) ./hw10 exampleImages/RV2.bmp expectedImages/outputRV2.bmp

test1: $(TARGET)
	./hw10 exampleImages/RV.bmp expectedImages/outputRV.bmp
	xxd expectedImages/expectedRV.bmp > expectedImages/expRV.txt
	xxd expectedImages/outputRV.bmp > expectedImages/outRV.txt
	diff expectedImages/expRV.txt expectedImages/outRV.txt
	
test2: $(TARGET)
	./hw10 exampleImages/RV2.bmp expectedImages/outputRV2.bmp
	xxd expectedImages/expectedRV2.bmp > expectedImages/expRV2.txt
	xxd expectedImages/outputRV2.bmp > expectedImages/outRV2.txt
	diff expectedImages/expRV2.txt expectedImages/outRV2.txt

test3: $(TARGET)
	./hw10 exampleImages/RV2Small.bmp expectedImages/outputRV2Small.bmp
	xxd expectedImages/expectedRV2Small.bmp > expectedImages/expRV2Small.txt
	xxd expectedImages/outputRV2Small.bmp > expectedImages/outRV2Small.txt
	diff expectedImages/expRV2Small.txt expectedImages/outRV2Small.txt

test4: $(TARGET)
	./hw10 exampleImages/CondProb.bmp expectedImages/outputCondProb.bmp
	xxd expectedImages/expectedCondProb.bmp > expectedImages/expCondProb.txt
	xxd expectedImages/outputCondProb.bmp > expectedImages/outCondProb.txt
	diff expectedImages/expCondProb.txt expectedImages/outCondProb.txt

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt
