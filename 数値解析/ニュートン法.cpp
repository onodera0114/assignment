#include <stdio.h>
#include <math.h>

double func(double x) {
  return (x * (x * (2 * x -11)+ 2) + 15);
}
double dfunc(double x) {
  return (6 * x * x - 22 * x + 2);
}

int main(void) {
  int count = 0;
  double x0, x1;
  double fx0, dx0, dx;
  double eps = 100;

  printf("x0：");  scanf("%lf", &x0);

  do {
    fx0 = func(x0);
    dx0 = dfunc(x0);
    x1 = x0 - fx0 / dx0;
    dx = fabs(x1 - x0);
    x0 = x1;

    count++;
  } while (dx > eps);

  printf("ループ回数：%d\n", count);
  printf("解：%lf\n", x0);

  return 0;
}
