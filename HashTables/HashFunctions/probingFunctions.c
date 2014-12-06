# include <string.h>
# include "probingFunctions.h"


/*******************************************************
 * Parameters:
 *             table: an array of pointers 
 * ASSUMES:
 *             empty slots contain NULL
 ******************************************************/
long linearProbeInsert (void *table, void *key, long m, HashFunction hashFunc) {
  
  long i, j;
  long h  = hashFunc(key, m);

  for ( i = 0; i < m; ++i ) {
    j = (h + i) % m;
    if ( ((void**)table)[j]== NULL ) {
      return j;
    }
  }

  return -1;
}


/* Works only for fixed size keys. */
long linearProbeSearch_fixedLenKey (void *table, void *key, long m, size_t size, HashFunction hashFunc) {
  
  long i, j;
  long h  = hashFunc(key, m);

  for (i = 0; i < m; ++i) {
    j = (h + i) % m;

    if (((void**)table)[j] == NULL) {
      break;
    }

    if (memcmp(table + j, key, size) == 0 ) {
      return j;
    }
  }

  return -1;
}


/* Works only for string keys. */
long linearProbeSearch_stringKey (void *table, void *key, long m, HashFunction hashFunc) {
  
  long i, j;
  long h  = hashFunc(key, m);

  for (i = 0; i < m; ++i) {
    j = (h + i) % m;

    if (((void**)table)[j] == NULL) {
      break;
    }

    if (strcmp(table + j, key) == 0 ) {
      return j;
    }
  }

  return -1;
}



/*******************************************************
 * Parameters:
 *             table: an array of pointers 
 * ASSUMES:
 *             empty slots contain NULL
 ******************************************************/
long quadraticProbe (void *table, void *key, long m, HashFunction hashFunc) {
  
  return -1;
}
