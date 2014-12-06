# ifndef TESTING_H
# define TESTING_H 1

# include <stdio.h>
# include "primes.h"

# ifdef OUTPUT_STATS
# define OUTPUT_STATS_TEST 1
# else
# define OUTPUT_STATS_TEST 0
# endif

# define stat_printf(fmt, ...) \
              do { if (OUTPUT_STATS_TEST) fprintf(stderr, fmt, ##__VA_ARGS__); } while (0)

# define MAX_M PRIME_NUMS[PRIME_NUMS_LEN -1]

# endif
