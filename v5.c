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

void fillZero(Matrix *c)
{
    for (int i = 0 ; i < 1000 ; i++) 
        for (int j = 0 ; j < 1000 ; j++) 
            c->matrix[i][j] = 0;
}


Matrix *matrix_multiply(Matrix *a,Matrix *b, int p, int q, int r)
{
    int i, j, k; 
    Matrix *result = malloc(sizeof(Matrix));

    for(int i=0; i < p; i++)
	{
		for(int j=0; j < r; j++)
			result -> matrix[i][j]= 0;
	}

    for(int i = 0; i < q; i++)
    {
        for(int j =0; j < i; j++)
        {
            int x = b->matrix[i][j], y = a->matrix[i][j];
            x = x ^ y;
            y = x ^ y;  
            x = x ^ y;
            b->matrix[i][j] = x;
            a->matrix[i][j] = y;
        }
    }

    for (i = 0; i < p; i++)	
    {
		for (j = 0; j < r; j++) 
        {
            int c1 =0, c2 =0, c3 =0, c4 =0;
			for (k = 0; k < q - 4; k += 4) 
            {
                c1 += (a->matrix[i][k] * b->matrix[j][k]);
				c2 += (a->matrix[i][k] * b->matrix[j][k+1]);
                c3 += (a->matrix[i][k] * b->matrix[j][k+2]);
                c4 += (a->matrix[i][k] * b->matrix[j][k+3]);
			}

            result->matrix[i][j] += c1;
            result->matrix[i][j+1] += c2;
            result->matrix[i][j+2] += c3;
            result->matrix[i][j+3] += c4;

            while(k < q)
            {
                result->matrix[i][j] = result->matrix[i][j] + (a->matrix[i][k] * b->matrix[j][k]);
                k++;
            }		
		}
	}

}

int main() 
{ 

    Matrix *a = malloc(sizeof(Matrix));
    Matrix *b = malloc(sizeof(Matrix));

    for(int i = 0; i < 5; i++)
    {   
        fillData(a);
        fillData(b);
        a -> matrix = {{1, 2}, {3,4}}; 
        b -> matrix = {{2, 3}, {1 ,4}};

        int p = 1000, q = 1000, r = 1000;
        //int p = 2, q = 2, r = 2;

        clock_gettime(CLOCK_MONOTONIC, &start);
        matrix_multiply(a, b, p, q, r);
        clock_gettime(CLOCK_MONOTONIC, &end);

        double tdiff = (end.tv_sec - start.tv_sec) + 1e-9*(end.tv_nsec - start.tv_nsec);
        printf("Time: %f\n",tdiff);
    }

    return 0; 
} 