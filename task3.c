#include <stdio.h>
#include <stdlib.h>
#include "str_list.h"
#include "buffer.h"

int main()
{
    char c, b[10] = "qwerty";
    
    while((c = get_c()) != '\0')
        printf("%c", c);
    return 0;
}
