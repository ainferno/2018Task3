#include "sh.h"
#include "buf.h"
#include <setjmp.h>

jmp_buf begin;

//Functions
string_struct input(string_struct, char*);//Считывает строку, добавляет в массив сстрок, возвращает этот массив
void error(char, char*, int);

void error(char c, char *buf, int i)
{
    int a = 0;
    char message[100] = "Error!Symbol ' ' is not allowed. Please restart.\n";
    message[14] = c;
    write(2,message,strlen(message));//Выводим сообщение об ошибке
    
    a = get_char(buf,&i);
    while(a != END_OF_STR && a != END_OF_INP)
        a = get_char(buf,&i);
    if(a == END_OF_INP)
        clean_input();
    longjmp(begin,1);//В случае ошибки перезапускаем пронрамму
}
string_struct input(string_struct lst, char *buf)
{
    char *str = NULL;//Текущая строка
    int c = 0;//Текущий символ
    int N = input_size, i = 0, buf_i = buf_size;//N - макс размер текущей строки, i - размер текущей строки
    str = (char*)malloc(N*sizeof(char));//Выделяем память
    write(1,"==>",3);
    c = get_char(buf,&buf_i);
    while(c != END_OF_INP)
    {
        while(c != END_OF_STR && c != END_OF_INP)
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

                        if(N >= 1000)
                        {
                            N = input_size;
                            str = (char*)realloc(str, N*sizeof(char));
                        }
                        else
                            str[0] = '\0';
                        i = 0;
                        str = (char*)malloc(N*sizeof(char));
                    }
                    while(c == '|' || c == '&' || c == '>')//Обрабатываем весь набор особыз спецсимволов | & > за раз, пока не встретим обычное слово
                    {//Или не повторяющееся
                        str[i++] = c;
                        c = get_char(buf,&buf_i);
                        if(c == str[i-1])//Если символ повторятся т.е. мы имеем && || >>
                        {//Добавляем его в слово
                            str[i++] = c;
                            c = get_char(buf,&buf_i);
                        }
                        str[i] = '\0';//Записываем это слово в массив
                        lst = add_string_list(lst,str,i+1);

                        if(N >= 1000)
                        {
                            N = input_size;
                            str = (char*)realloc(str, N*sizeof(char));
                        }
                        else
                            str[0] = '\0';
                        i = 0;
                        str = (char*)malloc(N*sizeof(char));
                    }
                    break;
                case ';': case '<': case '(': case ')':
                    if(i!=0)//Если слово не пустое, то добавляем его в массив
                    {
                        str[i] = '\0';
                        lst = add_string_list(lst,str,i+1);

                        if(N >= 1000)
                        {
                            N = input_size;
                            str = (char*)realloc(str, N*sizeof(char));
                        }
                        else
                            str[0] = '\0';
                        i = 0;
                        str = (char*)malloc(N*sizeof(char));
                    }
                    str[i++] = c;//Записываем наше спецслово в строку, а дальше аналогично case ' ':...
                case ' ': case '\t': case '\n':
                    if(i!=0)
                    {//Если слово не пустое(т.е. мы не смотрим на посл. пробелов) то добавляем его в массив
                        str[i] = '\0';
                        lst = add_string_list(lst,str,i+1);

                        if(N >= 1000)
                        {
                            N = input_size;
                            str = (char*)realloc(str, N*sizeof(char));
                        }
                        else
                            str[0] = '\0';
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
                    case -1: case -2:
                        break;
                    default:
                        clean_string_list(lst);
                        free(str);
                        error(c, buf, buf_i);
                }
            }
            c = get_char(buf,&buf_i);
        }
        if(i!=0)
        {//Если слово не пустое(т.е. мы не смотрим на посл. пробелов) то добавляем его в массив
            str[i] = '\0';
            lst = add_string_list(lst,str,i+1);
        }
        free(str);//Обнуление всего
        write(1, "\n", 1);
        print_string_list(lst);//Выводим массив
        sort_string_list(lst);//Сортируем массив
        write(1, "\n", 1);
        print_string_list(lst);//Выводим массив
        write(1, "\n", 1);
        lst = clean_string_list(lst);
        lst = init_string_list();
        N = input_size;
        i = 0;
        str = (char*)malloc(N*sizeof(char));
        write(1,"==>",3);
        c = get_char(buf,&buf_i);
    }
    free(str);//Отчистка памяти выделенной под строку
    clean_string_list(lst);
    return lst;
}

int main()
{
    string_struct str_lst;
    char buf[buf_size] = "\0";
    setjmp(begin);
    str_lst = init_string_list();//Инициализируем массив символов
    str_lst = input(str_lst, buf);//Вводим слова в массив
    write(1,"Exit\n", 5);
    return 0;
}