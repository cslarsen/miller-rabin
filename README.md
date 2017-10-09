The Miller-Rabin Primality Test in C++
======================================

The Miller-Rabin primality test is a probabilistic algorithm for determining
if a number is prime or not.

By its probabilistic nature, it runs fast --- in O(k log3 n) time ---
but there is a chance for false positives; it can report that a number is
prime while it is not.  False negatives are impossible, though.  If it
reports a number is composite, it is.  

For this reason, the algorithm comes with an adjustable _accuracy
parameter_.  By increasing the parameter (and running time) slightly, the
chance for false positives drops sharply.

You can read about the algorithm at
http://en.wikipedia.org/wiki/Miller–Rabin_primality_test

The possibility for misreporting a prime but not the opposite classifies
this as a Monte Carlo algorithm,
http://en.wikipedia.org/wiki/Monte_carlo_algorithm

I implemented the algorithm purely as a recreational challenge.  The code has
big room for improvements; however, it *does* work as advertised.

Files
=====

There are two implementations: One using `unit64_t` types (found in
`miller-rabin.cpp`) and another using
the GNU MP (GMP) library (`miller-rabin-gmp.cpp`).

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

You can also build the GNU MP (GMP) version, supporting big numbers. If the GMP
include files are in `/usr/local/include` and the libraries in `/usr/local/lib`
you can compile the example program with

    $ make -e GMPINC=/usr/local/include \
              GMPLIB=/usr/local/lib bigprimes
    $ ./bigprimes
    Finding 1-bit prime w/1 rounds ...
    1
    Finding 2-bit prime w/2 rounds ...
    3
    Finding 4-bit prime w/3 rounds ...
    11
    Finding 8-bit prime w/5 rounds ...
    137
    Finding 16-bit prime w/9 rounds ...
    59707
    Finding 32-bit prime w/17 rounds ...
    3517685341
    Finding 64-bit prime w/33 rounds ...
    10963775045314196617
    Finding 128-bit prime w/65 rounds ...
    281516008729379769704126238773222560103
    Finding 256-bit prime w/129 rounds ...
    83823799349606357369634194201632446089914586233603452883218275356746446559913
    Finding 512-bit prime w/257 rounds ...
    7240331190237823820319390215186659874588737918574865272043872032433513174924669267599284946563548681759025370509798262016670346799806305442183986554372741
    Finding 1024-bit prime w/513 rounds ...
    138179238083818074720044448555132992650161765934795156222794286602893221274723077171464217961999377850103925607996948713103609638309809307108624816571864167852821027111899247719922049974755318665282992573892838728235455927435307715992183111544772068186693041338196216243544761063831025510599991326067090692983
    Finding 2048-bit prime w/1025 rounds ...
    2978052895461772562682212913931739410197439995624951158892016811043903030587924355661276863282533736096289737149662388627537745166195440544466912897556313220419347194176524011749723267282770068934170949124159965049505661318530313348556342723429213374835670603257068856920634761017608748403375333328172899631976538189556947788451439911858504324520988494381022282672680498433010767081226988762744074900994051847163382490925061665351515487492062574533181863442479041980796932196584091527272854548918209222748055626020354762524172975651794543280297251696876357444123642119617178617142617426922276446847128516246374946931

Author and license
------------------

Copyright 2012, 2017 Christian Stigen Larsen

Distributed under the modified BSD license.
