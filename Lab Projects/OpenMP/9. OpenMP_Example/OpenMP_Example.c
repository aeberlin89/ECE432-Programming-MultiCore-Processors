#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#if defined(_OPENMP)
	#include<omp.h>
	void sumOfNums(int *sum);
#endif

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int N = 0;
	int global_sum = 0;

	if (argc < 2) {
		N = 1;
	}
	else {
		N = strtol(argv[1], NULL, 10);
	}

	if (N < 0) {
		printf("%d\n", N);
		return 0;
	}

	#if defined(_OPENMP)
		#pragma omp parallel num_threads(N)
		sumOfNums(&global_sum);
		printf("Total sum: %d\n", global_sum);
	#else
		printf("Total sum: %d\n", global_sum + rand() % 10);
	#endif

	return 0;
}

#if defined(_OPENMP)
void sumOfNums(int *sum) {
	int my_rank = omp_get_thread_num();
	int my_number = rand() % 10;
	
	printf("\nThread %d's number: %d\n",my_rank, my_number);

	#pragma omp critical 
	*sum += my_number;
}
#endif
