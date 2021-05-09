#include <stdio.h>

#define WORDSIZE 50

void clean_file(char* infile, char* outfile, char* words_to_delete[WORDSIZE], int number_of_words);
void delete_words(FILE* infid, FILE* outfid, char* words_to_delete[WORDSIZE], int number_of_words);
int checkWord(char* dest, char* words_to_delete[WORDSIZE], int number_of_words);
int isLast(char* word);
int strCmp(char* s1, char* s2);
int strLen(char* s);

int main()
{
    char inFileName[WORDSIZE] = "input.txt";
    char outFileName[WORDSIZE] = "output.txt";
    char* words[WORDSIZE] = {
        "good",
        "geek",
        "hello",
        "moon"
    };
    int number_of_words = 4;

    clean_file(inFileName, outFileName, words, number_of_words);
    return 0;
}

void clean_file(char* infile, char* outfile, char* words_to_delete[WORDSIZE], int number_of_words)
{
    FILE* infid, *outfid;
    
    infid = fopen(infile, "r+");
    
    if(infid == NULL)
    {
        fprintf(stderr, "Error! No such file: %s\n", infile);
        return;
    }
    
    outfid = fopen(outfile, "w");
    
    if(outfid == NULL)
    {
        fprintf(stderr, "Error! No such file: %s\n", outfile);
        return;
    }
    
    delete_words(infid, outfid, words_to_delete, number_of_words);
}

void delete_words(FILE* infid, FILE* outfid, char* words_to_delete[WORDSIZE], int number_of_words)
{
    char buffer[WORDSIZE];

    if(fscanf(infid, "%s", buffer) != 1)
        return;

    int endline = isLast(buffer);

    if(endline != -1)
        buffer[endline] = '\0';

    if(checkWord(buffer, words_to_delete, number_of_words) == 0)
    {
        fprintf(outfid, "%s", buffer);
        
        if(endline == -1)
            fprintf(outfid, " ");
    }

    if(endline != -1)
        fprintf(outfid, ".\n");

    delete_words(infid, outfid, words_to_delete, number_of_words);
}

int checkWord(char* dest, char* words_to_delete[WORDSIZE], int number_of_words)
{
    if(number_of_words == 0)
        return 0;
    
    if(strCmp(dest, words_to_delete[number_of_words - 1]) == 0)
        return 1;
    
    return checkWord(dest, words_to_delete, number_of_words - 1);
}

// Returns -1 if the word is not last word in the row. (does not include '.')
// Otherwise returns index of '.' character
int isLast(char* word)
{
    int len = strLen(word);

    if(word[len - 1] == '.')
        return len - 1;
    else
        return -1;
}

int strCmp(char* s1, char* s2)
{
    if(*s1 && *s2 && *s1 == *s2)
        return strCmp(s1 + 1, s2 + 1);
    
    return *s1 - *s2;
}

int strLen(char* s)
{
    if(!*s)
        return 0;
    
    return 1 + strLen(s + 1);
}