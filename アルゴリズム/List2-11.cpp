#include <stdio.h>

int mdays[][12] = {
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

int isleep(int year)
{
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

int dayofyear(int y, int m, int d)
{
	while (--m)
	{
		d += mdays[isleep(y)][m - 1];
		printf("%d\n", d);
	}

	return d;
}

int main(void)
{
	int year, month, day;
	int retry;

	do {
		printf("�N:");    scanf("%d", &year);
		printf("��:");    scanf("%d", &month);
		printf("��:");    scanf("%d", &day);

		printf("�N����%d���ڂł��B\n", dayofyear(year, month, day));

		printf("������x���܂����i1�c�͂��^0�c�������j�F");
		scanf("%d", &retry);
	} while (retry == 1);

	return 0;
}
