/*
 * Example program using the Miller-Rabin GMP package. Finds random prime
 * numbers with a given bit-length.
 */

#include <iostream>
#include "miller-rabin-gmp.h"

static mpz_class find_prime(const size_t bits, const size_t rounds)
{
  const mpz_class lo = mpz_class(1) << (bits - 1);
  const mpz_class hi = (mpz_class(1) << bits) - 1;

  for (;;) {
    mpz_class candidate = randint(lo, hi);

    // Try a few rounds first, to quickly discard obvious non-primes
    if ( prob_prime(candidate, 2) )
      if ( prob_prime(candidate, rounds) )
        return candidate;
  }
}

int main(int, char**)
{
  using namespace std;

  for (size_t bits = 1; ; bits *= 2) {
    const size_t rounds = 1 + bits / 2;

    cout << "Finding " << bits << "-bit prime w/"
      << rounds << " rounds ... " << flush;

    mpz_class n = find_prime(bits, rounds);
    cout << endl << n << endl << endl;
  }

  return 0;
}
