all: main.exe
main.exe: buffer.o task3.o str_list.o
	gcc buffer.o str_list.o task3.o -o main.exe
task3.o: task3.c
	gcc -c task3.c
buffer.o: buffer.c buffer.h
	gcc -c buffer.c
str_list.o: str_list.c str_list.h
	gcc -c str_list.c
clean:
	rm main.exe task3.o buffer.o str_list.o
