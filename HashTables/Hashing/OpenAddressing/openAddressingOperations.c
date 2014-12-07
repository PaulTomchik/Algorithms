# include <string.h>
# include <stdio.h>
# include "openAddressingOperations.h"


/* Returns the number of probes as a metric of efficiency. */
long openAddressTable_Insert (OpenAddressTable *oaTable, void *elem) {
 
  long h, i, k, slotKey;
  char *slot;

  /*printf("openAddressTable_Insert(%d)\n", *(int*)elem);*/

  /* Put the elem key into a long variable. */
  k = keyCopy((char*)elem + oaTable->keyOffset, oaTable->keySize);

  for (i = 0; i < oaTable->m; ++i) {

    /* Get the hash for the given key and probe number. */
    h = oaTable->hfunc(k, oaTable->m, i); 
    slot = (char*)(oaTable->table) + (oaTable->elemSize * h);

    slotKey = keyCopy(slot + oaTable->keyOffset, oaTable->keySize);

    /*printf("\th = %ld, slotKey = %ld\n", h, slotKey);*/

    if ((slotKey == oaTable->emptyFlag) || (slotKey == oaTable->deletedFlag)) {
      memcpy(slot, elem, oaTable->elemSize);
      return i;
    }    
  }

  return TABLE_FULL;
}

long openAddressTable_Search (OpenAddressTable *oaTable, void *key) {
  long h, i, k, m, slotKey; 
  char *slot;

  k = keyCopy(key, oaTable->keySize);

  m = oaTable->m;
  for (i = 0; i < m; ++i) {
    h = oaTable->hfunc(k, m, i);

    slot = (char*)(oaTable->table) + (oaTable->elemSize * h);
    slotKey = keyCopy(slot + oaTable->keyOffset, oaTable->keySize);

    if (slotKey == k) {
      return h;
    } else if (slotKey == oaTable->deletedFlag) {
      continue;
    } else if (slotKey == oaTable->emptyFlag) {
      break;
    }
  }

  return NOT_FOUND;
}

void openAddressTable_Delete (OpenAddressTable *oaTable, void *elem) {

  long slotNum;
  void *slot;
  size_t keyOffset = oaTable->keyOffset;

  slotNum = openAddressTable_Search(oaTable, ((char*)elem) + oaTable->keyOffset);
  if(slotNum != NOT_FOUND) {
    slot = (char*)(oaTable->table) + (slotNum * oaTable->elemSize);
    memcpy(slot + keyOffset, &(oaTable->deletedFlag), oaTable->keySize);
  } 
}


/* Endian independent copying of key of size lte sizeof(long) into a long. */
/* http://www.ibm.com/developerworks/aix/library/au-endianc/ */
/* FIXME: Doesn't handle negative values. */
long keyCopy (void *key, int keySize) {

  long keyCopy = 0L;
  signed char *kc = (signed char*)&keyCopy;
  signed char *k  = (signed char*)key;
  int i = 1;
  int offset;

  if (*((char*)&i)) { // Big-Endian System
    for(i=0; i < keySize; ++i) {
      kc[i] |= k[i];
    }
    if (k[i-1] < 0) {
      for (; i < sizeof(long); ++i) {
        kc[i] |= -1;
      }
    }
  } else {
    /* FIXME: Broken!!! */
    while (keySize--) {
      offset = sizeof(long) - keySize;
      printf("--> %d\n", offset);
      kc[offset + keySize] = k[keySize];
    }     
  }
  
  return keyCopy;
}
