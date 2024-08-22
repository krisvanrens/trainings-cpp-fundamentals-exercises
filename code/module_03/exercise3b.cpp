// C++ Fundamentals: exercise mod03-ex3b

#include <iostream>
#include <random>

// Generates a pseudo-random boolean value to indicate if the state machine may advance.
[[nodiscard]] bool advance() {
  static std::random_device              rd;
  static std::mt19937                    generator(rd());
  static std::uniform_int_distribution<> dist(1, 2);
  return (dist(generator) == 2);
}

// Exercise: create a function 'state_machine' that holds the switch statement from the 'main'
//            function. The idea is that after the refactoring, the while-loop in 'main' will
//            call out to `state_machine` to determine the next state ('main' will be shorter).
//
// Difficulty rating for this exercise: ⭐

enum class State { Idle, Initialize, Receive, Done };

void state_idle_impl() {
  std::cout << "Idle\n";
}

void state_init_impl() {
  std::cout << "Initialize\n";
}

void state_recv_impl() {
  std::cout << "Receive\n";
}

void state_done_impl() {
  std::cout << "Done\n";
}

int main() {
  State s{State::Idle};

  while (s != State::Done) {
    switch (s) {
    case State::Idle:
      state_idle_impl();
      if (advance()) {
        s = State::Initialize;
      }
      break;

    case State::Initialize:
      state_init_impl();
      if (advance()) {
        s = State::Receive;
      }
      break;

    case State::Receive:
      state_recv_impl();
      if (advance()) {
        s = State::Done;
      }
      break;

    case State::Done: // Will never be reached.
      break;
    }
  }

  state_done_impl();
}

// Compiler Explorer: https://www.godbolt.org/z/hW65acPEx
