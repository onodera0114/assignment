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

	while (1) // �������[�v
	{
		printf("���F");
		scanf("%lf", &upper); // upper(���)�����

		if (upper < 0) // upper�����̐��Ȃ�break
			break;

		printf("����F");
		scanf("%lf", &lower); // lower(����)�����

		if (lower < 0) // lower�����̐��Ȃ�break
			break;

		printf("�����F");
		scanf("%lf", &height); // height(����)�����

		if (height < 0) // height�����̐��Ȃ�break
			break;

		printf("�ʐρF%f\n", area(upper, lower, height)); // �ʐς��o��
	}

	return 0;
}