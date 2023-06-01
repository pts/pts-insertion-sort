/* gcc -W -Wall -Wextra -s -O2 insertion_sort.c && valgrind ./a.out */

/* Same signature as qsort(3), but it implements the slower insertion sort
 * instead in compact code.
 *
 * Worst case number of comparisons and swaps: n*(n-1)/2. Best case is when
 * the input is sorted: n-1 comparisons and 0 swaps.
 *
 * It implements swapping of elements by rotating a sequence of elements to
 * the right by 1 element. It rotates bytewise, so the constant factor is
 * quite slow.
 */
void mini_qsort(void *base, size_t n, size_t size,
                int (*cmp)(const void*, const void*)) {
  char *oldcur, *end, *newcur, *mid, tmp, *cur;
  if (n > 1) {
    for (cur = (char*)base + size, end = (char*)base + (size * n);
         cur != end;
         cur = newcur) {
      newcur = cur + size;
      if (cmp(cur, cur - size) < 0) {
        oldcur = cur;
        do {
          cur -= size;
        } while (cur != (char*)base && cmp(oldcur, cur - size) < 0);
        /* memrotate(cur, oldcur, size); */
        while (oldcur != newcur) {
          mid = oldcur;
          tmp = *mid;
          while (mid != cur) {
            *mid = *(mid - size);
            mid -= size;
          }
          *mid = tmp;
          ++oldcur;
          ++cur;
        }
      }
    }
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
