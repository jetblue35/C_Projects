#include <stdio.h>
#include <string.h>

#define MAX_SIZE_POL 1000
#define MAX_SIZE_VALUE 100

double calculate_result(char pol_exp[MAX_SIZE_POL], double value);				//This function calculates the polynomial expression for each values.
void removespaces(char* string, int* size);								//This function removes the spaces.

int main()
{
	char polynomial[MAX_SIZE_POL]; 							//Char array for polynomial expression.
	double values[MAX_SIZE_VALUE];								//Double array for values.
	double result = 0.0;
	int i=0, counterPolynomial = 0;					//Some declarations.
	int k;
	char c;
	FILE *f_value; 
	FILE *f_polynom;
	FILE *f_out;
	
	f_value = fopen("values.txt", "r");				//Open the file.
	
	if(f_value == NULL)								//If file does not exist, return (-1).
	{
		printf("Error!\n");
		return(-1);
	}
	
	while(!feof(f_value))							//Write the values from the file to array.
	{
		fscanf(f_value, "%lf", &values[i]);
		i++;
	}
	

	
	f_polynom = fopen("polynomial.txt", "r");		//Open file.
	
	if(f_polynom == NULL)							//If file does not exist, return (-1).
	{
		printf("Error!\n");
		return(-1);
	}
	

	while(fscanf(f_polynom, "%c", &c) != EOF)		//Write the polynom from file to array.
	{
		polynomial[counterPolynomial] = c;
		counterPolynomial++;
	}
	removespaces(polynomial, &counterPolynomial);	//Remove the spaces in the polynomial. 
	k = 0;
	
	f_out = fopen("evaluations.txt", "w");			//Open the file.
	
	if(f_value == NULL)								//If file does not exist, return (-1).
	{
		printf("Error!\n");
		return(-1);
	}
	
	while(k < i)									//Print results in the file.
	{
		result = calculate_result(polynomial, values[k]);

		fprintf(f_out, "%.2lf\n", result);
		k++;
	}

	fclose(f_value); 
	fclose(f_polynom);								//Closing the files. 
	fclose(f_out);

	return (0); 
	
}

double calculate_result(char pol_exp[MAX_SIZE_POL], double value)	//This function calculates the polynomial expression for each values.
{

	const char str2[] = "+-";								//For find the first '-' or '+'.
	const char str3[] = "x";								//For find the 'x'.
	char new_pol[MAX_SIZE_POL];								//For copying the polynom.
	char * ret, temp1, temp2;							
	char temp3 = '+';										//Some declarations.
	double coef;
	double result = 0.0;
	double valuePow = 1.0;
	int pow, n, i;

	strcpy(new_pol, pol_exp);								//Copying the polynom.
	ret = strpbrk(new_pol, str2); 							//Find the first '+' or '-' character in polynom.

	
	if (*pol_exp == '-')									//Check if start '-'.
	{
		temp3 = '-';
		strcpy(new_pol, ret+1);
		ret = strpbrk(new_pol, str2);
	}
	else if( *pol_exp == '+')								//Check if start '+'.
	{
		strcpy(new_pol, ret+1);
		ret = strpbrk(new_pol, str2);
	}

	n = sscanf(new_pol, "%lf %c %c %d", &coef, &temp1, &temp2, &pow);
	
	if(n == 0)												//If n = 0, so coefficient = 1.		
	{
		coef = 1;
		n = sscanf( new_pol, "%c %c %d", &temp1, &temp2, &pow);	
		
		if(n == 1)											//If n = 1, read 'x'.
		{
			pow = 1;
		}	
		else if(n == 2)										
		{
			ret = strstr(new_pol, str3);					//X's position.
			strcpy(new_pol, ret);							//Copy from.
			n = sscanf(new_pol, "%c %c %d", &temp1, &temp2, &pow);
			
			if(n == 1)										//Only read char, power = 1.
			{
				pow = 1;
			} 
		}
	}
	if (temp2 == '+' || temp2 == '-')						
	{
		pow = 1;
	}	
		

	for (i = 0; i < pow; ++i)
	{
		valuePow *= value;				//Making the exponential transaction.
	}	
		

	if (temp3 == '-')
	{
		result -= coef * valuePow; 		//Addition of single term value.
	}	
	else
	{
		result += coef * valuePow; 		//Addition of single term value.
	}	
		

	while(ret != NULL)
	{
		temp3 = *ret;
		valuePow = 1.0;
		
		strcpy(new_pol, ret+1); 						//Copying from point (ret+1) to new_pol.

		n = sscanf(new_pol, "%lf %c %c %d", &coef, &temp1, &temp2, &pow);
		

		if(n == 0)										//If n = 0, so x's coefficient = 1.
		{
			coef = 1;
			
			n = sscanf(new_pol, "%c %c %d", &temp1, &temp2, &pow);
			
			if(n == 1)									//If n = 1, read 'x'.
			{
				pow=1;
			} 
			else if(n == 2)
			{
				ret = strstr(new_pol, str3);			//X's position.
				
				strcpy(new_pol, ret);					//Copy from.
				
				n = sscanf(new_pol, "%c %c %d", &temp1, &temp2, &pow);
				
				if(n==1)
				{
					pow = 1;	
				} 
			}
		}
		if (temp2 == '+' || temp2 == '-')
		{
			pow = 1;
		}	

		for(i = 0; i < pow; ++i)
		{
			valuePow *= value;							//Making the exponential transaction.
		}	
			

		if (temp3 == '+')
		{
			result += coef * valuePow;					 //Addition of single term value.
		}	
			
		else
		{
			result -= coef * valuePow;					//Addition of single term value.
		}	
			

		ret = strpbrk(new_pol, str2); /* Finding the '+' or '-' character in the new_pol */
	}

	return (result);
}
void removespaces(char* string, int* size)			//This function removes the spaces.
{
	int i;
	
	int j=0;
	
	for(i = 0; string[i] != '\0'; i++)				//Read the string.
	{
		if(string[i] != ' ')						//If spaces.
		{
			string[j++] = string[i];				//Remove.
		}
	}
	string[j] = '\0';
	
	*size = strlen(string);
}