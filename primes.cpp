#include <iostream>
#include <sstream>
#include <cassert>

// Return whether a prime number is prime
bool is_prime(unsigned long long int n) {
  unsigned long long int factor = 3;
  while (factor * factor <= n) {
    if (n % factor == 0) return false;
    factor += 2;
  }
  return true;
}


void print_distribution(int prev, unsigned long long int dist[10][10]) {
  std::cout << "for (previous % 10) = " << prev << ":\n";
  std::cout << "  (next % 10) = 1: " << dist[prev][1] << "\n";
  std::cout << "  (next % 10) = 3: " << dist[prev][3] << "\n";
  std::cout << "  (next % 10) = 7: " << dist[prev][7] << "\n";
  std::cout << "  (next % 10) = 9: " << dist[prev][9] << "\n";
  std::cout << std::endl;
}


int main (int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Use: primes <count>\n";
    return 1;
  }

  std::stringstream stream;
  stream << argv[1];
  unsigned long long int target_count;
  stream >> target_count;

  std::cout << "finding distributions of first " << target_count;
  std::cout << " pairs of consecutive primes\n";
  // starting with 7, 11

  // How many consecutive primes end in x and y, respectively?
  // only possible values are 1, 3, 7, 9
  unsigned long long int distributions[10][10];
  for (int x = 1; x < 10; x += 2) {
    for (int y = 1; y < 10; y += 2) {
      distributions[x][y] = 0;
    }
  }

  unsigned long long int previous = 7;
  unsigned long long int candidate = 9;
  unsigned long long int count = 0;

  while (count < target_count) {
    if (is_prime(candidate)) {
      distributions[previous % 10][candidate % 10]++;
      // std::cout << "pair (" << previous << ", " << candidate << ")\n";
      previous = candidate;
      count++;
    }
    candidate += 2;
  }

  print_distribution(1, distributions);
  print_distribution(3, distributions);
  print_distribution(7, distributions);
  print_distribution(9, distributions);
  
  // sanity check
  int total = 0;
  for (int x = 1; x < 10; x += 2) {
    for (int y = 1; y < 10; y+= 2) {
      total += distributions[x][y];
    }
  }
  assert(total == target_count);

  return 0; 
}
