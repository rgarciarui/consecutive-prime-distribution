all: primes.cpp
	g++ -o primes primes.cpp

sieve: sieve.cpp
	g++ -o sieve sieve.cpp

.PHONY: clean
clean:
	rm -f primes sieve
