#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define buf_size 10u //Определяем размер буффера
//Types
typedef char **string_list;//Массив строк
//Variables
int string_list_size = 10;//Текущий максимальный размер массива
int string_list_size_current = 0;//Текущий размер массива
//Functions
int fill_buf(char*);//Заполняет буфер, возвращает количество считанных символов
void clean_buf(char*);//Отчищает буфер
char get_char();//Возвращает символ из буфера, если буфер пуст то заполняет его, если и там пусто возвращает '\0' 
//Functions
void copy_str(char*, char*);//Копирует строку 2 в строку 1 посимвольно
string_list add_string_list(string_list, char*, int);//Добавляет строку в конец массива строк, возвращает этот массив
void clean_string_list(string_list);//Отчищает массив. НЕ ВЕРНО ТАК КАК ПРИСУТСВУЕТ УТЕЧКА ПАМЯТИ
void print_string_list(string_list);//Выводит массив строк в stdout, через пробелы заканчивая \n
void sort_string_list(string_list);//Сортирует массив строк по возрастанию методом простого выбора
string_list init_string_list();//Выделяет памят под массив строк, возвращает этот массив 