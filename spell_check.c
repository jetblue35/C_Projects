#include <stdio.h>
#include <string.h>
#define MAX 50

int check_same(char* s1, FILE* fp);
char find_correct_char(char* s1, char* s2);
int incorrect_index(char* s1, char* s2);
int find_in_dic(char* s1, FILE* fp);
int count_difference(char* s1, char* s2);
int len_of_str(char* s);
void duz(char* s1);
int noktalama(char* s1);
void fix_spelling_error(char* s1, FILE* fp,int* ret, int* index, char* ch);

int main(int argc, char const *argv[])
{
	char str1[MAX], str2[MAX];
	FILE* fp_t = fopen("text.txt","r+");
	int len;
	FILE* fp_d;
	int err; 
	int index = 0;
	char ch;

	int ret = 0;
	while(fscanf(fp_t, "%s",str1) == 1)
	{
		//fscanf(fp_t, "%s",str1);
		len = len_of_str(str1);
		if( noktalama(str1) == 1)		//If there are any punctuatin, fix it.
		{
			duz(str1);
		}
		if( check_same(str1, fp_d) == 1 )			//Check the dictionary.
		{
			continue;
		}
		else
		{

			fix_spelling_error(str1, fp_d, &ret, &index, &ch);		//Check the spelling.

			if(ret == 1)
			{
				fseek(fp_t, index - len, SEEK_CUR);
				fprintf(fp_t, "%c", ch);					//Fix character and move back.
				fseek(fp_t, len - index, SEEK_CUR);
			}

			ret = 0;
		}
		
	}
	


	return 0;
}

char find_correct_char(char* s1, char* s2)	//This func find the correct character and return it.
{
	char ch;
	
	while(*s1 != '\0' || *s2 != '\0')
	{
		if(*s1 == *s2)		//If they are equal.
		{
			++s1;
			++s2;
		}
		else if ( (*s1 == '\0' && *s2 != '\0') || (*s1 != '\0' && *s2 == '\0') || (*s1 != *s2) )	//If not equal.
		{
			ch = *s2;		
			break;
		}
	}
	return ch;		//return char.
}	


int incorrect_index(char* s1, char* s2)	//Find incorrect char's index and return.
{
	int ret;
	int c = 0;
	while(*s1 != '\0' || *s2 != '\0')
	{
		if(*s1 == *s2)		//If strings are equal.
		{
			++s1;
			++s2;
			++c;
		}
		else if ( (*s1 == '\0' && *s2 != '\0') || (*s1 != '\0' && *s2 == '\0') || (*s1 != *s2) )	//If not equal.
		{
			ret = c;		//Index.
			break;
		}
	}
	return c;			//return index.
}
int count_difference(char* s1, char* s2)	//Find number of difference character.
{
	int counter = 0;

	while(*s1 != '\0' || *s2 != '\0')
	{
		if(*s1 != *s2)	//If char not equal, increase the counter.
		{
			counter++;
		}
		++s1;
		++s2;
	}
	return counter;
}
int len_of_str(char* s)		//Find length of string.
{
	int c = 0;
	while(*s != '\0')
	{
		++s;	
		++c;
	}
	return c;
}
/*This func if the dictionary consist wrong word, then return index and correct character.*/
void fix_spelling_error(char* s1, FILE* fp, int* ret, int* index, char* ch)
{
	fp = fopen("dictionary.txt","r");
	char word[MAX];
	int res;
	
	while(!feof(fp))		//Read end of file.
	{
		fscanf(fp, "%s", word);
		res = count_difference(s1, word);
		if(res == 1)
		{
			*ch = find_correct_char(s1, word);		//Find correct char.
			*index = incorrect_index(s1, word);		//Find incorrect index.
			*ret = 1;
			break;
		}	

	}
	fclose(fp);
	
}
int check_same(char* s1, FILE* fp)		//If the word read is in the dictionary, it returns 1.
{
	fp = fopen("dictionary.txt","r");
	char word[MAX];
	int check;
	int res = 0;
	while(!feof(fp))
	{
		fscanf(fp, "%s", word);
		check = strcmp(s1, word);
		if(check == 0)
		{
			res = 1;
			break;
		}
		
	}
	return res;
}


int noktalama(char* s1)		//If there are any punctuation, return 1, otherwise 0.
{
	int res = 0;
	while(*s1 != '\0')
	{
		if(*s1 < 97 || *s1 > 122)
		{
			res = 1;
		}
		++s1;
	}	
	return res;	
}
void duz(char* s1)			//This function fix the punctuation.
{
	if(*s1 < 97 || *s1 > 122)			//If first index is a punctuation return *(s +1).
	{
		*s1 = *(s1 + 1);				
		
	}
	else								//Assign the string up to the punctuation to the string.
	{
		while(*s1 != '\0')
		{
			++s1;	
			if(*s1 < 97 || *s1 > 122)
			{	
				*(s1 - 1) = '\0';
		
			}

			
		}
	}

}
