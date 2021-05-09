/* 

Muhammet Emrah Küçük

1801042100

CSE_102 HW01


*/

#include<stdio.h>

#define NUMBER_OF_SAMPLE_POINTS 10	//Number of training samples for each class.
#define VERY_SMALL_NUMBER 0.000000000000001	//I defined a macro to reduce the error rate.


int main()
{
	double sum_of_class1_x = 0, sum_of_class1_y = 0, sum_of_class2_x = 0, sum_of_class2_y = 0;
	double av_of_class1_x, av_of_class1_y, av_of_class2_x, av_of_class2_y;	//Average points of each class' coordinates.
	double mid_of_x, mid_of_y;	//Midpoints of the classes.
	double user_x, user_y, slope_of_line;				
	double class1_x, class1_y, class2_x, class2_y;		//Points of Class1 and Class2. 
	int i, j;

	for(i = 0; i < NUMBER_OF_SAMPLE_POINTS; i++)	//Whit this loop i get the points of class1 and.
	{
		scanf("%lf%lf",&class1_x,&class1_y);
		sum_of_class1_x += class1_x;				//I summed up the x coordinates of the points of class1.
		sum_of_class1_y += class1_y;				//I summed up the y coordinates of the points of class1.
	}

	av_of_class1_x = sum_of_class1_x / NUMBER_OF_SAMPLE_POINTS;		//Average of x coordinates of points of class1. 
	av_of_class1_y = sum_of_class1_y / NUMBER_OF_SAMPLE_POINTS;		//Average of y coordinates of points of class1.

	for(j = 0; j < NUMBER_OF_SAMPLE_POINTS; j++)	//Whit this loop i get the points of class1 and.	
	{
		scanf("%lf%lf",&class2_x,&class2_y);
		sum_of_class2_x += class2_x;				//I summed up the x coordinates of the points of class2.
		sum_of_class2_y += class2_y;				//I summed up the y coordinates of the points of class2.

	}

	av_of_class2_x = sum_of_class2_x / NUMBER_OF_SAMPLE_POINTS;		//Average of x coordinates of points of class2.
	av_of_class2_y = sum_of_class2_y / NUMBER_OF_SAMPLE_POINTS;		//Average of y coordinates of points of class2.

	mid_of_x = (av_of_class1_x + av_of_class2_x) / 2;				//I find the middle of x coordinates.
	mid_of_y = (av_of_class1_y + av_of_class2_y) / 2;				//I find the middle of y coordinates.

	if(av_of_class2_y - av_of_class1_y == 0)						//If the result is zero (y2 - y1), the slope cannot be calculated. (Undefine)
	{
		slope_of_line = (-1) / VERY_SMALL_NUMBER;					
	}
	else if(av_of_class2_x - av_of_class1_x == 0)					//If the result is zero (x2 - x1), the slope is 0.
	{
		slope_of_line = 0;
	}
	else															//The slope of the line.
	{
		slope_of_line = (-1) / ( (av_of_class2_y - av_of_class1_y) / (av_of_class2_x - av_of_class1_x) );
	}	


	while( scanf("%lf%lf",&user_x,&user_y) == 2)					//Users test points.
	{
		if( user_y > (slope_of_line) * (user_x - mid_of_x) + mid_of_y)			//I compared the slope line with the point the user entered.
		{
			if(av_of_class1_y > (slope_of_line) * (av_of_class1_x - mid_of_x) + mid_of_y)		//The side from the slope line to class 1.
			{
				printf("class1\n");																		
			}
			else																				//If it does not belong to class 1.
			{
				printf("class2\n");									 
			}	
		}

		else														//The comparison is also valid for x coordinates.
		{
			if(av_of_class1_y < (slope_of_line) * (av_of_class1_x - mid_of_x) + mid_of_y)		//The side from the slope line to class 1.
			{
				printf("class1\n");
			}

			else																				//If it does not belong to class 1.
			{
				printf("class2\n");
			}	
		}	

	}	



	return 0;
}