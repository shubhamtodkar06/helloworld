#include <cs50.h>
#include <stdio.h>

int main(void)
{


    int height;

    do
    {
        height = get_int("Height of pyiramid :- ");
    }
    while( height <= 0 || height >= 9);

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < (height - i -1); j++)
        {
            printf(" ");
        }
        for(int j = 0; j <=i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
