#include <stdio.h>
#include <time.h>
#include <stdlib.h> 
#include <stdio.h> 

struct timespec start, end;

void fillData(int *a, int len) 
{ 
    srand(time(0));
    for (int i = 0 ; i < len ; i++) 
    	a[i] = rand()%100;
    
    return; 
}   

void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; 
    j = 0; 
    k = l; 
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
  
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

int* merge_sort(int *arr, int n)
{
    int curr_size, left_start;
    for (curr_size=1; curr_size <=n-1; curr_size = 2*curr_size) 
    { 
        for (left_start=0; left_start<n-1; left_start += 2*curr_size) 
        {
            // int x = left_start + curr_size - 1, y = 
            int mid = (left_start + curr_size - 1 < n-1)?left_start + curr_size - 1: n-1;
            int right_end = (left_start + 2*curr_size - 1 < n-1)?left_start + 2*curr_size - 1: n-1;
            merge(arr, left_start, mid, right_end); 
        } 
    }  
	
    return arr;
}

int main() 
{
    int max = 1000000;
    int *arr;
	arr = malloc(sizeof(int)*max);
    fillData(arr, max);
    
    clock_gettime(CLOCK_MONOTONIC, &start);
    merge_sort(arr, max);
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    double tdiff = (end.tv_sec - start.tv_sec) + 1e-9*(end.tv_nsec - start.tv_nsec);
	printf("%f\n",tdiff);
    return 0;
} 