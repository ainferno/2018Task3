#include "sh.h" 
// #include "buffer.h"

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
