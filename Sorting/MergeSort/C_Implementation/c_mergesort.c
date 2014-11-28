# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "c_mergesort.h"

# define MIN_NUM_ELEMS 2
# define MIN_ELEM_SIZE 1


static void mergesort (char *p, 
                       char *r,
                       size_t elemSize, 
                       int (*comparator)(const void*, const void*));

static void merge (char *p,
                   char *q,
                   char *r,
                   size_t elemSize,
                   int (*comparator)(const void*, const void*));


void c_mergesort (void *arr, 
                  size_t numElems, 
                  size_t elemSize, 
                  int (*comparator)(const void*, const void*)) {

  if ((arr == NULL) || 
      (numElems < MIN_NUM_ELEMS) || 
      (elemSize < MIN_ELEM_SIZE) || 
      (comparator == NULL)) { 
    return; 
  }

  mergesort((char*)arr, (char*)arr + numElems*elemSize, elemSize, comparator);
}



static void mergesort (char *p, 
                       char *r,
                       size_t elemSize, 
                       int (*comparator)(const void*, const void*)) {

  int numElems;
  char *q;

  if ((r-p) < (2*elemSize)) return;
  
  numElems = (r-p)/elemSize;
  numElems /= 2;
  q = p + numElems*elemSize;

  mergesort(p, q, elemSize, comparator);
  mergesort(q, r, elemSize, comparator);

  merge(p, q, r, elemSize, comparator);
}



static void merge (char *p,
                   char *q,
                   char *r,
                   size_t elemSize,
                   int (*comparator)(const void*, const void*)) {

  char *left; 
  char *right;
  char *i, *j, *k;

  if ((left = (char*)malloc(q-p)) == NULL) {
    perror("ERROR: Mergesort; Unable to allocate heap memory for merge step");
    exit(1);
  }

  if ((right = (char*)malloc(r-q)) == NULL) {
    perror("ERROR: Mergesort; Unable to allocate heap memory for merge step");
    exit(1);
  }

  memcpy(left, p, q-p);
  memcpy(right, q, r-q);

  i = left;
  j = right;
  k = p;

  for (; k < r; k += elemSize) {

    /* Only left side has remaining elems. Flush. */
    if ((i-left) == (q-p)) {
      while(k < r) {
        memcpy(k, j, elemSize);
        k += elemSize;
        j += elemSize;
      }
      break;
    }

    /* Only right side has remaining elems. Flush. */
    if ((j-right) == (r-q)) {
      while(k < r) {
        memcpy(k, i, elemSize);
        k += elemSize;
        i += elemSize;
      }
      break;
    }

    if (comparator(i, j) <= 0) {
      memcpy(k, i, elemSize);
      i += elemSize;
    } else {
      memcpy(k, j, elemSize);
      j += elemSize;
    }
  }

  free(left);
  free(right);
}
