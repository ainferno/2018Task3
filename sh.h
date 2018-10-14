#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define buf_size 10u //Определяем размер буффера
//Types
typedef char **string_list;//Массив строк

typedef struct str_lst_struct
{
    string_list array;
    int size, size_current;
}string_struct;

//Functions buf
int fill_buf(char*);//Заполняет буфер, возвращает количество считанных символов
void clean_buf(char*);//Отчищает буфер
void clean_input();//Отчищает весь входной поток
char get_char();//Возвращает символ из буфера, если буфер пуст то заполняет его, если и там пусто возвращает '\0'   
//Functions string list
void copy_str(char*, char*);//Копирует строку 2 в строку 1 посимвольно
string_struct add_string_list(string_struct, char*, int);//Добавляет строку в конец массива строк, возвращает этот массив
string_struct clean_string_list(string_struct);//Отчищает массив. НЕ ВЕРНО ТАК КАК ПРИСУТСВУЕТ УТЕЧКА ПАМЯТИ
void print_string_list(string_struct);//Выводит массив строк в stdout, через пробелы заканчивая \n
void sort_string_list(string_struct);//Сортирует массив строк по возрастанию методом простого выбора
string_struct init_string_list();//Выделяет памят под массив строк, возвращает этот массив
//Functions task3