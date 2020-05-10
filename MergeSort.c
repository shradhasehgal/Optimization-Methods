#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void Merge(int *lista, int sizea, int *listb, int sizeb, int *mergedList)
{
    asm("movl (%rdi), %r14d");
    asm("movl (%rdx), %r13d");
    asm("movl $0,%eax");
    asm("movl $0,%ebx");

    asm("loop:");
        asm("cmpl %eax,%esi");
        asm("je loop1");
        asm("cmpl %ebx,%ecx");
        asm("je loop2");
        asm("cmpl %r14d,%r13d");
        asm("jl addb");
        asm("jge adda");
    
    asm("loop1:");
        asm("cmpl %ebx,%ecx");
        asm("je exit");
        asm("movl (%rdx),%r13d");
        asm("movl %r13d,(%r8)");
        asm("addq $4,%rdx");
        asm("addq $4,%r8");
        asm("addl $1,%ebx");
        asm("jmp loop1");

    asm("loop2:");
        asm("cmpl %eax,%esi");
        asm("je exit");
        asm("movl (%rdi),%r14d");
        asm("movl %r14d,(%r8)");
        asm("addq $4,%r8");
        asm("addq $4,%rdi");
        asm("addl $1,%eax");
        asm("jmp loop2");

    asm("adda:");
        asm("movl %r14d,(%r8)");
        asm("addq $4,%rdi");
        asm("addq $4,%r8");
        asm("movl (%rdi),%r14d");
        asm("addl $1, %eax");
        asm("jmp loop");

    asm("addb:");
        asm("movl %r13d,(%r8)");
        asm("addq $4,%rdx");
        asm("addq $4,%r8");
        asm("movl (%rdx),%r13d");
        asm("addl $1,%ebx");
        asm("jmp loop");
    asm("exit:");
}

int *merge_sort(int *arr, int n)
{
	int curr_size, left_start, right_end, i, j, k, mid, n1, n2, block = 32;

	for (i = 0; i < n; i += block)
	{
		int left = i;
		int right = ((i + block - 1) < (n - 1)) ? (i + block - 1) : (n - 1);
		for (int x = left + 1; x <= right; x++)
		{
			int temp = arr[x];
			int y = x - 1;
			while (arr[y] > temp && y >= left)
			{
				arr[y + 1] = arr[y];
				y--;
			}
			arr[y + 1] = temp;
		}
	}

	for (curr_size = block; curr_size <= n - 1; curr_size = curr_size << 1)
	{
		int d = curr_size << 1;
		for (left_start = 0; left_start < n - 1; left_start += d)
		{
			int x = left_start + curr_size - 1, y = left_start + d - 1, z = n - 1;

			int mid = (x < z) ? x : z;
			int right_end = (y < z) ? y : z;

			n1 = mid - left_start + 1;
			n2 = right_end - mid;

			int *L = (int *)malloc(n1 * 4);
			int *R = (int *)malloc(n2 * 4);

			memcpy(L, &arr[left_start], (n1 * 4));
			memcpy(R, &arr[mid + 1], (n2 * 4));

			Merge(L, n1, R, n2, arr + left_start);

		}
	}
	return arr;
}

int main()
{
	return 0;
}