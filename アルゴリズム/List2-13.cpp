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

	printf("年：");		scanf("%d", &data.y);
	printf("月：");		scanf("%d", &data.m);
	printf("日：");		scanf("%d", &data.d);

	printf("n日後の日付を求めます。\n");
	printf("日数：");	scanf("%d", &day);

	printf("%d年%d月%d日から%d日後の日数は%d年%d月%d日です。\n", data.y, data.m, data.d, day, after(data, day));
}
