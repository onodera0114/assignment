#include <stdio.h>

int main(void)
{
	int stu[5];
	int i, sum = 0; /* �ϐ�sum�͍��v�l��\�� */
	double ave = 0; /* �ϐ�ave�͕��ϒl��\�� */

	printf("�_�������\n");

	for (i = 0; i < 5; i++)
	{
		printf("%d�ԁF", i + 1);
		scanf("%d", &stu[i]); /* ���l����� */

		sum += stu[i];
	}

	ave = (double)sum / 5; /* ���ϒl���v�Z */

	printf("���v�_�F%5d\n", sum);
	printf("���ϓ_�F%5.1f\n", ave);

	return 0;
}