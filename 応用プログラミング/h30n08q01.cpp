#include <stdio.h>

double area(double upper, double lower, double height)
{
	double s;

	s = (upper + lower) * height / 2; // ��`�̖ʐς̌v�Z

	return s;
}

int main(void)
{
	double upper, lower, height; // upper�͏��, lower�͉���, height�͍���

	printf("���F");
	scanf("%lf", &upper); // upper(���)�����
	printf("����F");
	scanf("%lf", &lower); // lower(����)�����
	printf("�����F");
	scanf("%lf", &height); // height(����)�����

	printf("�ʐρF%f\n", area(upper, lower, height)); // �ʐς��o��

	return 0;
}