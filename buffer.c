#include "buf.h"
// #include "buffer.h"

int fill_buf(char *buf)
{
    return read(0,buf,buf_size);
    // return fread(buf, sizeof(char), buf_size, stdin);//Берем символы из ввода
}
void clean_input()
{
    char c;
    while((c = getchar()) != '\n' && c != EOF);//Пока входной поток не пуст отчищаем его
}
int clean_buf(char *buf)
{
    int i = 0;
    for(;(i < buf_size) && (buf[i] != '\n');i++, buf[i] = '\0');//Отчищаем буффер
    return i;
}
int get_char(char *buf, int *i)
{
    int n = 0;
    if(*i == buf_size)
    {
        clean_buf(buf);//В данном случае отчистка буфера не имеет особого смысла
        n = fill_buf(buf);
        // printf("POINT N = %d\n", n);
        if(n == 0)
            return END_OF_INP;
        if(n < buf_size)//Если мы нажали enter/ctrl-d в конец последнего буфера попадет символ конца строки
            buf[n] = '\n';
        *i = 0;
    }
    // printf("C[%d] = %c\n", *i, buf[*i]);
    if(buf[*i] == '\n')
    {
        *i = buf_size;
        return END_OF_STR;
    }
    return (unsigned char)buf[(*i)++];//Char -> unsigned char, так как потом переводим это число в int
}