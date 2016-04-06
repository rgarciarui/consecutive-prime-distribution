all: primes.cpp
	g++ -o primes primes.cpp

sieve: sieve.cpp
	g++ -o sieve sieve.cpp -lboost_thread -lboost_system

.PHONY: clean
clean:
	rm -f primes sieve
