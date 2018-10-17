#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef buf_size
#define buf_size 10u //Определяем размер буффера
#endif
#ifndef END_OF_STR
#define END_OF_STR -1
#endif
#ifndef END_OF_INP
#define END_OF_INP -2
#endif

//Functions buf
int fill_buf(char*);//Заполняет буфер, возвращает количество считанных символов
int clean_buf(char*);//Отчищает буфер
void clean_input();//Отчищает весь входной поток
int get_char(char*, int*);//Возвращает символ из буфера, если буфер пуст то заполняет его, если и там пусто возвращает '\0'  
//На вход принимает int, если int = 1 то отчищает буфер. 