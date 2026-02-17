SOURCEMODULES = math_functions.c root_and_integral.c test_root_and_integral.c
OBJECTMODULES = ${SOURCEMODULES:.c=.o}

LDFLAGS = -lm

%.o: %.c %.h
	${CC} ${CFLAGS} -c $< -o $@

all: prog

prog: main.c ${OBJECTMODULES}
	${CC} ${CFLAGS} $^ -o $@ $(LDFLAGS)

ifneq (clean, ${MAKECMDGOALS})
-include deps.mk
endif

deps.mk: ${SOURCEMODULES} main.c
	${CC} -MM $^ > $@

clean:
	rm -f *.o prog

