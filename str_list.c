#include <stdio.h>
#include <stdlib.h>

typedef char **string_list;
int string_list_size = 10;
int string_list_size_current = 0;

void add_string_list(string_list str, char *elem)
{
    str[string_list_size_current++] = elem;
}
void clean_string_list(string_list str)
{
    int i = 0;
    for(;i < string_list_size_current;i++)
        free(str[i]);
    free(str);
}
void print_string_list(string_list str)
{
    int i = 0;
    for(;i < string_list_size_current;i++)
        printf("%s\n", str[i]);
}
string_list init_string_list()
{
    string_list str_list = (char**)malloc(string_list_size * sizeof(char));
    return str_list;
}