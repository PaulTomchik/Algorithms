# include <stdio.h>
# include <string.h>
# include <assert.h>
# include "c_mergesort.h"

struct president {
  int id;
  char *lName;
};

typedef void (*Sorter) (void *arr, size_t numElems, size_t elemSize, int (*comparator)(const void*, const void*));

int intComparator(const void *a, const void *b) {
  if (*(int*)a > *(int*)b) return 1;
  if (*(int*)a == *(int*)b) return 0;
  return -1;
}

int presidentIDComparator(const void *a, const void *b) {
  struct president *empA = (struct president*)a;
  struct president *empB = (struct president*)b;

  if (empA->id > empB->id) return 1;
  if (empA->id == empB->id) return 0;
  return -1;
}

int presidentNameComparator(const void *a, const void *b) {
  struct president *empA = (struct president*)a;
  struct president *empB = (struct president*)b;

  return strcmp(empA->lName, empB->lName);
}

void testNullArray (Sorter sorter) {
  sorter(NULL, 1, 1, NULL);
}

void testEmptyArray (Sorter sorter) {
  int i;
  sorter(&i, 0, 4, intComparator);
}

void testPresortedIntArray(Sorter sorter) {
  int arr[] = {0, 1, 2};
  int i;

  sorter(arr, 0, 4, intComparator);
  for (i=1; i<3; ++i) {
    assert(arr[i-1] < arr[i]); 
  }
  sorter(arr, 1, 4, intComparator);
  for (i=1; i<3; ++i) {
    assert(arr[i-1] < arr[i]); 
  }
  sorter(arr, 2, 4, intComparator);
  for (i=1; i<3; ++i) {
    assert(arr[i-1] < arr[i]); 
  }
  sorter(arr, 3, 4, intComparator);
  for (i=1; i<3; ++i) {
    assert(arr[i-1] < arr[i]); 
  }
}

void testUnsortedIntArray(Sorter sorter) {
  int arr[] = {0, 2, 1};
  int i;

  sorter(arr, 0, 4, intComparator);
	assert(arr[0] == 0);

  sorter(arr, 1, 4, intComparator);
	assert(arr[0] == 0);

  sorter(arr, 2, 4, intComparator);
  for (i=1; i<2; ++i) {
    assert(arr[i-1] < arr[i]); 
  }
  sorter(arr, 3, 4, intComparator);
  for (i=1; i<3; ++i) {
    assert(arr[i-1] < arr[i]); 
  }
}

void testReverseSortedIntArray(Sorter sorter) {
  int arr[] = {2, 1, 0};
  int i;

  sorter(arr, 3, 4, intComparator);

  for (i=1; i<3; ++i) {
    assert(arr[i-1] < arr[i]); 
  }
}

void testStructArraySorts(Sorter sorter) {
  struct president presidents[3];

  presidents[0].id = 1;  
  presidents[0].lName = "Washington";
  presidents[1].id = 2;
  presidents[1].lName = "Adams";
  presidents[2].id = 3;
  presidents[2].lName = "Jefferson";
  
  sorter(presidents, 3, sizeof(struct president), presidentNameComparator);

  assert(presidents[0].id == 2);
  assert(presidents[1].id == 3);
  assert(presidents[2].id == 1);

  sorter(presidents, 3, sizeof(struct president), presidentIDComparator);

  assert(presidents[0].id == 1);
  assert(presidents[1].id == 2);
  assert(presidents[2].id == 3);
}

int main (void) {
  testNullArray(c_mergesort);  
  testEmptyArray(c_mergesort);
  testPresortedIntArray(c_mergesort);
  testUnsortedIntArray(c_mergesort);
  testReverseSortedIntArray(c_mergesort);
  testStructArraySorts(c_mergesort);
  return 0;
}
