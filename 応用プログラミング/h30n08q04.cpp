#include <stdio.h>

int min(int a, int b); /* �v���g�^�C�v�錾 */

int main(void)
{
	int a, b, ans = 0;

	scanf("%d %d", &a, &b);

	ans = min(a, b);
	printf("%d\n", ans);

	return 0;
}

int min(int a, int b)
{
	if (a < b)     /* a�̕������������a��Ԃ� */
		return a;
	else           /* b�̕������������b��Ԃ� */
		return b;
}