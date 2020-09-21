#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random(int min, int max)
{
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

int main(void)
{
	int i, j, k, num;
	int graph[51] = {0};

	srand((unsigned int)time(NULL));

	for (i = 1; i <= 50; i++)
	{
		num = random(1, 50);
		graph[num]++;
	}

	for (i = 1; i <= 5; i++){
		printf("%2d ` %2d :", (i - 1) * 10 + 1, i * 10);
		for (j = (i - 1) * 10 + 1; j <= i * 10; j++)
		{

			for (k = 1; k <= graph[j]; k++)
			{
				printf("*");
			}
		}
		printf("\n");
	}

	return 0;
}