#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int number_letters(string text);
int number_sent(string text);
int number_word(string text);

int main(void)
{
    string text = get_string("Text: ");
    float X = number_letters(text);
    float Y = number_word(text);
    float Z = number_sent(text);
    // L average number of letters per 100 words
    float L = (X / Y) * 100;
    // S average number of sentence per 100 words
    float S = (Z / Y) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index < 1.5)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 1.5 && index < 2.5)
    {
        printf("Grade 2\n");
    }
    else if (index > 2.5 && index < 3.5)
    {
        printf("Grade 3\n");
    }
    else if (index > 3.5 && index < 4.5)
    {
        printf("Grade 4\n");
    }
    else if (index > 4.5 && index < 5.5)
    {
        printf("Grade 5\n");
    }
    else if (index > 5.5 && index < 6.5)
    {
        printf("Grade 6\n");
    }
    else if (index > 6.5 && index < 7.5)
    {
        printf("Grade 7\n");
    }
    else if (index > 7.5 && index < 8.5)
    {
        printf("Grade 8\n");
    }
    else if (index > 8.5 && index < 9.5)
    {
        printf("Grade 9\n");
    }
    else if (index > 9.5 && index < 10.5)
    {
        printf("Grade 10\n");
    }
    else if (index > 10.5 && index < 11.5)
    {
        printf("Grade 11\n");
    }
    else if (index > 11.5 && index < 12.5)
    {
        printf("Grade 12\n");
    }
    else if (index > 12.5 && index < 13.5)
    {
        printf("Grade 13\n");
    }
    else if (index > 13.5 && index < 14.5)
    {
        printf("Grade 14\n");
    }
    else if (index > 14.5 && index < 15.5)
    {
        printf("Grade 15\n");
    }
    else
    {
        printf("Grade 16+\n");
    }

}

// function to count number of letters.
int number_letters(string text)
{
    int a = 0;
    for (int i = 0, len = strlen(text); i < len ; i++)
    {
        if (isalpha(text[i]))
        {
            a = a + 1;
        }
        else
        {
            a = a + 0;
        }
    }
    return a;
}

// function to count number of words.
int number_word(string text)
{
    int a = 0;
    for (int i = 0, len = strlen(text); i < len ; i++)
    {
        if (isspace(text[i]))
        {
            a = a + 1;
        }
        else
        {
            a = a + 0;
        }
    }
    return a + 1;

}

// function to count number of sentences.
int number_sent(string text)
{
    int a = 0;
    for (int i = 0, len = strlen(text); i < len ; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            a = a + 1;
        }
        else
        {
            a = a + 0;
        }
    }
    return a;

}