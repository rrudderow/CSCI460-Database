PROJ=simple1
SRC=${PROJ}.cpp
EXE=${PROJ}.exe
CFLAGS=-g -pg
#-g = debugging info - see C source code when debugging
#-g for gdb
#-pg = profiler - gathers time info
CFLAG=-s
#-s = strip all info out

${EXE}: ${SRC}
	g++ ${CFLAGS} $< -o $@

clean:
	rm ${EXE}

run: ${EXE}
	./${EXE}