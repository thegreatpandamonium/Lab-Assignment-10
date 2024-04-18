#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie *createTrie();

// Trie structure
struct Trie
{	
    int count; // end of word
    struct Trie* next[26];
    int wordCount;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int len = strlen(word);

    for(int i=0; i<len; i++){
        if(pTrie->next[word[i] - 'a'] == NULL) {
            pTrie->next[word[i] - 'a'] = createTrie(); 
        }
        pTrie = pTrie->next[word[i] - 'a'];
        pTrie->wordCount++;
    }
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    return pTrie->wordCount;

}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for (int i=0; i<26;i++){
        if(pTrie -> next[i] != NULL)
            deallocateTrie(pTrie->next[i]);
    }

    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *myTree= malloc(sizeof(struct Trie));
    myTree->count = 0;
    myTree ->wordCount = 0;

    int i;

    for(i=0; i<26; i++){
        myTree->next[i] = NULL;
    }

    return myTree;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
     FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int numWords = 0;
    char word[100]; 

    while (fscanf(file, "%s", word) == 1) {
        pInWords[numWords] = strdup(word); 
        numWords++;
    }

    fclose(file);
    return numWords;
    

}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}