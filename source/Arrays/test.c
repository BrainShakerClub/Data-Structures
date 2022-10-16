#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int* p = malloc(sizeof(int*));
    free(p);

    if( p)
        printf("yes\n");

}
