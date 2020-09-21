#include <stdio.h>

void print_table(void);

void print_table(void)
{
	int i, j;

	for (i = 0; i <= 15; i++)
	{
		printf("%X:", i);
		for (j = 0; j <= 7; j++)
		{
			if ((i + (16 * j) >= 0 && i + (16 * j) <= 31) || i + (16 * j) == 127)
			{
				if (i + (16 * j) == 127)
				{
					printf(" ");
				}
				printf("--");
				if (j == 0)
				{
					printf(" ");
				}
			}
			else
			{
				printf("%2c", i + (16 * j));
				if (j >= 2)
				{
					printf(" ");
				}
			}
		}
		printf("\n");
	}
}


int main(void)
{
	int i;

	for (i = 0; i <= 7; i++)
	{
		printf("%3d", i);
	}
	printf("\n  ");

	for (i = 1; i <= 22; i++)
	{
		printf("-");
	}
	printf("\n");

	print_table();

	return 0;
}
