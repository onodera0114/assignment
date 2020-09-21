#include <stdio.h>
#include <math.h>

double func(double x, double y) {
  return x * x  - y;
}

int main(void) {
  int a = 0, b = 2.0, eta = 2, k = 8;
  double h, x, y, n = pow(2, k);
  h = (b - a) / n;
  x = a;
  y = eta;

  while (x < b) {
    y += h * func(x, y);
    x += h;
  }

  printf("%lf\n", y);

  return 0;
}
