#include <random>

// Generates a pseudo-random boolean value to indicate if the state machine may advance.
[[nodiscard]] bool advance() {
  static std::random_device rd;
  static std::mt19937 generator(rd());
  static std::uniform_int_distribution<> dist(1, 2);
  return (dist(generator) == 2);
}

// Exercise: implement a state machine..

int main() {
  // ...
}

// Compiler Explorer: https://www.godbolt.org/z/sxa1b8PPe