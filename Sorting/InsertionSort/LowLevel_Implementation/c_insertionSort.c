/*
 The MIT License (MIT)

 Copyright (c) 2014 PaulTomchik

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */


# include <stdlib.h>
# include <string.h>
# include "c_insertionSort.h"


void c_insertionSort (void *array, int numElems, size_t elemSize, int (*comparator)(void *elem1, void*elem2))
{
  char *arr, *i, *j;
  void *key;

  if (!(array && numElems && elemSize && comparator)) {
    return;
  }
  
  arr = (char*)array;
  key = malloc(elemSize);

  for (j = (arr + elemSize); j < (arr + numElems*elemSize); j += elemSize) {
    memcpy(key, j, elemSize);
    i = j - elemSize;
    while ((i >= arr) && (comparator(key, i) < 0)) {
      memcpy(i + elemSize, i, elemSize);
      i -= elemSize;
    }  
    memcpy(i + elemSize, key, elemSize);
  }
  free(key);
}
