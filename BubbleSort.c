#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

int bubblesort(int x[],int n) {
	int i,nr=0,changes=1,tmp;
	while(changes) {
		#pragma omp parallel private(tmp)
		{
			nr++; changes = 0;
			#pragma omp for reduction(+:changes)
			for(i = 0; i < n - 1; i = i + 2) {
				if(x[i] > x[i+1]) {
					tmp = x[i];
					x[i] = x[i+1];
					x[i+1] = tmp;
					++changes;
				}
			}
			#pragma omp for reduction(+:changes)
			for(i = 1; i < n - 1; i = i + 2) {
				if( x[i] > x[i+1]) {
					tmp = x[i];
					x[i] = x[i+1];
					x[i+1] = tmp;
					++changes;
				}
			}
		}
	}
}

int main() {
	int i, n, *x;
	scanf("%d", &n);
	x = (int*)
	malloc(n * sizeof(int));
	for(i = n; i>=0; i--) {
		x[n-1-i] = (i+1)*10;
		printf("Original Array:\n");
	}
	for(i=0;i<n;i++) {
		printf("%d ",x[i]);
		bubblesort(x,n);
		printf("\nSorted Array:\n");
	}
	for(i=0;i<n;i++) {
		printf("%d ",x[i]);
		printf("\n");
	}
	return 0;
}
