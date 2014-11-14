# ifndef ARM_INSERTIONSORT_H
# define ARM_INSERTIONSORT_H 1

void arm_insertionSort(void *array, int numElems, size_t elemSize, int (*comparator)(void *elem1, void*elem2));

# endif
