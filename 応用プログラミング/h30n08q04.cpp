#include <stdio.h>

int min(int a, int b); /* プロトタイプ宣言 */

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
	if (a < b)     /* aの方が小さければaを返す */
		return a;
	else           /* bの方が小さければbを返す */
		return b;
}