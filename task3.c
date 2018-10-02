#include <stdio.h>
#include <stdlib.h>
#include "str_list.h"
#include "buffer.h"

void input()
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
        //            add(&a, str);
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
    string_list lst = (char**)malloc(10 * sizeof(char*));
    add_string_list(lst, "aaaa");
    add_string_list(lst, "bbbb");
    add_string_list(lst, "cccc");
    add_string_list(lst, "dddd");
    // print_string_list(lst);
    for(int i = 0;i < 2;i++)
        printf("%s\n", lst[3]);

    // free(lst[0]);
    // free(lst[1]);
    // free(lst[2]);
    // free(lst[3]);
    // free(lst);
    //input();
    return 0;
}