#include <stdio.h>
#include <stdlib.h>
#include "str_list.h"
#include "buffer.h"

void input(string_list lst)
{
    char *str = NULL;
    char c;
    int N = 10, i = 0;
    str = (char*)malloc(N*sizeof(char));

    for(;(c = get_char()) != '\0';i++)
    {
        if(i == N)
        {
            N*=2;
            str = (char*)realloc(str, N*sizeof(char));
        }
        if( i > 0)
        {
            switch(c)
            {
                case ' ': case '\n': case '\t':
                    N = 10;
                    str[i] = '\0';
                    add_string_list(lst, str);
                    str = (char*)malloc(N*sizeof(char));
                    i = -1;
            }
        }
        if(c != ' ' && c != '\n' && c != '\t')
        {
            str[i] = c;
        }
        else
            i--;
    }
}

int main()
{
    string_list lst = init_string_list();
    input(lst);
    print_string_list(lst);
    return 0;
}
