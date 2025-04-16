EXE=MNist2PSQL
${EXE}.exe : ${EXE}.cpp
	g++ $< -o $@

run: ${EXE}.exe
	./${EXE}.exe train
