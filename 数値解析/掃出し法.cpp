#include <stdio.h>

#define N 4

int main(void) {
  double a[N][N + 1] = { {2, 8, 2, -3, 2}, {4, 6, -2, -1, 1}, {2, -4, -2, -1, 3}, {1, -5, 2, 1, -2} }; // 問1
  // double a[N][N + 1] = { {1, 1, 1, 1, 9}, {8, 4, 2, 1, 34}, {27, 9, 3, 1, 85}, {64, 16, 4, 1, 171} }; // 問2
  double pivot, aik;
  int i, j, k;

  for (i = 0; i < N; i++){
    pivot = a[i][i];
    for (j = i; j < N + 1; j++)
      a[i][j] = a[i][j] / pivot;
    for (k = 0; k < N; k++) {
      if ((k - i) != 0) {
        aik = a[k][i];
        for (j = i; j < N + 1; j++)
          a[k][j] = a[k][j] - aik * a[i][j];
      }
    }
  }

  for (i = 0; i < N; i++) {
    printf("x%d = %.6lf\n", i+1, a[i][N]); //問1
    /*
    switch (i){
      case 0:printf("a = %.6lf\n", a[i][N]); break;
      case 1:printf("b = %.6lf\n", a[i][N]); break;
      case 2:printf("c = %.6lf\n", a[i][N]); break;
      case 3:printf("d = %.6lf\n", a[i][N]); break;
    }
    */ // 問2
  }

  return 0;
}
