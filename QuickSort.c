#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
int partition(int * a, int p, int r)
{
	int lt[r-p];
	int gt[r-p];
	int i;
	int j;
	int key = a[r];
	int lt_n = 0;
	int gt_n = 0;
	
	#pragma omp parallel for
	for(i = p; i < r; i++) {
		if(a[i] < a[r]) {
			lt[lt_n++] = a[i];
		} else {
			gt[gt_n++] = a[i];
		}
	}
	
	for(i = 0; i < lt_n; i++) {
		a[p + i] = lt[i];
	}
	
	a[p + lt_n] = key;
	for(j = 0; j < gt_n; j++) {
		a[p + lt_n + j + 1] = gt[j];
	}
	return p + lt_n;
}

void quicksort(int * a, int p, int r)
{
	int div;
	if(p < r) {
		div = partition(a, p, r);
		#pragma omp parallel sections
		{
			#pragma omp section
			quicksort(a, p, div - 1);
			#pragma omp section
			quicksort(a, div + 1, r);
		}
	}
}

int main(void) {
	printf("Number of elements = 11\n");
	int a[11] = {5, 3, 8, 4, 0, 9, 2, 1, 7, 6,11};
	printf("Initial Array = \n ");
	for(int i = 0; i < 11; i++) {
		printf("%d ", a[i]);
	}
	int i;
	quicksort(a, 0, 9);
	printf("\nFinal array = \n");
	for(i = 0;i < 11; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}
