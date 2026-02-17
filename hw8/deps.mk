math_functions.o: math_functions.c math_functions.h
root_and_integral.o: root_and_integral.c root_and_integral.h
test_root_and_integral.o: test_root_and_integral.c root_and_integral.h \
 math_functions.h
main.o: main.c math_functions.h root_and_integral.h \
 test_root_and_integral.h
