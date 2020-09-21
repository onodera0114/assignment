#include <stdio.h>
#include <math.h>

double func(double x) {
  return (x * (x * (2 * x - 11) + 2) + 15);
}


int main(void) {
  int count = 0;
  double a, b, c;
  double fa, fb, fc;
  double eps = 0.000001;

  printf("a�F"); scanf("%lf", &a);
  printf("b�F"); scanf("%lf", &b);

  do {
    fa = func(a);
    fb = func(b);
    c = (a * fb - b * fa) / (fb - fa);
    fc = func(c);

    if (fb * fc < 0) a = c;
    else b = c;

    count++;

  } while (fabs(fc) > eps);

  printf("���[�v�񐔁F%d\n", count);
  printf("���F%lf\n", c);

  return 0;
}
