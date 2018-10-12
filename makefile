main: buffer.o task3.o str_list.o
	gcc -o main buffer.o str_list.o task3.o
task3.o: task3.c
	gcc -c -o task3.o task3.c
buffer.o: buffer.c buffer.h
	gcc -c -o buffer.o buffer.c
str_list.o: str_list.c str_list.h
	gcc -c -o str_list.o str_list.c
clean:
	rm main task3.o buffer.o str_list.o