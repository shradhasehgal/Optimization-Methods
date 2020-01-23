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

int* merge_sort(int *arr, int n)
{
    int curr_size, left_start;
    for (int i = 0; i < n; i += 10) 
    {	
    	int left = i;
		int right = ((i+9) < (n-1)) ? (i+9) : (n-1);
        for (int x = left + 1; x <= right; x++) 
	    { 
	        int temp = arr[x]; 
	        int y = x - 1; 
	        while (arr[y] > temp && y >= left) 
	        { 
	            arr[y+1] = arr[y]; 
	            y--; 
	        } 
	        arr[y+1] = temp; 
	    } 
	}

    for(curr_size = 1; curr_size <= n-1; curr_size = curr_size << 1) 
    { 
        int d  = curr_size << 1;
        for (left_start=0; left_start < n-1; left_start += d) 
        {
            int x = left_start + curr_size - 1, y = left_start + d - 1, z = n -1;
            
            int mid = (x < z)? x: z;
            int right_end = (y < z)? y: z;
            
            int i, j, k;             
            int n1 = mid - left_start + 1; 
            int n2 =  right_end - mid; 
            int L[n1], R[n2]; 
            
            for (i = 0; i < n1; i++) 
                L[i] = arr[left_start + i]; 

            for (j = 0; j < n2; j++) 
                R[j] = arr[mid + 1+ j]; 
        
            i = 0; 
            j = 0; 
            k = left_start; 
            
            while (i < n1 && j < n2) 
            { 
                int cmp = (L[i] <= R[j]);
                int min = R[j] ^ ((R[j] ^ L[i]) & (-cmp));
                arr[k++] = min;
                i += cmp, j += !cmp;
            } 

            while (i < n1) 
                arr[k++] = L[i++]; 
        
            while (j < n2) 
                arr[k++] = R[j++]; 

        } 
    }  
	
    return arr;
}

int main() 
{
    int max = 1000000, flag = 1;
    for(int i=0; i<5; i++)
    {
        int *arr;
        arr = malloc(sizeof(int)*max);
        fillData(arr, max);
        
        clock_gettime(CLOCK_MONOTONIC, &start);
        merge_sort(arr, max);
        clock_gettime(CLOCK_MONOTONIC, &end);
        
        for(int x=0 ; x < max-1 ; x++)
            if(arr[x] > arr[x+1])
                flag = 0;

        if(flag == 1)
        {
            double tdiff = (end.tv_sec - start.tv_sec) + 1e-9*(end.tv_nsec - start.tv_nsec);
            printf("%f\n",tdiff);
        }

        else 
        {
            for(int i=0; i < 10; i++)
                printf("%d ", arr[i]);
            printf("What da\n");
        }
    }
    
    return 0;
} 