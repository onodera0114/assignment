#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int saikoro(void);
void print_masu(int x, int *position);
int susumu(int sai, int *position, int mass);

int saikoro() 
{
	int sai, i;

	printf("\nEnterKey�������Ƃ��������U��܂��B\n");

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
			printf("�� ");
			if (*position == 1 || *position == x - 1)
			{
				printf("�b");
			}
		}
		else {
			if (i == 1 || i == x) 
			{
				printf("�@ ");
			}
			else 
			{
				printf("�Q ");
			}

			if (i == 1 || i == x - 1) 
			{
				printf("�b");
			}
		}
	}
	printf("GOAL�b\n");
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

	printf("�}�X����10�ȏ�100�ȉ��̐��œ��͂��Ă��������B�F");
	scanf("%d", &num);

	printf("�����낭���J�n���܂�\n");
	print_masu(num, &position);
	getchar();

	while (1) {
		x = saikoro();
		clear = susumu(x, &position, num);
		printf("��������̖ڂ�%d�ł��B\n%d�}�X�ړ����܂��B\n", x, x);
		print_masu(num, &position);

		if (clear == 1)
		{
			printf("\n�S�[�����܂���!!\n");
			break;
		}
	}

}
