// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

#define HASHTABLE_SIZE 1000
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Hash table
node *hashtable[HASHTABLE_SIZE];

unsigned int num_words = 0;
bool dict_loaded;


// Hashes word to a number <source: deliberate think, youtube>
unsigned int hash(const char *word)
{
    int hash = 0;
    int n;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalpha(word[i]))
            n = word[i] - 'a' + 1;

        else
        {
            n = 27;
            hash  = ((hash << 3) + n) % HASHTABLE_SIZE;
        }
    }
    return hash;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char check_word[strlen(word)];
    strcpy(check_word, word);
    for (int i = 0; check_word[i] != '\0'; i++)
    {
        check_word[i] = tolower(check_word[i]);
    }
    int index = hash(check_word);
    if (hashtable[index] != NULL)
    {
        for (node* nodeptr = hashtable[index]; nodeptr != NULL; nodeptr = nodeptr->next)
            if (strcmp(nodeptr->word, check_word) == 0)
                return true;
    }
    return false;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    //fopen dictionary file
    FILE *infile = fopen(dictionary, "r");
    //check for NULL, if unable to open return false
    if (infile == NULL)
    {
        printf("unable to open\n");
        return false;
    }
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        hashtable[i] = NULL;

    }
    char word[LENGTH + 1];
    node* new_nodeptr;
    while(fscanf(infile, "%s", word)!= EOF)
    {
        num_words++;
        do
        {
            new_nodeptr = malloc(sizeof(node));
            if (new_nodeptr == NULL)
                free(new_nodeptr);
        } while (new_nodeptr == NULL);


        strcpy(new_nodeptr->word, word);
        int index = hash(word);

        //adding to start of linked list
        new_nodeptr->next = hashtable[index];
        hashtable[index] = new_nodeptr;
    }
    fclose(infile);
    dict_loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (!dict_loaded)
        return 0;
    return num_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (!dict_loaded)
        return false;

    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        if (hashtable[i] != NULL)
        {
            node* ptr = hashtable[i];
            while (ptr != NULL)
            {
                node* cursor = ptr;
                ptr = ptr->next;
                free(cursor);
            }
        }
    }
    return true;
}
