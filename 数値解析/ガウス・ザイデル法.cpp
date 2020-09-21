#include <stdio.h>
#include <math.h>

#define N 5

int main(void) {
  double a[N][N + 1] = {  {4, -1, 0, 0, -1, 3},
                          {-1, 4, -1, 0, 0, 3},
                          {0, -1, 4, -1, 0, 7},
                          {0, 0, -1, 4, -1, 9},
                          {-1, 0, 0, -1, 4, 8} };
  double x[N], y[N], sum, q;
  double eps = 0.000001;
  int i, j, k;
  int count = 0;

  for (i = 0; i < N; i++)
    x[i] = 1.0;

  for (i = 0; i < N; i++)
    y[i] = x[i];


  for (k = 1; k <= 30; k++){
    count++;
    for (i = 0; i < N; i++){
      sum = 0;
      for (j = 0; j < N; j++)
        if (i != j)
          sum += a[i][j] * x[j];
      x[i] = (a[i][N] - sum) / a[i][i];
    }
    q = 0;
    for (i = 0; i < N; i++){
      q += fabs(x[i] - y[i]);
      y[i] = x[i];
    }
    if (q < eps){
      printf("ループ回数：%d\n", count);
      for (i = 0; i < N; i++)
        printf("x%d = %lf\n", i, x[i]);
      printf("\n");
      break;
    }
    else {
      printf("ループ回数：%d\n", count);
      for (i = 0; i < N; i++)
        printf("x%d = %lf\n", i, x[i]);
      printf("\n");
    }
  }

  if (k > 30) printf("収束しない\n") ;

  return 0;
}
