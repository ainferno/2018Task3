#include "buf.h" 
// #include "buffer.h"

int fill_buf(char *buf)
{
    return fread(buf, sizeof(char), buf_size, stdin);//Берем символы из ввода
}
void clean_input()
{
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}
void clean_buf(char *buf)
{
    int i = 0;
    for(;i < buf_size;i++, buf[i] = '\0');
}
char get_char(int STATE)
{
    static char buf[buf_size] = "\0";//Заводим буфера, так как нам нужно чтобы он был глобальным делаем его статик
    static int i = buf_size;//Не заводим его в точке вызова, так как он используется только здесь
    int n = 0;
    //printf("i = %d\n", i);
    if(STATE == 1)
    {
        clean_buf(buf);
        i = buf_size;
        return '\0';
    }
    if(i == buf_size)//Если дошли до конца буфера
    {
        clean_buf(buf);
        if((n = fill_buf(buf)) == 0)
            return '\0';
        if(n < buf_size)
            buf[n] = '\0';
        i = 0;
    }
    return buf[i++];//Как видим, если наш буфер не заполнен до конца, то на Nном месте будет стоять '\0'  
}//и она вернет его, а '\0' у нас считается концом ввода