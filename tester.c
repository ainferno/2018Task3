#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        write(2, "ERROR, NEED MORE FILES\n", 23);
        return 0;
    }
    int f1 = open(argv[1], O_RDONLY);
    int f2;
    int n = 0;
    char c1, c2;
    for(int i = 3;i < argc;i++)
    {
        f2 = open(argv[i], O_RDONLY);
        while(c1 > )
        close(f2);
    }
    close(f1);
    return 0;
}