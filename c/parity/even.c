#include<cs50.h>
#include<stdio.h>

int main(void)
{
    int i = get_int("What's your number?\n");
    if(i % 2 == 0)
    {
        printf("Your number is even.\n");
    }
    else
    {
        printf("Your number is odd.\n");
    }
}