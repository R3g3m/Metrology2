#include "stdafx.h"
#include "conio.h"
#include "time.h"
#include "stdlib.h"

int matrix[5][5];
int sum[5];

int main()
{
	int i, j, k, temp, s;

	srand(time(0));
	for (int i = 0; i <= 4; i++)
		for (int j = 0; j <= 4; j++)
		{
			matrix[i][j] = rand() % 100;
		}
	printf_s("\nMatrix: \n");
	for (int i = 0; i <= 4; i++)
	{
		for (int j = 0; j <= 4; j++)
			printf_s("%d %c", matrix[i][j], ' ');
		printf_s("\n");
	}

	for (i = 0; i <= 4; i++)
	{
		s = 0;
		for (j = 0; j <= 4; j++)
		{
			s = s + matrix[j][i];
		}
		sum[i] = s;
	}

	printf_s("\nSuma elementov stolbcov: \n");
	for (i = 0; i <= 4; i++)
		printf("%d %c", sum[i], ' ');

	for (i = 1; i < 5; i++)
		for (j = 4; j >= i; j--)
			if (sum[j - 1] > sum[j])
			{
				for (k = 0; k <= 4; k++)
				{
					temp = matrix[k][j - 1];
					matrix[k][j-1] = matrix[k][j];
					matrix[k][j] = temp;
				}
				temp = sum[j - 1];
				sum[j - 1] = sum[j];
				sum[j] = temp;
			}

	printf_s("\nSorted matrix: \n");
	for (int i = 0; i <= 4; i++)
	{
		for (int j = 0; j <= 4; j++)
			printf_s("%d %s", matrix[i][j], " ");
		printf_s("\n");
	}

	_getch();
	return 0;
}
