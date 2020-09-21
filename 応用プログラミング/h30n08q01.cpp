#include <stdio.h>

double area(double upper, double lower, double height)
{
	double s;

	s = (upper + lower) * height / 2; // 台形の面積の計算

	return s;
}

int main(void)
{
	double upper, lower, height; // upperは上底, lowerは下底, heightは高さ

	printf("上底：");
	scanf("%lf", &upper); // upper(上底)を入力
	printf("下底：");
	scanf("%lf", &lower); // lower(下底)を入力
	printf("高さ：");
	scanf("%lf", &height); // height(高さ)を入力

	printf("面積：%f\n", area(upper, lower, height)); // 面積を出力

	return 0;
}