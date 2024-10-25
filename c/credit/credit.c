#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long i;
    do
    {
     i = get_long("Number: ");
     
    }
    while( i < 100000000000 || i > 999999999999);

    long j = 10;
    long a = 0;
    while ( j < i)
    {
      a = a + (i % j);
      j = j * 100;
    }
    printf("%ld\n" , a);
}