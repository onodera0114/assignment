#include <stdio.h>

int main(void)
{
	int stu[5];
	int i, sum = 0; /* 変数sumは合計値を表す */
	double ave = 0; /* 変数aveは平均値を表す */

	printf("点数を入力\n");

	for (i = 0; i < 5; i++)
	{
		printf("%d番：", i + 1);
		scanf("%d", &stu[i]); /* 数値を入力 */

		sum += stu[i];
	}

	ave = (double)sum / 5; /* 平均値を計算 */

	printf("合計点：%5d\n", sum);
	printf("平均点：%5.1f\n", ave);

	return 0;
}