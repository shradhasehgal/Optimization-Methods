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

    int max = q ^ ((q ^ r) & -(q < r));
    // int x = p, y = r;
    // int max = x ^ ((x ^ y) & -(x < y));
    //printf("%d\n", max);
    for(int i = 0; i < max; i++)
    {
        for(int j =0; j < i; j++)
        {
            int x = b->matrix[i][j], y = b->matrix[j][i];
            // printf("%d %d\n", x, y);
            x = x ^ y;
            y = x ^ y;  
            x = x ^ y;
            // printf("%d %d\n", x, y);
            b->matrix[i][j] = x;
            b->matrix[j][i] = y;
        }
    }

    //printf("%d %d %d\n", b->matrix[0][0], b->matrix[0][1], b->matrix[0][2]);

    for (i = 0; i < p; i++)	
    {
		for (j = 0; j < r; j++) 
        {
            int c = 0;
			for (k = 0; k < q - 4; k += 4) 
                c += a->matrix[i][k] * b->matrix[j][k] + a->matrix[i][k+1] * b->matrix[j][k+1] + a->matrix[i][k+2] * b->matrix[j][k+2] + a->matrix[i][k+3] * b->matrix[j][k+3];

            while(k < q)
            {
                c += (a->matrix[i][k] * b->matrix[j][k]);
                k++;
            }

            result->matrix[i][j] = c;
		}
	}

    return result;
}

int main() 
{ 

    Matrix *a = malloc(sizeof(Matrix));
    Matrix *b = malloc(sizeof(Matrix));

    for(int i = 0; i < 5; i++)
    {   
        fillData(a);
        fillData(b);

        int p = 1000, q = 1000, r = 1000;
        //int p = 2, q = 3, r = 1;
        // for(int i=0; i<p; i++)
        // {
        //     for(int j=0; j<q; j++)
        //         scanf("%d", &a->matrix[i][j]);
        // }

        // for(int i=0; i<q; i++)
        // {
        //     for(int j=0; j<r; j++)
        //         scanf("%d", &b->matrix[i][j]);
        // }
            

        clock_gettime(CLOCK_MONOTONIC, &start);
        Matrix *c = matrix_multiply(a, b, p, q, r);
        clock_gettime(CLOCK_MONOTONIC, &end);

        // for(int i=0; i<p; i++)
        // {
        //     for(int j=0; j<r; j++)
        //         printf("%d ", c->matrix[i][j]);
        //     printf("\n");
        // }

        double tdiff = (end.tv_sec - start.tv_sec) + 1e-9*(end.tv_nsec - start.tv_nsec);
        printf("Time: %f\n",tdiff);
    }

    return 0; 
} 