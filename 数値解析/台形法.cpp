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
  k = 10;
  double n = pow(2, k);
  double x, s1, s2, h;
  double a = 0, b = PI;

  h = (b - a) / n;
  s1 = 0;
  for (i = 1; i < n; i++) {
    x = a + h * i;
    s1 += 2 * func1(x);
  }

  s1 =0.5 * (s1 + func1(a) + func1(b)) * h ;

  s2 = 0;
  for (i = 1; i < n; i++) {
    x = a + h * i;
    s2 += 2 * func2(x);
  }

  s2 = 0.5 * (s2 + func2(a) + func2(b)) * h;

  printf("ANSF%.10f\n", (s1 + 0.5 * s2) * PI);

  return 0;
}
