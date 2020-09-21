#include <stdio.h>
#include <stdlib.h>

double aveof(const int a[], int n);

double aveof(const int a[], int n) {
	int i;
	double ave = 0;

	for (i = 0; i < n; i++) {
		ave += a[i];
	}

	return ave / n;
}

int main(void) {
	int number, i;
	int *data;

	printf("データの数を入力してください。：");
	scanf("%d", &number);

	data = (int *)calloc(number, sizeof(int));

	for (i = 0; i < number; i++) {
		printf("データ%d：", i + 1);
		scanf("%d", &data[i]);
	}

	printf("入力された%d個の平均値は%lfです。\n", number, aveof(data, number));

	free(data);

	return 0;
}
