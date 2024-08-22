// C++ Fundamentals: exercise mod03-ex3e

#include <functional>
#include <iostream>
#include <map>
#include <random>

// Generates a pseudo-random boolean value to indicate if the state machine may advance.
[[nodiscard]] bool advance() {
  static std::random_device              rd;
  static std::mt19937                    generator(rd());
  static std::uniform_int_distribution<> dist(1, 2);
  return (dist(generator) == 2);
}

// Exercise: in the same vein as exercise 2d, we can replace the switch statement in the
//            'state_machine' function with the use of an associative map.
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

// clang-format off
const std::map<State, std::function<void()>> dispatch_map{
  {State::Idle,       &state_idle_impl},
  {State::Initialize, &state_init_impl},
  {State::Receive,    &state_recv_impl},
  {State::Done,       &state_done_impl}};
// clang-format on

State state_machine(State s) {
  switch (s) {
  case State::Idle:
    if (advance()) {
      return State::Initialize;
    } else {
      return State::Idle;
    }

  case State::Initialize:
    if (advance()) {
      return State::Receive;
    } else {
      return State::Initialize;
    }

  case State::Receive:
    if (advance()) {
      return State::Done;
    } else {
      return State::Receive;
    }

  default:
  case State::Done:
    return State::Done;
  }
}

int main() {
  State s{State::Idle}, s_next{State::Idle};

  while (s != State::Done) {
    s      = s_next;
    s_next = state_machine(s);
    dispatch_map.at(s)();
  }
}

// Compiler Explorer: https://www.godbolt.org/z/qY4T7Mf6E
