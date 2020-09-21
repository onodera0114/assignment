#include <stdio.h>

int main(void) {
  int i, j;
  int n;
  int x[4], y[4];
  double sx1, sx2, sy, sxy;

  sx1 = sx2 = sy = sxy = 0;

  scanf("%d", &n);
  printf("%d組のデータを入力\n", n);

  for (i = 0; i < n; i++)
    scanf("%d %d", &x[i], &y[i]);

  for (i = 0; i < n; i++)
  {
    sx1 += x[i];
    sx2 += x[i] * x[i];
    sy += y[i];
    sxy += x[i] * y[i];
  }
  
  printf("a = %lf, b = %lf\n", (double)((sy * sx2) - (sx1 * sxy)) / (n * sx2 - sx1 * sx1), (double)(n * sxy - (sy * sx1)) / (n * sx2 - sx1 * sx1));


  return 0;
}
