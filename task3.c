#include <stdio.h>
#include <stdlib.h>
// #include "str_list.h"
// #include "buffer.h"

//str = (char*)malloc(N*sizeof(char));
//str = (char*)realloc(str, N*sizeof(char));

string_list input(string_list lst)
{
    char *str = NULL;
    char c;
    int N = 10, i = 0, pp_entered = 0;
    str = (char*)malloc(N*sizeof(char));

    while((c = get_char()) != '\0')
    {
        if(i == N)
        {
            N*=2;
            str = (char*)realloc(str, N*sizeof(char));
        }
        switch(c)
        {
            case '|': case '&': case '>':
                if(i!=0)
                {
                    str[i] = '\0';
                    lst = add_string_list(lst,str,i+1);

                    free(str);
                    N = 10, i = 0;
                    str = (char*)malloc(N*sizeof(char));
                }
                while(c == '|' || c == '&' || c == '>')
                {
                    str[i++] = c;
                    c = get_char();
                    if(c == str[i-1])
                    {
                        str[i++] = c;
                        c = get_char();
                    }
                    str[i] = '\0';
                    lst = add_string_list(lst,str,i+1);

                    free(str);
                    N = 10, i = 0;
                    str = (char*)malloc(N*sizeof(char));
                }
                break;
            case ';': case '<': case '(': case ')':
                if(i!=0)
                {
                    str[i] = '\0';
                    lst = add_string_list(lst,str,i+1);

                    free(str);
                    N = 10, i = 0;
                    str = (char*)malloc(N*sizeof(char));
                }
                str[i++] = c;
            case ' ': case '\t': case '\n':
                if(i!=0)
                {
                    str[i] = '\0';
                    lst = add_string_list(lst,str,i+1);

                    free(str);
                    N = 10, i = 0;
                    str = (char*)malloc(N*sizeof(char));
                }
        }
        if(c != ' ' && c != '\t' && c != '\n' && 
           c != ';' && c != '<'  && c != '('  && c != ')' &&
           c != '|' && c != '&'  && c != '>')
        {
            str[i++] = c;
        }
    }

    free(str);
    return lst;
}

int main()
{
    string_list lst = init_string_list();
    lst = input(lst);
    print_string_list(lst);
    sort_string_list(lst);
    print_string_list(lst);
    clean_string_list(lst);
    return 0;
}
