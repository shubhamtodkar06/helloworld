#include <cs50.h>
#include <stdio.h>

void build(int wide);
int main(void)
{
    int height = get_int("Height :- ");
    build(height);


}
void build(int wide)
{
    if(wide <= 0)
    {
        return;
    }
    build(wide - 1);
    for(int i = 0; i < wide; i++)
    {
        printf("#");
    }
    printf("\n");
}
