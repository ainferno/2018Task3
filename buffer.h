#include <stdio.h>
#define buf_size 10u //Определяем размер буффера
//Functions
int fill_buf(char*);//Заполняет буфер, возвращает количество считанных символов
void clean_buf(char*);//Отчищает буфер
char get_char();//Возвращает символ из буфера, если буфер пуст то заполняет его, если и там пусто возвращает '\0'   