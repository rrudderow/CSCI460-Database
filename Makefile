EXE=MNist2PSQL
${EXE}.exe : ${EXE}.cpp
	g++ $< -o $@

run: ${EXE}.exe
	./${EXE}.exe t10k > trainData.sql 
#use > trainData.sql to redirect couts to trainData.sql instead
