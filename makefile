all: primes.cpp
	g++ -o primes primes.cpp

.PHONY: clean
clean:
	rm -f primes
