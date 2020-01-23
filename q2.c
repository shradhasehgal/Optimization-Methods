#include <stdio.h>
#include <time.h>
#include <stdlib.h> 
#include <stdio.h> 

struct timespec start, end;

void fillData(int a[], int len) 
{ 
    srand(time(0));
    for (int i = 0 ; i < len ; i++) 
    	a[i] = rand()%100;
    
    return; 
} 

void SingleFunction_MergeSort(int arr[], int n) 
{ 
	int curr_size, left_start, right_end, i , j, k, mid, n1, n2;

	for (curr_size = 1; curr_size <= n-1; curr_size = curr_size * 2)  
	{ 
		for (left_start = 0; left_start < n-1; left_start += curr_size * 2) 
		{ 
			mid = ((left_start + curr_size - 1) < ( n-1)) ? (left_start + curr_size - 1) : (n-1);
			right_end = ((left_start + (curr_size * 2) - 1) < (n-1)) ? (left_start + (curr_size * 2) - 1) : (n-1);
			
			i, j, k; 
			n1 = mid - left_start + 1; 
			n2 = right_end - mid; 

			double L[n1], R[n2]; 

			for (i = 0; i < n1; i++) 
				L[i] = arr[left_start + i]; 
			for (j = 0; j < n2; j++) 
				R[j] = arr[mid + 1+ j]; 

			i = 0; 
			j = 0;  
			k = left_start; 
			
			while (i < n1 && j < n2) 
			{ 
				if (L[i] <= R[j]) 
				{ 
					arr[k] = L[i]; 
					i++; 
				} 
				else
				{ 
					arr[k] = R[j]; 
					j++; 
				} 
				k++; 
			} 

			while (i < n1) 
			{ 
				arr[k] = L[i]; 
				i++; 
				k++; 
			} 

			while (j < n2) 
			{ 
				arr[k] = R[j]; 
				j++; 
				k++; 
			} 
		} 
	} 
} 

int main() 
{
	int max = 1000000, tests = 5, flag = 1;
	double Avg_SingleFunc = 0;
	int a[max];

	for(int i = 0 ; i < tests ; i++)
	{	

		fillData(a,max);		
		clock_gettime(CLOCK_MONOTONIC, &start);
		SingleFunction_MergeSort(a, max);
		clock_gettime(CLOCK_MONOTONIC, &end);
		
		double tdiff = (end.tv_sec - start.tv_sec) + 1e-9*(end.tv_nsec - start.tv_nsec);
		
		for(int x=0 ; x < max-1 ; x++)
			if(a[x] > a[x+1])
				flag = 0;
		
		Avg_SingleFunc = tdiff;
        if(flag == 1)
		    printf("\nAverage: function inling, time %f\n", Avg_SingleFunc);
	    else
		    printf("Sort Failed\n");
	}
	
	// Avg_SingleFunc /= tests;

	// if(flag == 1)
	// 	printf("\nAverage: function inling, time %f\n", Avg_SingleFunc);
	// else
	// 	printf("Sort Failed\n");

	return 0;
} 