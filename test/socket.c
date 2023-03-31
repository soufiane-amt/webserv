#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int *func()
{
    int a = 4;
    return &a;
}

int main(int argc, char const *argv[])
{
    int *ptr = func();
    return 0;
}
