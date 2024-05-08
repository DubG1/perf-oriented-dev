#include <stdio.h>
#include <stdlib.h>

#define S 2048
#define N S
#define M S
#define K S

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

#define TYPE double
#define MATRIX TYPE **

// A utility function
MATRIX createMatrix(unsigned x, unsigned y)
{
	TYPE *data = malloc(x * y * sizeof(TYPE));

	TYPE **index = malloc(x * sizeof(TYPE *));
	index[0] = data;
	for (unsigned i = 1; i < x; ++i)
	{
		index[i] = &(data[i * y]);
	}
	return index;
}

void freeMatrix(MATRIX matrix)
{
	free(matrix[0]);
	free(matrix);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <block_size>\n", argv[0]);
		return EXIT_FAILURE;
	}
	int block_size = atoi(argv[1]);

	// create the matrices
	MATRIX A = createMatrix(N, M);
	MATRIX B = createMatrix(M, K);
	MATRIX C = createMatrix(N, K);

	// initialize the matrices

	// A contains real values
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			A[i][j] = i * j;
		}
	}

	// B is the identity matrix
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < K; j++)
		{
			B[i][j] = (i == j) ? 1 : 0;
		}
	}

	// conduct multiplication
for (int ii = 0; ii < N; ii += block_size)
{
    for (int jj = 0; jj < K; jj += block_size)
    {
        for (int i = ii; i < MIN(N, ii + block_size); i++)
        {
            for (int j = jj; j < MIN(K, jj + block_size); j++)
            {
                TYPE sum = 0;
                for (int kk = 0; kk < M; kk += block_size)
                {
                    for (int k = kk; k < MIN(M, kk + block_size); k++)
                    {
                        sum += A[i][k] * B[k][j];
                    }
                }
                C[i][j] = sum;
            }
        }
    }
}

	// verify result
	int success = 1;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < MIN(M, K); j++)
		{
			if (A[i][j] != C[i][j])
			{
				success = 0;
			}
		}
		for (int j = MIN(M, K); j < MAX(M, K); j++)
		{
			if (C[i][j] != 0)
			{
				success = 0;
			}
		}
	}

	// print verification result
	printf("Verification: %s\n", (success) ? "OK" : "ERR");

	freeMatrix(A);
	freeMatrix(B);
	freeMatrix(C);

	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
