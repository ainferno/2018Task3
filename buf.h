#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef buf_size
#define buf_size 10u //Определяем размер буффера
#endif

//Functions buf
int fill_buf(char*);//Заполняет буфер, возвращает количество считанных символов
void clean_buf(char*);//Отчищает буфер
void clean_input();//Отчищает весь входной поток
char get_char(int);//Возвращает символ из буфера, если буфер пуст то заполняет его, если и там пусто возвращает '\0'  
//На вход принимает int, если int = 1 то отчищает буфер. 