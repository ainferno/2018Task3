all: main.out
main.out: buffer.o str_list.o task3.o
	gcc buffer.o str_list.o task3.o -o main.out
task3.o: task3.c sh.h buf.h
	gcc -c task3.c
buffer.o: buffer.c buf.h
	gcc -c buffer.c
str_list.o: str_list.c sh.h
	gcc -c str_list.c
clean:
	rm main.out task3.o buffer.o str_list.o