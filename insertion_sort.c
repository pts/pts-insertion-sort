/* gcc -W -Wall -Wextra -s -O2 insertion_sort.c && valgrind ./a.out */

#include <string.h>

/* Same signature as qsort(3), but implements the slower insertion sort instead
 * in compact code.
 */
void insertion_sort(void *base, size_t nmemb, size_t size,
                    int (*compar)(const void *, const void *)) {
  char tmp[size];  /* Variable-length array. */
  size_t i, j;
  for (i = 1; i < nmemb; ++i) {
    memcpy(tmp, (char*)base + size * i, size);
    for (j = i; j > 0 && compar(tmp, (char*)base + size * (j - 1)) < 0; --j) {
      memcpy((char*)base + size * j, (char*)base + size * (j - 1), size);
    }
    memcpy((char*)base + size * j, tmp, size);
  }
}

#include <stdio.h>
#include <stdlib.h>

static int short_cmp(const void *a, const void *b) {
  return *(const short*)a - *(const short*)b;
}

int main(int argc, char **argv) {
  short ta[5] = {11, 22, 33, 44, 55};
  short tb[5] = {33, 55, 44, 22, 11};
  size_t i;
  (void)argc; (void)argv;
  insertion_sort(ta, sizeof(ta) / sizeof(ta[0]), sizeof(ta[0]), short_cmp);
  for (i = 0; i < sizeof(ta) / sizeof(ta[0]); ++i) printf(" %d", ta[i]);
  printf("\n");
  insertion_sort(tb, sizeof(tb) / sizeof(tb[0]), sizeof(tb[0]), short_cmp);
  for (i = 0; i < sizeof(tb) / sizeof(tb[0]); ++i) printf(" %d", tb[i]);
  printf("\n");
  return 0;
}
