// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Initialize number of words loaded
unsigned int words_loaded = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Apply hash to given word
    unsigned int hashed_index = 0;
    hashed_index = hash(word);

    // Dictionary is all lowercase, so we should change the word we need to be checked to be lowercase as well
    char lowercased_word[LENGTH + 1];

    for (int i = 0; i < LENGTH + 1; i++)
    {
        if (word[i] == '\0')
        {
            lowercased_word[i] = '\0';
            break;
        }
        lowercased_word[i] = tolower(word[i]);
    }

    // Check if word matches dictionary word at appropriate hash index
    for (node *tmp = table[hashed_index]; tmp != NULL; tmp = tmp->next)
    {
        if (strcmp(tmp->word, lowercased_word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open dictionary
    FILE *reader = fopen(dictionary, "r");
    if (reader == NULL)
    {
        return false;
    }

    char word_buffer[LENGTH + 1];
    while (fscanf(reader, "%s", word_buffer) != EOF)
    {
        // Allocate space for new word to be put into hash table
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            free(n);
            return false;
        }
        for (int i = 0; i < LENGTH + 1; i++)
        {
            // At this point, node has not yet been put into table, so table should still be null
            n->word[i] = word_buffer[i];
        }

        // Hash the word
        unsigned int hashed_index = hash(n->word);

        // If there's no word at that hash index
        if (table[hashed_index] == NULL)
        {
            n->next = NULL;
            table[hashed_index] = n;
        }

        // If there's already a word at that hash index
        else
        {
            n->next = table[hashed_index];
            table[hashed_index] = n;
        }
        words_loaded ++;
    }
    fclose(reader);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (words_loaded > 0)
    {
        return words_loaded;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
