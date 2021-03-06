#include <stdio.h>
#include <stdlib.h>

int compar(const int *a, const int *b);
void *binsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

int compar(const int *a, const int *b) {
  if (*a < *b) {
    return -1;
  }
  else if (*a > *b) {
    return 1;
  }
  else {
    return 0;
  }
}



void *binsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
  size_t pl = 0, pr = nmemb - 1;
  size_t pc;

  do {
    pc = (pl + pr) / 2;
    if (compar(key, (int *)((int)base + size * pc)) == -1) {
      pr = pc - 1;
    }
    else if (compar(key, (int *)((int)base + size * pc)) == 1) {
      pl = pc + 1;
    }
    else{
      return &pc;
    }

  } while (pl <= pr);


  return NULL;

}

int main(void) {
  int i, nx, ky;
  int *x;
  int *p;

  printf("要素数：");
  scanf("%d", &nx);

  x = (int*)calloc(nx, sizeof(int));

  printf("x[0]：");
  scanf("%d", &x[0]);

  for (i = 1; i < nx ; i++) {
    do {
      printf("x[%d]：", i);
      scanf("%d", &x[i]);
    } while (x[i] < x[i - 1]);
  }

  printf("探す値：");
  scanf("%d", &ky);

  p = (int *)binsearch(&ky, x, nx, sizeof(int), (int (*)(const void *, const void *))compar);

  if (p == NULL) {
    printf("探索失敗\n");
  }
  else {
    printf("%dはx[%d]にあります。\n", ky, *p);
  }

  free(x);

  return 0;
}

