# ifndef MAXSUBARRAY_H
# define MAXSUBARRAY_H 1

# include <stdlib.h>

struct maxSubarrayTuple {
  int *low;
  int *high;
  int sum;
};

struct maxSubarrayTuple maxsubarray_NLgN (int arr[], size_t numElems);
struct maxSubarrayTuple maxsubarray_Linear (int arr[], size_t numElems);

# endif
