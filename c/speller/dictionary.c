// Implements a dictionary's functionality

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
unsigned int word_count = 0;
unsigned int hashv;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    hashv = hash(word);
    node *temp = table[hashv];
    while (temp != 0)
    {
        if (strcasecmp(word, temp->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improve this hash function
    unsigned long a = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        a += tolower(word[i]);
        a = a * tolower(word[i]) % N;
    }
    return a;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    while((fscanf(file , "%s", word)) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        n->next = NULL;
        strcpy(n->word, word);
        hashv = hash(n->word);
        n->next = table[hashv];
        table[hashv] = n;
        word_count = word_count + 1;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor)
        {
            node *temp = cursor;
            cursor = temp->next;
            free(temp);
        }
        if (cursor == NULL)
        {
            return true;
        }

    }
    return false;
}