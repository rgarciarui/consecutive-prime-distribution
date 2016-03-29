from sys import argv

"""
How often does the last digit of a prime number match the last digit of the
next prime number?

checking "Unexpected biases in the distribution of consecutive primes"
http://arxiv.org/abs/1603.03720
"""

def is_prime(n):
    """Is n prime? assumes n is odd"""
    factor = 3
    while factor * factor <= n:
        if n % factor == 0:
            return False
        factor += 2
    return True


def prime_gen(n, start=3):
    """Generate n odd primes starting at 3"""
    count = 0
    candidate = start
    while count < n:
        if is_prime(candidate):
            yield candidate
            count += 1
        candidate += 2


def calculate_distributions(n):
    """Count distribution of final digits of n consecutive primes"""
    last_prime = 7
    distributions = dict((prev, dict((next, 0) for next in [1, 3, 7, 9]))
                         for prev in [1, 3, 7, 9])

    for prime in prime_gen(n, 9):
        distributions[last_prime % 10][prime % 10] += 1
        last_prime = prime

    return distributions


if __name__ == "__main__":
    if len(argv) == 1:
        count = 1000
    count = int(argv[1])
    print calculate_distributions(count)
