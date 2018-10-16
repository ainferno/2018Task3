#include "sh.h"
#include "buf.h"
#include<setjmp.h>
jmp_buf begin;

//Functions
string_struct input(string_struct);//Считывает строку, добавляет в массив сстрок, возвращает этот массив

string_struct input(string_struct lst)
{
    char *str = NULL;//Текущая строка
    char c;//Текущий символ
    int N = input_size, i = 0;//N - макс размер текущей строки, i - размер текущей строки
    str = (char*)malloc(N*sizeof(char));//Выделяем память
    while((c = get_char(0)) != '\0')
    {
        if(i == N)//Если считанная строка не укладывается в нашу строку то перевыделяем память увеличивая в 2 раза место
        {
            N*=2;
            str = (char*)realloc(str, N*sizeof(char));
        }
        switch(c)
        {
            case '|': case '&': case '>'://Если текущее слово не определенно однозначно тоесть | или ||, & или && и.т.д.
                if(i!=0)//Если текущее слово не пустое, то вначале добавляем его в массив
                {
                    str[i] = '\0';
                    lst = add_string_list(lst,str,i+1);

                    free(str);
                    N = input_size;
                    i = 0;
                    str = (char*)malloc(N*sizeof(char));
                }
                while(c == '|' || c == '&' || c == '>')//Обрабатываем весь набор особыз спецсимволов | & > за раз, пока не встретим обычное слово
                {//Или не повторяющееся
                    str[i++] = c;
                    c = get_char(0);
                    if(c == str[i-1])//Если символ повторятся т.е. мы имеем && || >>
                    {//Добавляем его в слово
                        str[i++] = c;
                        c = get_char(0);
                    }
                    str[i] = '\0';//Записываем это слово в массив
                    lst = add_string_list(lst,str,i+1);

                    free(str);//Обнуление всего
                    N = input_size;
                    i = 0;
                    str = (char*)malloc(N*sizeof(char));
                }
                break;
            case ';': case '<': case '(': case ')':
                if(i!=0)//Если слово не пустое, то добавляем его в массив
                {
                    str[i] = '\0';
                    lst = add_string_list(lst,str,i+1);

                    free(str);//Обнуление всего
                    N = input_size;
                    i = 0;
                    str = (char*)malloc(N*sizeof(char));
                }
                str[i++] = c;//Записываем наше спецслово в строку, а дальше аналогично case ' ':...
            case ' ': case '\t': case '\n':
                if(i!=0)
                {//Если слово не пустое(т.е. мы не смотрим на посл. пробелов) то добавляем его в массив
                    str[i] = '\0';
                    lst = add_string_list(lst,str,i+1);

                    free(str);//Обнуление всего
                    N = input_size;
                    i = 0;
                    str = (char*)malloc(N*sizeof(char));
                }
        }//Слова состоят из символов+букв+набора символов '&' '_' '/ '.'
        if( c >= '0' && c <= '9' ||
            c >= 'a' && c <= 'z' ||
            c >= 'A' && c <= 'Z' ||
            c == '&' || c == '_' || c == '/' || c == '.')
        {
            str[i++] = c;
        }
        else
        {
            switch(c)
            {
                case ' ': case '\n': case '\t': 
                case ';': case '<': case '(': case ')': 
                case '&': case '|': case '>':
                    break;
                default:
                    lst = clean_string_list(lst);
                    get_char(1);

                    char message[100] = "\nError!Symbol ' ' is not allowed. Please restart.\n";
                    message[15] = c;
                    fwrite(message,sizeof(char), strlen(message),stderr);
                    
                    longjmp(begin,1);
            }
        }
    }

    free(str);//Отчистка памяти выделенной под строку
    return lst;
}

int main()
{
    string_struct str_lst;//Инициализируем массив символов
    setjmp(begin);
    printf("==>");
    str_lst = init_string_list();
    str_lst = input(str_lst);//Вводим слова в массив
    print_string_list(str_lst);//Выводим массив
    sort_string_list(str_lst);//Сортируем массив
    print_string_list(str_lst);//Выводим массив
    clean_string_list(str_lst);//Отчищаем массив
    return 0;
}
