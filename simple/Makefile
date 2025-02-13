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
	rm *.exe

run: ${EXE}
	./${EXE}

check: ${EXE}
# check for security vulnerabilities
	cppcheck ${SRC}

lint: ${EXE}
# formating - --filter to turn things off
	cpplint --filter=-legal/copyright,-build/namespaces,-whitespace,-runtime ${SRC}

linked:
	g++ ${CFLAGS} linked.cpp -o linked.exe

link_run:
	./linked.exe
