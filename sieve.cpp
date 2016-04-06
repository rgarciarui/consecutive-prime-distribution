#include <iostream>
#include <bitset>
#include <cassert>
#include <boost/thread.hpp>

// The highest number considered will be 2 * NUM_PRIME_BITS + 1
// The billionth prime number is 29,996,224,275,833
// This is totally impractical :-/
const unsigned int NUM_PRIME_BITS = 2738429;
unsigned int prime_list[379311];

class PrimeBitSet {
private:
  // The highest number in the set
  unsigned int max;

  // This represents odd numbers starting at 3
  std::bitset<NUM_PRIME_BITS> prime_bits;

  // Get index for number n
  unsigned int number_to_index(unsigned int n);

  // Get number for index i
  unsigned int index_to_number(unsigned int i);

public:
  // Initially, set all numbers to prime
  PrimeBitSet();

  // Get value for number n- assumes n is odd!
  bool get_prime(unsigned int n);

  // Set value for number n- assumes n is odd!
  void set_prime(unsigned int n, bool is_prime);

  //  Perform prime sieve
  void sieve();

  // Perform prime sieve up to a maximum factor
  //  void sieve(int max_factor);

  // Get maximum number
  unsigned int get_max();
};  
  

int main() {
  // Do prime sieve up to 5476859
  PrimeBitSet primes;
  primes.sieve();

  // Populate prime list
  unsigned int n = 3;
  int count = 0;
  while (count < 379311) {
    if (primes.get_prime(n)) {
      prime_list[count] = n;
      count ++;
    }
    n += 2;
  }

  assert(prime_list[379310] == 5476859);

  // How many cores does this computer have? split the work between n threads.
  unsigned int n_cores = boost::thread::hardware_concurrency();
  std::cerr << "starting " << n_cores << " threads.\n";

  return 0;
}


PrimeBitSet::PrimeBitSet() {
  max = index_to_number(NUM_PRIME_BITS - 1);
  unsigned int size = prime_bits.size();
  for (unsigned int x = 0; x < prime_bits.size(); x++) {
    prime_bits[x] = true;
  }
}

unsigned int PrimeBitSet::number_to_index(unsigned int n) {
  return (n - 3) / 2;
}

unsigned int PrimeBitSet::index_to_number(unsigned int i) {
  return i * 2 + 3;
}

bool PrimeBitSet::get_prime(unsigned int n) {
  return prime_bits[number_to_index(n)];
}

void PrimeBitSet::set_prime(unsigned int n, bool is_prime) {
  prime_bits[number_to_index(n)] = is_prime;
}

void PrimeBitSet::sieve() {
  // std::cout << "doing sieve\n";
  unsigned int factor = 3;
  while (factor * factor <= max) {
    if (get_prime(factor)) {
      // std::cout << "removing multiples of " << factor << "...\n";
      int index = number_to_index(factor) + factor;
      while (index < NUM_PRIME_BITS) {
	// std::cout << "  removing " << index_to_number(index) << "\n";
	prime_bits[index] = false;
	index += factor;
      }
    }
    factor += 2;
  }
}

unsigned int PrimeBitSet::get_max() {
  return max;
}

/*
unsigned long int is "at least 4 bytes", unsigned long long int is at least 8
choose one with 8 (but not 16!) unsigned long long int to be safe

We need to check all primes up to the billionth prime, 29996224275833
create list of primes up to sqrt(29996224275833) (5476880)
there should be 379312 of them (we only need the 379311 odd ones)
the last prime we'll need is 5476859

Use """
#include <boost/thread.hpp>
unsigned int nthreads = boost::thread::hardware_concurrency();
"""
and make a ton of threads and distribute ranges to test to each

[GCC 5.2.1 20151010] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> from math import sqrt
>>> sqrt(29,996,224,275,833)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: sqrt() takes exactly one argument (5 given)
>>> max = int("29,996,224,275,833".replace(",", ""))
>>> max
29996224275833
>>> sqrt(max)
5476859
5476880.889323138
>>> pi_n = 379312
>>> max_int = 4294967295
>>> from math import log12
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
ImportError: cannot import name log12
>>> from math import log2
Traceback (most recent call last):
File "<stdin>", line 1, in <module>
ImportError: cannot import name log2
>>> from math import log
>>> log(max_int) / log(2)
31.999999999664098
>>> 4 * pi_n / 1000.0
1517.248
>>> 4 * pi_n / 1000.0 / 1000.0
1.5172480000000002
>>> pi_n
379312
>>> max
29996224275833
>>> sqrt(max)
5476880.889323138
>>> from math import floor
>>> floor(_) - 1
5476879.0
>>> int(_)
5476879
>>> (_ + 1.0) / 2 / pi_n
7.219492133125237
>>> log(max) / log(2)
44.769846148878635
>>>
*/
