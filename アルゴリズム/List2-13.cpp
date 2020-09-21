#include <stdio.h>

typedef struct{
	int y;
	int m;
	int d;
} YMD;

YMD after(YMD x, int n);

int mdays[][12] = {
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

int isleep(int year)
{
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

YMD after(YMD x, int n){
	x.d += n;

	while (1){
		if (x.d <= mdays[isleep(x.y)][x.m - 1])
			break;
		x.d -= mdays[isleep(x.y)][x.m - 1];
		x.m++;
		if (x.m > 12){
			x.m = 1;
			x.y++;
		}
	}

	return x;
}

int main(void){
	int day;
	YMD data;

	printf("�N�F");		scanf("%d", &data.y);
	printf("���F");		scanf("%d", &data.m);
	printf("���F");		scanf("%d", &data.d);

	printf("n����̓��t�����߂܂��B\n");
	printf("�����F");	scanf("%d", &day);

	printf("%d�N%d��%d������%d����̓�����%d�N%d��%d���ł��B\n", data.y, data.m, data.d, day, after(data, day));
}
