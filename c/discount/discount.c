#include<cs50.h>
#include<stdio.h>

float discount(float price , int percentage)
{
    return price * (100- percentage)/100;
}
int main(void)
{
    float regular = get_float("Regular price :- ");
    float percentoff = get_int("percent of:- ");
    float sale = discount( regular , percentoff );
    printf("sale price :- %2f\n" , sale);
}