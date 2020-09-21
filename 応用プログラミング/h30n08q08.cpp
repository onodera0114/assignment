#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random(int min, int max);
void print_hand(int hand);
int junken(int _myhand, int _enemyhand);

int random(int min, int max)
{
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

void print_hand(int number)
{

	switch (number)
	{
	case 0: printf("グーを出しました。\n"); break;
	case 1: printf("ちょきを出しました。\n"); break;
	case 2: printf("パーを出しました。\n");break;
	}
}

int junken(int _myhand, int _enemyhand)
{
	if (_myhand == _enemyhand)
	{
		return 0;
	}
	else if ((_myhand == 1 && _enemyhand == 2) || (_myhand == 2 && _enemyhand == 0) || (_myhand == 0 && _enemyhand == 1))
	{
		return 1;
	}
	else 
	{
		return 2;
	}
}

int main(void)
{
	int x, y, i;

	srand((unsigned int)time(NULL));

	while (1){
		printf("0：グー、 1：ちょき、 2：パー\n");
		scanf("%d", &x);

		if (x < 0 || x > 2)
		{
			printf("0～2以外の数字が入力されました。\n");
			continue;
		}

		print_hand(x);

		y = random(0, 2);
		printf("敵は");
		print_hand(y);

		switch (junken(x, y))
		{
		case 0: printf("アイコです。\n\n"); break;
		case 1: printf("勝ちました。\n\n"); break;
		case 2: printf("負けました。\n\n"); break;
		}

		printf("続ける場合は0、やめる場合は0以外の数字を入力してください：");
		scanf("%d", &i);

		if (i != 0)
		{
			break;
		}

	}
}