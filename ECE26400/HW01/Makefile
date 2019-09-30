# ***
# *** Please modify this file and check what would happen
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
COVERAGE = -fprofile-arcs -ftest-coverage
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) $(COVERAGE)

TESTFALGS = -DTEST_ADD -DTEST_SUB -DTEST_MUL -DTEST_DIV -DTEST_MAIN

# list all .c files
SRCS = add.c div.c mul.c  main.c solution.c sub.c

# object files are created by converting .c to .o
OBJS = $(SRCS:%.c=%.o)

main: $(OBJS) 
	$(GCC) $(TESTFALGS) $(OBJS) -o main
	# without -c means linking to create the executable
	# the executable is after -o and is called main
	# By convention, executable in Linux has no extension
	# (no .exe)

# convert .c to .o 
.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 
	# -c means compilation only (creating object file)
	# no linking

testall: testadd testsub testmul testdiv

testadd: main
	# main here to ensure the executable is up-to-date
	./main 4 5 A > add1.out
	diff add1.out add1.correct
	./main -2 17 A > add2.out
	diff add2.out add2.correct

testsub: main
	./main 4 5 S > sub1.out
	diff sub1.out sub1.correct
	./main 7 26 S > sub2.out
	diff sub2.out sub2.correct

testmul: main
	./main 4 5 M > mul1.out
	diff mul1.out mul1.correct
	./main 7 26 M > mul2.out
	diff mul2.out mul2.correct

testdiv: main
	./main 240 5 D > div1.out
	diff div1.out div1.correct
	./main 70 26 D > div2.out
	diff div2.out div2.correct

coverage: testall
	gcov $(SRCS)

clean: # remove all machine generated files
	rm -f main *.o *.out *gcda *gcno *gcov

# DO NOT DELETE THIS LINE -- make depend depends on it.

add.o: header.h /usr/include/stdio.h /usr/include/features.h
add.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
add.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
add.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
add.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
add.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
div.o: header.h /usr/include/stdio.h /usr/include/features.h
div.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
div.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
div.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
div.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
div.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
mul.o: header.h /usr/include/stdio.h /usr/include/features.h
mul.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
mul.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
mul.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
mul.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
mul.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
main.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
main.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
main.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
main.o: /usr/include/bits/typesizes.h /usr/include/libio.h
main.o: /usr/include/_G_config.h /usr/include/wchar.h
main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
main.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
main.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
main.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
main.o: /usr/include/sys/types.h /usr/include/time.h
main.o: /usr/include/sys/select.h /usr/include/bits/select.h
main.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
main.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
main.o: /usr/include/alloca.h /usr/include/string.h /usr/include/xlocale.h
main.o: header.h
solution.o: header.h /usr/include/stdio.h /usr/include/features.h
solution.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
solution.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
solution.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
solution.o: /usr/include/libio.h /usr/include/_G_config.h
solution.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
solution.o: /usr/include/bits/sys_errlist.h
sub.o: header.h /usr/include/stdio.h /usr/include/features.h
sub.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
sub.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
sub.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
sub.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
sub.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
