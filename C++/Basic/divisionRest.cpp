#include <iostream>
#include <cstdlib>
#include <time.h> 
 
int main()
{
    srand(time(0));

    printf("%i\n", rand()%4);
    return 0;
}