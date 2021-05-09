#include<stdio.h>
#include<string.h>

#define MAX_LENGTH 10
#define MAX_COLUMN 250
#define MAX_ROW 100

const char horizontal_value = 'h'; //These global values for search function 
const char vertical_value = 'v'; 

char search(int, char*, int*, int*);
int find_smallest(int[], int);

void main()
{
    char word[MAX_LENGTH];
      
    int size_of_word,vert_coord,hor_coord;				//Some declarations
      
    FILE *f_input1, *f_output;
      
    f_input1 = fopen("input1.txt","r");
      
    f_output = fopen("output.txt","w");
      
    while(fscanf(f_input1,"%s",word)!= EOF)     //I didn't use array for store the words, I am searching (check) the words in order.
    {
        size_of_word=strlen(word);          //Length of the word.
            
        if(search(size_of_word, word, &vert_coord, &hor_coord) == horizontal_value)		//Check horizontal or vertical
        {
            fprintf(f_output,"%s (%d,%d) Horizontal\n",word,hor_coord,vert_coord);
        }      
            
        else if(search(size_of_word, word, &vert_coord, &hor_coord) == vertical_value)	//Check horizontal or vertical
        {
            fprintf(f_output,"%s (%d,%d) Vertical\n",word,vert_coord,hor_coord);
        }      
                  

    }
    fclose(f_input1);
      
    fclose(f_output);

}

char search(int size_of_word, char* word, int* vert_coord, int* hor_coord)
{
      
    char row[MAX_COLUMN], text[MAX_ROW][MAX_COLUMN];
      
    int row_size[MAX_COLUMN], smallest_row, number_of_rows = 0, check = 0, c = 0, size = 0;
      
    int i, j;
    FILE* f_input2;
      
    f_input2 = fopen("input2.txt","r");
      
    // Read text.
    while(fscanf(f_input2, "%s", row) != EOF)              // I read the text file and assigned to the array.
    {
        row_size[number_of_rows] = strlen(row);     
            
        for(i = 0; i < row_size[number_of_rows]; i++)
        {
            text[number_of_rows][i] = row[i];
        }      
            
        number_of_rows++;                              
    }
      
    for(i = 0; i < number_of_rows; i++)             //For horizontal.
    {
        for(j = 0; j < row_size[i]; j++)
        {
            if(text[i][j] == word[check])             // Check first character of the word.
            {
                check = j;
                while(text[i][check] == word[c] && size != size_of_word)        //If it is same, check the length of horizontally. 
                {
                    c++;
                    size++;
                    check++;
                              
                }
                if(size == size_of_word)            // If the length is equal, return the true value. 
                {
                    *vert_coord=j+1; 
                    *hor_coord=i+1; 
                     return horizontal_value;
                }
                else
                {
                    c=0,size=0,check=0;                 // If it is not, reseted the values and try again.
                }
            }
        }
    }
      
    size = 0, c = 0, check = 0;                                 //Reset the values.
      
    smallest_row = find_smallest(row_size,number_of_rows);      //Find the smallest row in text ,cause If we check words vertically, we must find the smallest row.
      
    for(i= 0; i < smallest_row;i++)                                 //For vertical.
    {
        for(j = 0; j < number_of_rows; j++)
        {
            if(text[j][i] == word[check])                     // I checked the character in the location and the first character of the word 
            {
                check = j; 
                while(text[check][i] == word[c] && size != size_of_word)    //If it is same, checked the length of vertically.
                {
                    c++;
                    size++;
                    check++;
                              
                }
                if(size == size_of_word)                  // If the length is equal, return the true value. 
                {
                    *vert_coord = j+1; 
                    *hor_coord = i+1; 
                    return vertical_value;
                }
                else
                {
                    c= 0,size = 0, check = 0;                 // If it is not, reseted the values and try again.
                }
            }
        }
    }
    fclose(f_input2);
}
int find_smallest(int a[], int size)                        //This function for use in searching in verticvally, and it find and returns min position in array.  
{
    int min = a[0];
      
    int i;
      
    for(i = 1; i < size; i++)
    {
        if(a[i] < min)
        {
            min = a[i];
        }      
    }      
    return min;
}