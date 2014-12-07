# ifndef PROBINGFUNCTIONS_H
# define PROBINFFUNCTIONS_H 1

# include <stdlib.h>
# include "../HashFunctions/hashFunctions.h"

# define NOT_FOUND -1
# define TABLE_FULL -2

/* Max keySize is sizeof(long) */
typedef struct OpenAddressTable {
  void   *table;
  long   m;
  size_t elemSize;
  size_t keySize;
  size_t keyOffset;
  long   emptyFlag;
  long   deletedFlag;
  NumericProbingHashFunction hfunc;
} OpenAddressTable;

long openAddressTable_Insert (OpenAddressTable *table, void *elem);
long openAddressTable_Search (OpenAddressTable *table, void *key);
void openAddressTable_Delete (OpenAddressTable *table, void *elem);

/* Helper function in probingFunctions. Should be static. Here for testing purposes. */
long keyCopy (void *key, int keySize); 

# endif
