#include <stdio.h>
#include <math.h>

double func(double x, double y) {
  return (3 * y) / (1 + x);
}

int main(void) {
  int a = 0, b = 1, k = 8;
  double h, x, y, k1, k2, k3, k4;
  double n = pow(2, k);
  double y0 = 1;

  h = (b - a) / n;
  x = a;
  y = y0;

  while (x < b) {
    k1 = func(x, y);
    k2 = func(x + h / 2.0, y + k1 * h / 2.0);
    k3 = func(x + h / 2.0, y + k2 * h / 2.0);
    k4 = func(x + h, y + k3 * h);

    y += h * (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6;
    x += h;
  }

  printf("%lf\n", y);

  return 0;
}
