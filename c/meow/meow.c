#include<stdio.h>

void meow(void);


int main(void)
{
    meow();

}


void meow(void)
{
    int i = 0;
    while(i<10)
    {
       printf("meow\n");
        i++;

    }
}