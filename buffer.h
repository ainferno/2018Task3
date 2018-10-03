#include <stdio.h>
#define buf_size 10u //Определяем размер буффера
//Functions
int fill_buf(char*);//Заполняет буфер, возвращает количество считанных символов
void clean_buf(char*);//Отчищает буфер
char get_char();//Возвращает символ из буфера, если буфер пуст то заполняет его, если и там пусто возвращает '\0'

int fill_buf(char *buf)
{
    return fread(buf, sizeof(char), buf_size, stdin);//Берем символы из ввода
}
void clean_buf(char *buf)
{
    int i = 0;
    for(;i < buf_size;i++, buf[i] = '\0');
}
char get_char()
{
    static char buf[buf_size] = "\0";//Заводим буфера, так как нам нужно чтобы он был глобальным делаем его статик
    static int i = buf_size;//Не заводим его в точке вызова, так как он используется только здесь
    //printf("i = %d\n", i);
    if(i == buf_size)//Если дошли до конца буфера
    {
        clean_buf(buf);
        if(fill_buf(buf) == 0)
            return '\0';
        i = 0;
    }
    return buf[i++];
}