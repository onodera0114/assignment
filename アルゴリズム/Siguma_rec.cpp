#include <stdio.h>

int siguma_while(int n);
int siguma_do(int n);
int siguma_for(int n);
int siguma_rec(int n);

int siguma_while(int n) {
  int ans = 0;

  while (n > 0) {
    ans += n;
    n--;
  }

  return ans;
}

int siguma_do(int n) {
  int ans = 0;

  do {
    if (n < 0)
      break;
    ans += n;
    n--;
  } while (n > 0);

  return ans;
}

int siguma_for(int n) {
  int i, ans = 0;

  for (i = n; i > 0; i--) {
    ans += i;
  }

  return ans;
}

int siguma_rec(int n) {
  if (n > 0)
    return n + siguma_rec(n - 1);
  else
    return 0;
}

int main(void) {
  int x;

  printf("数値：");
  scanf("%d", &x);

  printf("\n");
  printf("siguma_while　　：%d\n", siguma_while(x));
  printf("siguma_do　 　　：%d\n", siguma_do(x));
  printf("siguma_for　　　：%d\n", siguma_for(x));
  printf("siguma_recursive：%d\n", siguma_rec(x));

  return 0;
}
