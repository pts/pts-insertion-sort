pts-insertion-sort: insertion sort in C compatible with qsort(3)

pts-insertion-sort implements the insertion_sort(...) function in C with the
same signature as qsort(3). insertion_sort(...) is generally slower for long
inputs (nmemb being high), but its code is shorter.

The implementation uses variable-length arrays, so it needs gcc, or C99 with
support for variable-length arrays.

__END__
