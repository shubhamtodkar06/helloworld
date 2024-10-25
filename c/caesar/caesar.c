#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2 && isdigit(*argv[1]))
    {
        int a = atoi(argv[1]);
        string s = get_string("plaintext:  ");
        printf("ciphertext: ");

        for (int i = 0,  len = strlen(s); i < len; i++)
        {

            if (isupper(s[i]) && isalpha(s[i]))
            {
                int x = (s[i] - 'A');
                char m = (x + a) % 26 + 'A';
                printf("%c", m);
            }
            else if (islower(s[i]) && isalpha(s[i]))
            {
                int x = (s[i] - 'a');
                char n = (x + a) % 26 + 'a';
                printf("%c", n);
            }
            else
            {
                printf("%c", s[i]);
            }

        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key\n");
    }
}

