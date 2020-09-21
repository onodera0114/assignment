#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random(int min, int max);
int conparison(int *str);
void print(int *str);

int random(int min, int max)
{
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

int comparison(int *str)
{
	int x, i;
	x = 0;

	for (i = 1; i <= 6; i++)
	{
		switch (str[i])
		{
		case 0:
			if (i == 1 || i == 2 || i == 3 || i == 4){
				x++;
			}
			break;
		case 1:
			if (i == 5){
				x++;
			}
			break;
		case 2:
			if (i == 6){
				x++;
			}
			break;
		}
	}

	return x;
}

void print(int *str)
{
	int i;
	for (i = 1; i <= 6; i++)
	{
		str[i] = random(0, 2);

		switch (str[i]){
		case 0: printf("ズン・"); break;
		case 1: printf("ドコ・"); break;
		case 2: printf("キ・ヨ・シ！！"); break;
		}
	}
}

int main(void)
{
	int i, ans, num;
	int str[7];

	srand((unsigned int)time(NULL));

	for (i = 1; i <= 6; i++)
	{
		str[i] = random(0, 2);
	}

	while (1)
	{
		printf("\n");
		print(str);
		ans = comparison(str);

		if (ans == 6)
			break;

		num = random(0, 2);
		for (i = 6; i < 0; i--)
		{
			if (i != 1)
			{
				str[i] = str[i - 1];
			}
			else
			{
				str[i] = num;
			}
		}
	}

	printf("\n");

	return 0;
}