#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int saikoro(void);
void print_masu(int x, int *position);
int susumu(int sai, int *position, int mass);

int saikoro() 
{
	int sai, i;

	printf("\nEnterKeyを押すとさいころを振ります。\n");

	for (i = 0; i < 10; i++)
	{
		sai = rand() % 6 + 1;
	}
	getchar();
	return sai;
}

void print_masu(int x, int *position) 
{
	int i;

	printf("START");
	for (i = 1; i <= x; i++) 
	{
		if (i == *position) 
		{
			printf("★ ");
			if (*position == 1 || *position == x - 1)
			{
				printf("｜");
			}
		}
		else {
			if (i == 1 || i == x) 
			{
				printf("　 ");
			}
			else 
			{
				printf("＿ ");
			}

			if (i == 1 || i == x - 1) 
			{
				printf("｜");
			}
		}
	}
	printf("GOAL｜\n");
}

int susumu(int sai, int *position, int mass) 
{
	*position += sai;

	if (*position - mass > 0)
	{
		*position = mass - (*position - mass);
	}
	else if (*position == mass) 
	{
		return 1;
	}

	return 0;

}


int main(void)
{
	int num, position = 1, x = 0, clear = 0;;

	srand((unsigned int)time(NULL));

	printf("マス数を10以上100以下の数で入力してください。：");
	scanf("%d", &num);

	printf("すごろくを開始します\n");
	print_masu(num, &position);
	getchar();

	while (1) {
		x = saikoro();
		clear = susumu(x, &position, num);
		printf("さいころの目は%dです。\n%dマス移動します。\n", x, x);
		print_masu(num, &position);

		if (clear == 1)
		{
			printf("\nゴールしました!!\n");
			break;
		}
	}

}
