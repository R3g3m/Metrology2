// ConsoleApplication2.cpp: определ€ет точку входа дл€ консольного приложени€.
//


#include "stdafx.h"
#include "conio.h"
#include "time.h"
#include "stdlib.h"

int main()
{
	int i, j;
	int arr[6][6];

	srand(time(0));
	for (i = 0; i <= 5; i++)
		for (j = 0; j <= 5; j++)
		{
			arr[i][j] = rand() % 100;
		}
	printf_s("\nMatrix: \n");

	for (i = 0; i <= 5; i++)
	{
		for (j = 0; j <= 5; j++)
			printf_s("%d %s", arr[i][j], " ");
		printf_s("\n");
	}

	int sum_main, sum_sec, sum;
	sum = sum_main = sum_sec = 0;

	for (i = 0; i <= 5; i++)
	{
		sum_main = sum_main + arr[i][i];
		sum_sec = sum_sec + arr[i][5 - i];
	}

	sum = sum_main + sum_sec;
	
	printf_s("\nSumma elementov glavnoi i pobochnoi diagonalei: \n %d", sum);
	printf_s("\nSrednee arifmetichescoe elementov glavnoi i pobochnoi diagonalei: \n %d", sum/12);

	srand(time(0));
	for (i = 0; i <= 5; i++)
		for (j = 0; j <= 5; j++)
		{
			arr[i][j] = rand() % 100;
		}
	printf_s("\nMatrix: \n");

	for (i = 0; i <= 5; i++)
	{
		for (j = 0; j <= 5; j++)
			printf_s("%d %s", arr[i][j], " ");
		printf_s("\n");
	}

	int temp, max_j, min_j;
	for (i = 0; i <= 5; i++)
	{
		// поиск индекса максимального элемента строки
		max_j = j;
		for (j = 0; j <= 5; j++)
		{
			if (arr[i][j] > arr[i][max_j])
				max_j = j;	
		}
		// поиск индекса минимального элемента строки
		min_j = j;
		for (j = 0; j <= 5; j++)
		{
			if (arr[i][j] < arr[i][min_j])
				min_j = j;
		}
		// обмен максимального и минимального 
		temp = arr[i][max_j];
		arr[i][max_j] = arr[i][min_j];
		arr[i][min_j] = temp;
	}

	printf_s("\nChanged matrix: \n");

	for (i = 0; i <= 5; i++)
	{
		for (j = 0; j <= 5; j++)
			printf_s("%d %s", arr[i][j], " ");
		printf_s("\n");
	}

	_getch();
	return 0;
}