# ifndef INSERTIONSORT_H
# define INSERTIONSORT_H 1

# include <stdlib.h>

void c_insertionSort (void *array, int numElems, size_t elemSize, int (*comparator)(void *elem1, void*elem2));

# endif
