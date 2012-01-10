The Miller-Rabin Primality Test
===============================

The Miller-Rabin primality test is a probabilistic algorithm for determining
if a number is prime or not.

By its probabilistic nature, it runs quite fast --- in O(k log3 n) time ---
but there is a chance for false positives; it can report that a number is
prime while it is not.  False negatives are impossible, though.  If it
reports a number is composite, it is.

You can read about the algorithm at
http://en.wikipedia.org/wiki/Miller–Rabin_primality_test

I implemented the algorithm purely as a recreational challenge.  The code has big room for improvements; however, it *does* work
as advertised.

Compiling and testing
---------------------

    $ make clean check

This should produce output like below.

    Calculating pi(n) by using the Miller-Rabin primality test.
    
    While this is a SLOW way of computing pi(n), we use it to test
    the accuracy parameter `k´.
    
    Note that since this is a probabilistic algorithm, each run can
    produce different results.  That is why you might see incorrect
    results below, from time to time.
    
    Written by Christian Stigen Larsen, http://csl.sublevel3.org
    
    For this run, k = 4
    
    There are 0 primes less than 1
    There are 4 primes less than 10
    There are 25 primes less than 100
    There are 168 primes less than 1000
    There are 1229 primes less than 10000
    There are 9592 primes less than 100000

Author
------
Written by Christian Stigen Larsen on 2012-01-10.
For more information about me, see http://csl.sublevel3.org

Distributed under the modified BSD license.
