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
    int i, j, k; 
    Matrix *result = malloc(sizeof(Matrix));

    int max = q ^ ((q ^ r) & -(q < r));
    
    for(int i = 0; i < max; i++)
    {
        for(int j = 0; j < i; j++)
        {
            int x = b->matrix[i][j], y = b->matrix[j][i];
            x = x ^ y;
            y = x ^ y;
            x = x ^ y;
            b->matrix[i][j] = x;     b->matrix[j][i] = y;

        }
    }


    for (i = 0; i < p; i++)	
    {
        for (j = 0; j < r; j++) 
        {
            int c = 0;
			for (k = 0; k < q - 16; k += 16) 
                c += a->matrix[i][k] * b->matrix[j][k] + a->matrix[i][k+1] * b->matrix[j][k+1] + a->matrix[i][k+2] * b->matrix[j][k+2] + a->matrix[i][k+3] * b->matrix[j][k+3]+ a->matrix[i][k+ 4 ] * b->matrix[j][k+ 4 ] + a->matrix[i][k+ 5 ] * b->matrix[j][k+ 5 ] + a->matrix[i][k+ 6 ] * b->matrix[j][k+ 6 ] + a->matrix[i][k+ 7 ] * b->matrix[j][k+ 7 ] + a->matrix[i][k+ 8 ] * b->matrix[j][k+ 8 ] + a->matrix[i][k+ 9 ] * b->matrix[j][k+ 9 ] + a->matrix[i][k+ 10 ] * b->matrix[j][k+ 10 ] + a->matrix[i][k+ 11 ] * b->matrix[j][k+ 11 ] + a->matrix[i][k+ 12 ] * b->matrix[j][k+ 12 ] + a->matrix[i][k+ 13 ] * b->matrix[j][k+ 13 ] + a->matrix[i][k+ 14 ] * b->matrix[j][k+ 14 ] + a->matrix[i][k+ 15 ] * b->matrix[j][k+ 15 ];
            
            while(k < q)
                c += (a->matrix[i][k] * b->matrix[j][k++]);

            result->matrix[i][j] = c;
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

    Matrix *a = malloc(sizeof(Matrix));
    Matrix *b = malloc(sizeof(Matrix));

    for(int i = 0; i < 5; i++)
    {   
        fillData(a);
        fillData(b);

        int p = 1000, q = 1000, r = 1000;
            

        clock_gettime(CLOCK_MONOTONIC, &start);
        Matrix *c = matrix_multiply(a, b, p, q, r);
        clock_gettime(CLOCK_MONOTONIC, &end);

        int flag = Test(a, b, p, q, r, c);

        double tdiff = (end.tv_sec - start.tv_sec) + 1e-9*(end.tv_nsec - start.tv_nsec);
       
        if(flag == 1)
            printf("Time: %f\n",tdiff);
        else
            printf("Incorrect Multiplication\n");
    }

    return 0; 
} 