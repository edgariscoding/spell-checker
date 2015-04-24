/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

unsigned int totalDict = 0; 
node* hashTable[HASHTABLE_SIZE];

// Hash Function - Credit: /u/delipity
int hash_it(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
	int length = strlen(word);
	char tempWord[length + 1];
	
	for (int i = 0; i <= length; i++)
	{
		tempWord[i] = tolower(word[i]);
	}
	
    node* ptr = hashTable[hash_it(tempWord)];
    
    
    while (ptr != NULL)
    {
		if (strcmp(ptr->word, tempWord) == 0)
		{
			return true;
		}
		else
		{
			ptr = ptr->next;
		}
    }
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
	// Create temporary char array
	//char tempWord[LENGTH+1];
	
    // Open dictionary file for reading
    FILE* fp;
    fp = fopen(dictionary, "r");
    
    // If file is NULL, return false
    if(fp == NULL)
    {
    	return false;
    }
    
    // Initialize new node
    node* new_node = malloc(sizeof(node));
    
    // While fscanf() does not return EOF, continue reading from file
    while (fscanf(fp, "%s", new_node->word) != EOF)
    {
    	// If fp returns an error, return false
    	if (ferror(fp))
    	{
    		return false;
    	}
    	// Else, insert node to the beginning of the list
    	else 
    	{
    		totalDict++;
    		// Store hash function result in key
    		int key = hash_it(new_node->word);
    		
    		// Insert node at beginning of list
    		new_node->next = hashTable[key];
    		hashTable[key] = new_node;
    		
    		// Malloc node for next word
    		new_node = malloc(sizeof(node));
    	}
    }
    
    // Return true once all dictionary words are loaded
    free(new_node);
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    	return totalDict;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
    	node* ptr = hashTable[i];
    	
    	while (ptr != NULL)
    	{
    		node* temp = ptr;
    		ptr = ptr->next;
    		free(temp);
    	}
    }
    return true;
}
