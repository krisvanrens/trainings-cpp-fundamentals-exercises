// C++ Fundamentals: exercise mod03-ex3a

#include <iostream>
#include <random>

// Generates a pseudo-random boolean value to indicate if the state machine may advance.
[[nodiscard]] bool advance() {
  static std::random_device rd;
  static std::mt19937 generator(rd());
  static std::uniform_int_distribution<> dist(1, 2);
  return (dist(generator) == 2);
}

// Exercise: create one function for each state implementation (doing the printing 'work').

enum class State { Idle, Initialize, Receive, Done };

int main() {
  State s{State::Idle};

  while (s != State::Done) {
    switch (s) {
    case State::Idle:
      std::cout << "Idle\n";
      if (advance()) {
        s = State::Initialize;
      }
      break;

    case State::Initialize:
      std::cout << "Initialize\n";
      if (advance()) {
        s = State::Receive;
      }
      break;

    case State::Receive:
      std::cout << "Receive\n";
      if (advance()) {
        s = State::Done;
      }
      break;

    case State::Done: // Will never be reached.
      break;
    }
  }

  std::cout << "Done\n";
}

// Compiler Explorer: https://www.godbolt.org/z/czrdMz5h5