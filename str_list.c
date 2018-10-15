#include "sh.h"
// #include "str_list.h"

void copy_str(char *a, char *b)
{
    for(;*b != '\0';a++, b++)
        *a = *b;
    *a = '\0';
}

string_struct add_string_list(string_struct str, char *elem, int elem_size)
{
    if(str.size_current == str.size)//Если выходим за пределы массива то перевыделяем память под него
    {
        str.size*=2;
        str.array = realloc(str.array, sizeof(char*) * str.size);
    }
    str.array[str.size_current] = (char*)malloc(sizeof(char) * elem_size);
    copy_str(str.array[str.size_current], elem);//Нельзя делать простое приравнивание так как в таком случае
    str.array[++str.size_current] = NULL;//если вне функции очистить то что передали очистим, то и тут пропадет
    return str;//А мы хотим функцию которая работает корректно не зависимо от реализации программы ее вызывающей
}
string_struct clean_string_list(string_struct str)
{
    for(int i = 0;i < str.size_current;i++)
        free(str.array[i]);
    free(str.array);
    str.size = array_size, str.size_current = 0;
    return str;
}
void print_string_list(string_struct str)
{
    for(int i = 0;i < str.size_current;i++)
    {
        int size_of_str = strlen(str.array[i])+1;//Так как мы выводим в файл, то мы используем буфер чтобы
        char out_buff[size_of_str];//Добавить символы ' '/'\n' в конец
        copy_str(out_buff, str.array[i]);
        out_buff[size_of_str-1] = (i == str.size_current-1) ? '\n' : ' ';
        fwrite(out_buff, sizeof(char), size_of_str, stdout);
    }        
}
void sort_string_list(string_struct str)
{
    char *buff = NULL;
    int max = 0;

    for(int i = 0;i < str.size_current;i++)
    {
        max = i;
        for(int j = i+1;j < str.size_current;j++)
        {
            if(strcmp(str.array[max], str.array[j]) > 0)
                max = j;
        }
        if(max != i)
        {
            buff = str.array[max];
            str.array[max] = str.array[i];
            str.array[i] = buff;
        }
    }
}
string_struct init_string_list()
{
    string_struct str_list;
    str_list.array = (char**)malloc(10 * sizeof(char*));
    str_list.array[0] = NULL;

    str_list.size = array_size;
    str_list.size_current = 0;
    
    return str_list;
}
