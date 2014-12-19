# ifndef HASHFUNCTIONS_H
# define HASHFUNCTIONS_H 1

# define callUniversalHashFunction(uhf, key) (uhf.hf(key, uhf.p, uhf.m))

/**********************************************************/
/* Usage:                                                 */
/*       callUniversalHashFunction(UHF, key);             */
/*                                                        */
/**********************************************************/
typedef struct UniversalHashFunction {
  long (*hf)(long, long, long);
  long p;
  long m;
} UniversalHashFunction;

typedef long (*NumericHashFunction) (long key, long m);
typedef long (*NumericProbingHashFunction) (long key, long m, long i);
typedef long (*StringHashFunction)  (const char key[], long m);

long simpleDivisionMethodHash (long key, long m);
long simpleMultiplicationMethodHash(long key, long m);

/*************************************************************/
/*                                                           */
/* NOTE: The probing functions are implemented as follows to */
/*         a) stay true to the crls examples.                */
/*         b) facilitate statistics keeping.                 */
/*                                                           */
/*************************************************************/
long divisionMethodHash_linearProbe (long key, long m, long i);
long multiplicationMethodHash_linearProbe (long key, long m, long i);

long divisionMethodHash_quadraticProbe (long key, long m, long i);
long multiplicationMethodHash_quadraticProbe (long key, long m, long i);

long bigEndianStringHash    (const char key[], long m);
long littleEndianStringHash (const char key[], long m);

UniversalHashFunction newUniversalHashFunction (long m);

# endif
