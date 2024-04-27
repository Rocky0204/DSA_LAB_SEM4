/*
	Course:		CS2024 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab No:		1
	Aim: 		Simple data analysis on a list of non-zero integers. 
	Instructions:
		1.	Read a list of numbers from the terminal and store it in an array.
		2.	You can also read the list by redirecting a file data.txt to the input 
		3.	Complete a set of data analytic tasks on these numbers.
*/

#include <stdio.h>
#define N 100		// The maximum amount of data the program will handle



int main()
{
	int a[N];
	int i, len, temp;

	for(i = 0; i < N; i++)
	{
		scanf("%d", &temp);
		if(temp == 0){
			len = i;
			break;}
		else{
			a[i] = temp;}
	}

	/* Task 1. Modify the loop below to print the numbers in reverse order
	*/
	for(i = 0; i < len; i++)
		printf("%d\n", a[i]);

	/* Task 2. Find some cumulative statistics of the data
		a) 	Average 
		b)	Standard Deviation
		c)	Minimum value
		d) 	Maximum value
	*/

	/* Task 3. Generate a histogram of the data in the following form
		01 - 10 : ####
		11 - 20 : ########
		...
		91 -100 : ##
		
		Here the number of #'s after i-j denote the number of numbers in the
		list which are between i and j (i and j included)
	*/

	/* Task 4. Search type tasks
		a) 	Find the number of times the maximum value repeats in the list
		b)	Find the value which repeats the maximum number of times in the list
			(this is called the mode of the list)
	*/

	/* Task 5. Sorting
		a) Sort the array in the non-decreasing order 
		b) Print the array in sorted order*/

	/* Task 6.  Uniqueness
		a) Create a new array which contains all elements of the first 
				but without any repetition.
		b) Print this array
	*/

	return 0;
}
