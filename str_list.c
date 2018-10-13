#include "sh.h"
// #include "str_list.h"
//Variables
int string_list_size = 10;//Текущий максимальный размер массива
int string_list_size_current = 0;//Текущий размер массива

void copy_str(char *a, char *b)
{
    for(;*b != '\0';a++, b++)
        *a = *b;
    *a = '\0';
}

string_list add_string_list(string_list str, char *elem, int elem_size)
{
    if(string_list_size_current == string_list_size)//Если выходим за пределы массива то перевыделяем память под него
    {
        string_list_size*=2;
        str = realloc(str, sizeof(char*) * string_list_size);
    }
    str[string_list_size_current] = (char*)malloc(sizeof(char) * elem_size);//ERROR
    copy_str(str[string_list_size_current], elem);//Нельзя делать простое приравнивание так как в таком случае
    string_list_size_current++;//если вне функции очистить то что передали очистим, то и тут пропадет
    return str;//А мы хотим функцию которая работает корректно не зависимо от реализации программы ее вызывающей
}
void clean_string_list(string_list str)
{
    // printf("POINT CUR = %d, MAX = %d\n", string_list_size_current, string_list_size);
    // printf("str = %s\n", str[0]); 
    for(int i = 0;i < string_list_size_current;i++)// WHY ERROR IF UNCOMMENTED?
        free(str[i]);// Тут утечка памяти, но я пока не знаю почему, похоже на ошибку подобную такой в таске 2.5
    free(str);
}
void print_string_list(string_list str)
{
    for(int i = 0;i < string_list_size_current;i++)
    {
        int size_of_str = strlen(str[i])+1;//Так как мы выводим в файл, то мы используем буфер чтобы
        char out_buff[size_of_str];//Добавить символы ' '/'\n' в конец
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
