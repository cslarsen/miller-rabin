/*
 * The Miller-Rabin primality test
 *
 * Written by Christian Stigen Larsen, 2012-01-10
 * http://csl.sublevel3.org
 *
 * Distributed under the modified BSD license
 */

/*
 * Accuracy parameter `k´ of the Miller-Rabin algorithm.
 *
 */
static const int DEFAULT_ACCURACY = 4;

/*
 * The Miller-Rabin probabilistic primality test.
 *
 * Returns true if ``n´´ is PROBABLY prime, false if it's composite.
 * The parameter ``k´´ is the accuracy.
 *
 * The running time should be somewhere around O(k log_3 n).
 *
 */
bool isprime(int n, int accuracy = DEFAULT_ACCURACY);
