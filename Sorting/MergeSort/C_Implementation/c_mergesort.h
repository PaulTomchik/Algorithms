# ifndef C_MERGESORT_H
# define C_MERGESORT_H 1

void c_mergesort (void *arr, 
                  size_t numElems, 
                  size_t elemSize, 
                  int (*comparator)(const void*, const void*));

# endif
