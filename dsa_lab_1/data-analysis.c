/*
NAME: SWADHA SWAROOP
ROLL: 112201009
	Course:		CS2024 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab No:		1
	Aim: 		Simple data analysis on a list of non-zero integers. 
	Instructions:
		1.	Read a list of numbers from the terminal and store it in an array.
		2.	You can also read the list by redirecting a file data.txt to the input 
		3.	Complete a set of data analytic tasks on these numbers.
*/
#include<math.h>
#include <stdio.h>
#define N 100		// The maximum amount of data the program will handle
void histogram(int x);

void histogram(int x){
	for (int i=0; i<x;i++){
		printf("#");
	}
	printf("\n");
}

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
	// for(i = 0; i < len; i++)
	// 	printf("%d\n", a[i]);

	for(i = len-1; i >=0; i--){
		printf("%d ", a[i]);
	}

	/* Task 2. Find some cumulative statistics of the data
		a) 	Average 
		b)	Standard Deviation
		c)	Minimum value
		d) 	Maximum value
	*/

    float average;
	float sum=0;
	for (int i=0;i<len;i++){
	    sum = sum+a[i];
	}
	average=sum/len;
	printf("Average: %f\n",average);

	int stdsum;
	for (int i=0;i<len;i++){
		stdsum += ((a[i]-average),2);
	}
	float ssqur= sqrt(stdsum/(len-1));
	printf("Standard Deviation: %f\n",ssqur);

	int min=a[0];
	for (int i=1;i<len;i++){
		if (a[i]<min){
			min=a[i];
		}
	}
	printf("Minimum: %d\n",min);

	int max=a[0];
	for (int i=1;i<len;i++){
		if (a[i]>max){
			max=a[i];
		}
	}
	printf("Maximum: %d \n",max);

	/* Task 3. Generate a histogram of the data in the following form
		01 - 10 : ####
		11 - 20 : ########
		...
		91 -100 : ##
		
		Here the number of #'s after i-j denote the number of numbers in the
		list which are between i and j (i and j included)
	*/

    int r[10] ={0,0,0,0,0,0,0,0,0,0};
	for (int i=0;i<len;i++){
		if ((0<=a[i]) && (a[i]<=10)){
			r[0]=r[0]+1;
			}
		else if ((11<=a[i]) && (a[i]<=20)){
			r[1]=r[1]+1;
			}
		else if ((21<=a[i]) && (a[i]<=30)){
			r[2]=r[2]+1;
			}
		else if ((31<=a[i]) && (a[i]<=40)){
			r[3]=r[3]+1;
			}
		else if ((41<=a[i]) && (a[i]<=50)){
			r[4]=r[4]+1;
			}
		else if ((51<=a[i]) && (a[i]<=60)){
			r[5]=r[5]+1;
			}
		else if ((61<=a[i]) && (a[i]<=70)){
			r[6]=r[6]+1;
			}
		else if ((71<=a[i]) && (a[i]<=80)){
			r[7]=r[7]+1;
			}
		else if ((81<=a[i]) && (a[i]<=90)){
			r[8]=r[8]+1;
			}
		else if ((91<=a[i]) && (a[i]<=100)){
			r[9]=r[9]+1;
			}
	    }

    printf("01 - 10:");
	histogram(r[0]);
	printf("11 - 20:");
	histogram(r[1]);
	printf("21 - 30:");
	histogram(r[2]);
	printf("31 - 40:");
	histogram(r[3]);
	printf("41 - 50:");
	histogram(r[4]);
	printf("51 - 60:");
	histogram(r[5]);
	printf("61 - 70:");
	histogram(r[6]);
	printf("71 - 80:");
	histogram(r[7]);
	printf("81 - 90:");
	histogram(r[8]);
	printf("91 - 100:");
	histogram(r[9]);

	/* Task 4. Search type tasks
		a) 	Find the number of times the maximum value repeats in the list
		b)	Find the value which repeats the maximum number of times in the list
			(this is called the mode of the list)
	*/
    int count=0;
	for (int i=0;i<len;i++){
		if (a[i]==max){
			count=count+1;
		}
	}
	printf("Maximum Repeat: %d\n",count);

	int arr[N];
	for (int i=0; i<N; i++){
		arr[i]=0;
	}
	for (int i=0; i<len; i++){
		arr[a[i]]+=1;
	}
	int max=arr[0];
	int k=0;
	for (int i=1;i<len;i++){
		if (arr[i]>max){
			max=arr[i];
			k=i;
		}
	}
	printf("Mode: %d \n",k);

	/* Task 5. Sorting
		a) Sort the array in the non-decreasing order 
		b) Print the array in sorted order*/

		for(int i=0;i<len-1;i++){
			for (int j=1;j<len;j++){
				if (a[i]>a[j]){
					int temp=a[i];
					a[i]=a[j];
					a[j]=temp;
				}
			}
		}
		for (int k=0; k<len;k++){
			printf("%d ",a[k]);
		}

	/* Task 6.  Uniqueness
		a) Create a new array which contains all elements of the first 
				but without any repetition.
		b) Print this array
	*/
    int rep[len];
	int cou=0;
	rep[0]=a[0];
	for(int t=1;t<len;t++){
		if(a[t]!=rep[cou]){
			rep[cou+1]=a[t];
			cou+=1;
		}
	}
	for(int y;y<cou;y++){
		printf("%d ",rep[y]);
	}

	return 0;
}
