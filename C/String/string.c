#include <stdio.h>
#include <string.h>

void function(char* str);

int main()
{
    char* str = "ABCDhags12";
    function(str);
}

void function(char* str)
{
    printf("\n%s",str);
}