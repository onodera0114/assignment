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

	printf("�f�[�^�̐�����͂��Ă��������B�F");
	scanf("%d", &number);

	data = (int *)calloc(number, sizeof(int));

	for (i = 0; i < number; i++) {
		printf("�f�[�^%d�F", i + 1);
		scanf("%d", &data[i]);
	}

	printf("���͂��ꂽ%d�̕��ϒl��%lf�ł��B\n", number, aveof(data, number));

	free(data);

	return 0;
}
