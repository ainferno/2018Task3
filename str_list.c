#include "sh.h"
// #include "str_list.h"

void copy_str(char *a, char *b)
{
    for(;*b != '\0';a++, b++)
        *a = *b;
    *a = '\0';
}
int copy_int(char *a, int b)
{
    int i = 0, j = 0, k = 1;
    char c[100] = "\0";
    if(b < 0)
    {
        b = -b;
        k = -1;
    }
    if(b == 0)
    {
        a[0] = '0';
        a[1] = '\0';
        i = 1;
    }
    else
    {
        for(;b > 0;b/=10,j++)
        c[j] = b%10 + '0';
        c[j--] = '\0';
        if(k == -1)
            a[i++] = '-';
        for(;j >= 0;i++,j--)
            a[i] = c[j];
        a[i] = '\0';
    }
    return i;
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
    str.size = array_size;
    str.size_current = 0;
    return str;
}
void print_string_list(string_struct str)
{
    char out_buf_int[12];
    int n = copy_int(out_buf_int,str.size_current)+1;
    out_buf_int[n-1] = '\n';
    fwrite(out_buf_int, sizeof(char), n, stdout);
    for(int i = 0;i < str.size_current;i++)
    {
        int size_of_str = strlen(str.array[i])+1;//Так как мы выводим в файл, то мы используем буфер чтобы
        char out_buf[size_of_str];
        copy_str(out_buf, str.array[i]);//Добавить символы ' '/'\n' в конец
        // out_buf[size_of_str-1] = (i == str.size_current-1) ? '\n' : ' ';
        out_buf[size_of_str-1] = '\n';
        fwrite(out_buf, sizeof(char), size_of_str, stdout);
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