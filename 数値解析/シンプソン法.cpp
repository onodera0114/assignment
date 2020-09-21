#include <stdio.h>
#include <math.h>

#define PI 3.14159265359

double func1(double x) {
  return ((-2 / PI) * (-0.1 * cos(x) - 0.087));
}

double func2(double x) {
  return ((-4 / PI) * (-0.1 * cos(x) - 0.087) * cos(x));
}

int main(void) {
  int i, k;
  k = -4;
  double n = pow(2, k);
  double x, s1, s2, s11, s12, s21, s22, h;
  double a = 0, b = PI;

  h = (b - a) / (2 * n);
  s11 = 0;
  s21 = 0;

  for (i = 1; i <= 2 * n - 1; i += 2) {
    x = a + h * i;
    s11 += 4 * func1(x);
    s21 += 4 * func2(x);
  }
  s12 = 0;
  s22 = 0;

  for (i = 2; i <= 2 * n - 2; i += 2) {
    x = a + h * i;
    s12 += 2 * func1(x);
    s22 += 2 * func2(x);
  }
  s1 = (s11 + s12 + func1(a) + func1(b)) * h / 3;
  s2 = (s21 + s22 + func2(a) + func2(b)) * h / 3;

  printf("ANSF%.10f\n", (s1 + 0.5 * s2) * PI);

  return 0;
}
