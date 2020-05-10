#include <stdio.h>
#include <time.h>
#include <stdlib.h> 
#include <stdio.h> 
  
struct timespec start, end;
typedef struct Matrix
{
    int matrix[1000][1000];
}
Matrix;


void fillData(Matrix *a) 
{ 
    srand(time(0));
    for (int i = 0 ; i < 1000; i++) 
        for (int j = 0 ; j < 1000 ; j++) 
            a->matrix[i][j] = rand()%100;
    return; 
}


Matrix *matrix_multiply(Matrix *a,Matrix *b, int p, int q, int r)
{
    Matrix *result = malloc(sizeof(Matrix));
    int i, j, k; 
    int max = q ^ ((q ^ r) & -(q < r));
    
    for(int i = 0; i < max; i++)
    {
        for(int j = 0; j < i; j++)
        {
            b->matrix[i][j] =  b->matrix[i][j] ^ b->matrix[j][i];
            b->matrix[j][i] =  b->matrix[i][j] ^ b->matrix[j][i];
            b->matrix[i][j] =  b->matrix[i][j] ^ b->matrix[j][i];
        }
    }


    for (i = 0; i < p; i++)	
    {
        int *aa = a->matrix[i];
        for (j = 0; j < r; j++) 
        {
            int *bb = b->matrix[j];
            int temp = 0;
			for (k = 0; k < q - 16; k += 16) 
                temp += (*(aa + k)) * (*( bb + k)) + (*(aa + k+1)) * (*( bb + k+1)) + (*(aa + k+2)) * (*( bb + k+2)) + 
                (*(aa + k+3)) * (*( bb + k+3))+ (*(aa + k+ 4 )) * (*( bb + k+ 4 )) + (*(aa + k+ 5 )) * (*( bb + k+ 5 )) + 
                (*(aa + k+ 6 )) * (*( bb + k+ 6 )) + (*(aa + k+ 7 )) * (*( bb + k+ 7 )) + (*(aa + k+ 8 )) * (*( bb + k+ 8 )) + 
                (*(aa + k+ 9 )) * (*( bb + k+ 9 )) + (*(aa + k+ 10 )) * (*( bb + k+ 10 )) + (*(aa + k+ 11 )) * (*( bb + k+ 11 )) + 
                (*(aa + k+ 12 )) * (*( bb + k+ 12 )) + (*(aa + k+ 13 )) * (*( bb + k+ 13 )) + (*(aa + k+ 14 )) * (*( bb + k+ 14 )) + 
                (*(aa + k+ 15 )) * (*( bb + k+ 15 ));
            
                while(k < q)
                {
                    temp += (*(aa + k)) * (*( bb + k));
                    k++;
                }

            result->matrix[i][j] = temp;
		}
	}

    return result;
}

int Test(Matrix *a, Matrix *b, int p, int q, int r, Matrix *d)
{
    int i, j, k, flag = 1; 
    Matrix *result = malloc(sizeof(Matrix));

    for (i = 0; i < p; i++) 
    {
        for (j = 0; j < r; j++) 
        {
            int c = 0;
            for (k = 0; k < q ; k ++) 
               c += (a->matrix[i][k] * b->matrix[j][k]);
            
            if(c != d->matrix[i][j])
                flag = 0;
        }
    }


    return flag;
}

int main() 
{ 

    // Matrix *a = malloc(sizeof(Matrix));
    // Matrix *b = malloc(sizeof(Matrix));

    // for(int i = 0; i < 5; i++)
    // {   
    //     fillData(a);
    //     fillData(b);

    //     int p = 1000, q = 1000, r = 1000;
            

    //     clock_gettime(CLOCK_MONOTONIC, &start);
    //     Matrix *c = matrix_multiply(a, b, p, q, r);
    //     clock_gettime(CLOCK_MONOTONIC, &end);

    //     int flag = Test(a, b, p, q, r, c);

    //     double tdiff = (end.tv_sec - start.tv_sec) + 1e-9*(end.tv_nsec - start.tv_nsec);
       
    //     if(flag == 1)
    //         printf("Time: %f\n",tdiff);
    //     else
    //         printf("Incorrect Multiplication\n");
    // }

    return 0; 
} 