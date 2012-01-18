/*
 * The Miller-Rabin primality test
 *
 * Written by Christian Stigen Larsen, 2012-01-10
 * http://csl.sublevel3.org
 *
 * Distributed under the modified BSD license
 *
 * NOTE:  I implemented this probabilistic algorithm purely as a recreational
 *        challenge.  The code has big room for improvements, but it does work
 *        as advertised.
 */

#include <stdlib.h> // rand
#include <stdint.h> // uint64_t
#include "miller-rabin.h"

/*
 * Which PRNG function to use; libc rand() by default
 */
static int (*rand_func)(void) = rand;

/*
 * Maximum number that rand_func can return.
 */
static int rand_max = RAND_MAX;

/*
 * Fast calculation of `a^x mod n´ by using right-to-left
 * binary modular exponentiation.
 *
 * This algorithm is taken from Bruce Schneier's book
 * APPLIED CRYPTOGRAPHY.
 *
 * See http://en.wikipedia.org/wiki/Modular_exponentiation
 */
static uint64_t pow_mod(uint64_t a, uint64_t x, uint64_t n)
{
  /*
   * Note that this code is sensitive to overflowing for testing
   * of large prime numbers.  The `a*r´ and `a*a´ operations can
   * overflow.  One easy way of solving this is to use 128-bit
   * precision for calculating a*b % n, since the mod operator
   * should always get us back to 64bits again.
   *
   * You can either use GCC's built-in __int128_t or use
   *
   * typedef unsigned int uint128_t __attribute__((mode(TI)));
   *
   * to create a 128-bit datatype.
   */

  uint64_t r=1;

  while ( x ) {
    if ( (x & 1) == 1 )
      //r = (__int128_t)a*r % n; // Slow
      r = a*r % n;

    x >>= 1;
    //a = (__int128_t)a*a % n; // SLow
    a = a*a % n;
  }

  return r;
}

/*
 * Return an integer between a and b.
 *
 * Note that we use rand() here, meaning that all its pathological cases
 * will apply here as well --- i.e., it's slow and not very random --- but
 * should suffice.
 *
 */
static uint64_t rand_between(uint64_t a, uint64_t b)
{
  // Assume rand_func() is 32 bits 
  uint64_t r = (static_cast<uint64_t>(rand_func())<<32) | rand_func();
  return a + (uint64_t)((double)(b-a+1)*r/(UINT64_MAX+1.0));
}

/*
 * The Miller-Rabin probabilistic primality test.
 *
 * Returns true if ``n´´ is PROBABLY prime, false if it's composite.
 * The parameter ``k´´ is the accuracy.
 *
 * The running time should be somewhere around O(k log_3 n).
 *
 */
bool isprime(uint64_t n, int k)
{
  // Must have ODD n greater than THREE
  if ( n==2 || n==3 ) return true;
  if ( n<=1 || !(n & 1) ) return false;

  // Write n-1 as d*2^s by factoring powers of 2 from n-1
  int s = 0;
  for ( uint64_t m = n-1; !(m & 1); ++s, m >>= 1 )
    ; // loop

  uint64_t d = (n-1) / (1<<s);

  for ( int i = 0; i < k; ++i ) {
    uint64_t a = rand_between(2, n-2);
    uint64_t x = pow_mod(a,d,n);

    if ( x == 1 || x == n-1 )
      continue;

    for ( int r = 1; r <= s-1; ++r ) {
      x = pow_mod(x, 2, n);
      if ( x == 1 ) return false;
      if ( x == n - 1 ) goto LOOP;
    }

    return false;
LOOP:
    continue;
  }

  // n is *probably* prime
  return true;
}

/*
 * Set which rand function to use.
 *
 * If passed a NULL parameter, it will revert back to the default libc
 * rand().
 */
void setrand(int (*pf)(void), const int rmax)
{
  if ( pf != NULL ) {
    rand_func = pf;
    rand_max = rmax;
  } else {
    rand_func = rand;
    rand_max = RAND_MAX;
  }
}
