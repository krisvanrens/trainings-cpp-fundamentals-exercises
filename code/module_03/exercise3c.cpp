// C++ Fundamentals: exercise mod03-ex3c

#include <iostream>
#include <random>

// Generates a pseudo-random boolean value to indicate if the state machine may advance.
[[nodiscard]] bool advance() {
  static std::random_device              rd;
  static std::mt19937                    generator(rd());
  static std::uniform_int_distribution<> dist(1, 2);
  return (dist(generator) == 2);
}

// Exercise: split out the state machine mechanics (determining the next state) and the calling
//            of the work functions depending on the state. Make a new function 'dispatch' that,
//            depending on the given state, calls out to the work functions.
//
// Difficulty rating for this exercise: ⭐⭐

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

State state_machine(State s) {
  State result{s};

  switch (s) {
  case State::Idle:
    state_idle_impl();
    if (advance()) {
      result = State::Initialize;
    }
    break;

  case State::Initialize:
    state_init_impl();
    if (advance()) {
      result = State::Receive;
    }
    break;

  case State::Receive:
    state_recv_impl();
    if (advance()) {
      result = State::Done;
    }
    break;

  case State::Done: // Will never be reached.
    break;
  }

  return result;
}

int main() {
  State s{State::Idle};

  while (s != State::Done) {
    s = state_machine(s);
  }

  state_done_impl();
}

// Compiler Explorer: https://www.godbolt.org/z/WcT641397
