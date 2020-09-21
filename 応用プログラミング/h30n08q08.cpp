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
	case 0: printf("�O�[���o���܂����B\n"); break;
	case 1: printf("���傫���o���܂����B\n"); break;
	case 2: printf("�p�[���o���܂����B\n");break;
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
		printf("0�F�O�[�A 1�F���傫�A 2�F�p�[\n");
		scanf("%d", &x);

		if (x < 0 || x > 2)
		{
			printf("0�`2�ȊO�̐��������͂���܂����B\n");
			continue;
		}

		print_hand(x);

		y = random(0, 2);
		printf("�G��");
		print_hand(y);

		switch (junken(x, y))
		{
		case 0: printf("�A�C�R�ł��B\n\n"); break;
		case 1: printf("�����܂����B\n\n"); break;
		case 2: printf("�����܂����B\n\n"); break;
		}

		printf("������ꍇ��0�A��߂�ꍇ��0�ȊO�̐�������͂��Ă��������F");
		scanf("%d", &i);

		if (i != 0)
		{
			break;
		}

	}
}