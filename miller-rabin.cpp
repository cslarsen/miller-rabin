/*
 * The Miller-Rabin primality test
 *
 * Written on 2012-01-10 by Christian Stigen Larsen
 * http://csl.sublevel3.org
 *
 * Distributed under the modified BSD license
 *
 * NOTE:  I implemented this probabilistic algorithm purely as a recreational
 *        challenge.  The code has big room for improvements, but it does work
 *        as advertised.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

/*
 * Accuracy parameter `k´ of the Miller-Rabin algorithm.
 *
 */
static const int ACCURACY = 4;

/*
 * Calculate `a^x mod n´ without overflowing by using modular
 * exponentiation.
 */
static uint64_t pow_mod(uint64_t a, uint64_t x, uint64_t n)
{
  uint64_t r=1;

  while ( x-- )
    r = a*r % n;

  return r;
}

/*
 * Return an integer between a and b.
 *
 * Note that we use rand() hear, meaning that all its pathological cases
 * will apply here as well --- i.e., it's slow and not very random --- but
 * should suffice.
 *
 */
static int rand_between(int a, int b)
{
  return a + (int)((float)(b-a+1)*rand()/(RAND_MAX+1.0));
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
bool isprime(int n, int k = ACCURACY)
{
  // Must have ODD n greater than THREE
  if ( n==2 || n==3 ) return true;
  if ( n<=1 || !(n & 1) ) return false;

  // Write n-1 as d*2^s by factoring powers of 2 from n-1
  int s = 0;
  for ( int m = n-1; !(m & 1); ++s, m >>= 1 )
    ; // loop

  int d = (n-1) / (1<<s);

  for ( int i = 0; i < k; ++i ) {
    int a = rand_between(2, n-2);
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
 * Return the number of primes less than or equal to n, by virtue of brute
 * force.  There are much faster ways of computing this number, but we'll
 * use it to test the primality function.
 *
 */
int pi(int n)
{
  int r=0, m=2;

  while ( m < n )
    if ( isprime(m++) ) ++r;

  return r;
}

int main()
{
  /*
   * Instead of honoring my own advice over at
   * http://csl.sublevel3.org/c++/#srand_time we'll just go ahead and use
   * the idiomatic form for initializing the seed. (It doesn't really matter
   * in this code).
   */
  srand(time(0));

  printf(
    "Calculating pi(n) by using the Miller-Rabin primality test.\n"
    "\n"
    "While this is a SLOW way of computing pi(n), we use it to test\n"
    "the accuracy parameter `k´.\n"
    "\n"
    "Note that since this is a probabilistic algorithm, each run can\n"
    "produce different results.  That is why you might see incorrect\n"
    "results below, from time to time.\n"
    "\n"
    "Written by Christian Stigen Larsen, http://csl.sublevel3.org\n"
    "\n"
    "For this run, k = %d\n\n", ACCURACY);

  int expected[] = {0, 4, 25, 168, 1229, 9592};

  for ( int n=1, e=0; n<=100000; n*=10, ++e ) {
    int primes = pi(n);
    printf("There are %d primes less than %d", primes, n);

    if ( primes == expected[e] ) printf("\n");
    else printf(" --- FAIL, expecteded %d\n", expected[e]);
  }

  return 0;
}
