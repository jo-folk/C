/* COP 3502C Programming Assignment 4
This program is written by: Joanna Folk */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "leak_detector_c.h"


// node of a trie
struct trie {
    int isWord;
    int freq;
    int sum_of_freq;
    int max_child;
    struct trie* next[26];
};


// For Adding a word to the dictionary
void insert(struct trie* tree, char word[],int num_times);
void insertRec(struct trie* tree, char word[], int k, int wordlen,int num_times);

// For  query with a prefix
char* prefixQuery(struct trie* tree, char word[]) ;
char* prefixQueryRec(struct trie* tree, char word[], int k, int wordlen);

// Start, printing, freeing.
struct trie* init( int k, int num_times);
void freeDictionary(struct trie* tree);

int main(void) {
    atexit(report_mem_leak);
    struct trie* myDictionary = init(0,0);
    int i, n;
    FILE* ifp = fopen("in.txt", "r");
    FILE *outFile = fopen("out.txt", "w"); 
    fscanf(ifp, "%d", &n);

    int sum = 0;

    // Read in each word and insert it.
    for (i=0; i<n; i++) {
        // printf("here,%d",i);
        int query;
        char word[2000000];
        fscanf(ifp, "%d", &query);
        fscanf(ifp, "%s", word);
        if(query==1){
            int num_times;
            fscanf(ifp, "%d", &num_times);
            insert(myDictionary, word,num_times);

        }
        else if(query==2){
            char* ans=prefixQuery( myDictionary, word);
            if(ans==NULL){
                fprintf(outFile,"unknown word\n");
            }
            else{
                fprintf(outFile,"%s\n",ans);
            }
            free(ans);
        }
        else{
            fprintf(outFile,"invalid query...exiting");
            break;
        }
    }
    freeDictionary(myDictionary);
    // Clean up.
    fclose(ifp);
    fclose(outFile);

    return 0;
}

struct trie* init( int k, int num_times){

    // Create the struct, not a word.
    struct trie* myTree = malloc(sizeof(struct trie));
    myTree->isWord = 0;
    myTree->freq=num_times;
    myTree->sum_of_freq=k*num_times;
    myTree->max_child=0;
    // Set each pointer to NULLL.
    int i;
    for (i=0; i<26; i++)
        myTree->next[i] = NULL;

    // Return a pointer to the new root.
    return myTree;
}

// Provide this function for the user...
void insert(struct trie* tree, char word[],int num_times) {
    return insertRec(tree, word, 0, strlen(word),num_times);
}

// Recursive insert function that does all the work.
// k represents how many letters down the trie we have gone.
void insertRec(struct trie* tree, char word[], int k, int wordlen,int num_times) {

    // Down to the end, insert the word.
    if (k == wordlen) {
        tree->isWord = 1;

        return;
    }

    // See if the next place to go exists, if not, create it.
    int nextIndex = word[k] - 'a';
    if (tree->next[nextIndex] == NULL)
        tree->next[nextIndex] = init(  k+1,num_times);
    else{
        tree->next[nextIndex]->freq+=num_times;
        tree->next[nextIndex]->sum_of_freq+=(k+1)*num_times;
    }
    if ((tree->max_child)<((tree->next[nextIndex])->freq)){
        tree->max_child=((tree->next[nextIndex])->freq);
        // printf("max of %c updated to %d\n",(nextIndex+'a'),tree->max_child);
    }

    // Insert recursively down the path of this word, advancing one letter.
    insertRec(tree->next[nextIndex], word, k+1, wordlen,num_times);

}

// Wrapper function returns the pointer to a char arr of predictions
char* prefixQuery(struct trie* tree, char word[]) {
    return prefixQueryRec(tree, word, 0, strlen(word));
}

// Recursive prefixQuery from level k of the trie for word.
char* prefixQueryRec(struct trie* tree, char word[], int k, int wordlen) {
    
    // if the last character of prefix, checking for the max childs and returning the array of predicted characters
    
    if (k == wordlen){
        
        if(tree->max_child==0){
            return NULL;
        }
        char *arr=malloc(27*sizeof(char));
        // return NULL;
        int count=0;
        for(int i=0;i<26;i++){
            if((tree->next[i]!=NULL) && (tree->next[i]->freq==tree->max_child)){
                arr[count]=(char)(i+'a');
                count++;
            }
        }
        arr[count]='\0';
        return arr;
    }
    

    // If the next place doesn't exist, no predicted char returning a nullptr
    int nextIndex = word[k] - 'a';
    if (tree->next[nextIndex] == NULL)
        return NULL;

    return prefixQueryRec(tree->next[nextIndex], word, k+1, wordlen);
}

// Just frees all the memory pointed to by tree (directly and indirectly)
void freeDictionary(struct trie* tree) {

    int i;
    for (i=0; i<26; i++)
        if (tree->next[i] != NULL){
            // printf("%c\n",(i+'a'));
            // printf( "%d\n",tree->next[i]->freq);
            // printf("%d\n",tree->next[i]->sum_of_freq);
            // printf("%d\n",tree->next[i]->max_child);
            freeDictionary(tree->next[i]);
          
        }

    free(tree);
    // printf("here\n");
}

