#include <stdio.h>
#define buff_size 10u

int fill_buff(char *buff)
{
    return fread(buff, sizeof(char), buff_size, stdin);
}
void clean_buff(char *buff)
{
    int i = 0;
    for(;i < buff_size;i++, buff[i] = '\0');
}
char get_char()
{
    static char buff[buff_size] = "\0";
    static int i = buff_size;
    //printf("i = %d\n", i);
    if(i == buff_size)
    {
        clean_buff(buff);
        if(fill_buff(buff) == 0)
            return '\0';
        i = 0;
    }
    return buff[i++];
}