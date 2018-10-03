#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Types
typedef char **string_list;
//Variables
int string_list_size = 10;
int string_list_size_current = 0;
//Functions
void copy_str(char*, char*);
string_list add_string_list(string_list, char*, int);
void clean_string_list(string_list);
void print_string_list(string_list);
void sort_string_list(string_list);
string_list init_string_list();

void copy_str(char *a, char *b)
{
    for(;*b != '\0';a++, b++)
        *a = *b;
    *a = '\0';
}

string_list add_string_list(string_list str, char *elem, int elem_size)
{
    if(string_list_size_current == string_list_size)
    {
        string_list_size*=2;
        str = realloc(str, sizeof(char*) * string_list_size);
    }
    str[string_list_size_current] = (char*)malloc(sizeof(char) * elem_size);//ERROR
    copy_str(str[string_list_size_current], elem);
    string_list_size_current++;
    return str;
}
void clean_string_list(string_list str)
{
    // printf("POINT CUR = %d, MAX = %d\n", string_list_size_current, string_list_size);
    // printf("str = %s\n", str[0]); 
    // for(int i = 0;i < string_list_size_current;i++)// WHY ERROR IF UNCOMMENTED?
    //     free(str[i]);// Тут утечка памяти, но я пока не знаю почему, похоже на ошибку подобную такой в таске 2.5
    free(str);
}
void print_string_list(string_list str)
{
    for(int i = 0;i < string_list_size_current;i++)
    {
        int size_of_str = strlen(str[i])+1;
        char out_buff[size_of_str];
        copy_str(out_buff, str[i]);
        // out_buff[size_of_str-1] = '\n';
        out_buff[size_of_str-1] = (i == string_list_size_current-1) ? '\n' : ' ';
        fwrite(out_buff, sizeof(char), size_of_str, stdout);
    }        
}
void sort_string_list(string_list str)
{
    char *buff = NULL;
    int max = 0;

    for(int i = 0;i < string_list_size_current;i++)
    {
        max = i;
        for(int j = i+1;j < string_list_size_current;j++)
        {
            if(strcmp(str[max], str[j]) > 0)
                max = j;
        }
        if(max != i)
        {
            buff = str[max];
            str[max] = str[i];
            str[i] = buff;
        }
    }
}
string_list init_string_list()
{
    string_list str_list = (char**)malloc(string_list_size * sizeof(char*));
    str_list[0] = NULL;
    return str_list;
}
