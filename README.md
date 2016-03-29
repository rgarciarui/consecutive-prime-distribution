Prime last-digit-distribution count
===================================

"Unexpected biases in the distribution of consecutive primes" by Robert J.
Lemke Oliver and Kannan Soundararajan (http://arxiv.org/abs/1603.03720)
suggests that for primes ending in a particular digit n, the distribution of
final digits of the next consecutive primes is biased away from n.

## primes.py
Use: python primes.py <number of primes>
Print nested dictionary- keys of the outer dictionary are the last digit of a
prime, keys of the inner dictionaries are the last digit of the next
consecutive prime.

## primes.cpp
The "all" make target compiles primes.cpp into the application "primes".
Use: ./primes <number of primes>
Prints a more readable distribution of the first number-of-primes primes.
