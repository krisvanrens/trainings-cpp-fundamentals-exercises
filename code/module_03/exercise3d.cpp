// C++ Fundamentals: exercise mod03-ex3d

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

// Exercise: replace the 'dispatch' function with a call to a dispatch map, containing a
//            function object for each state value. Use the 'at' function of the map when
//            calling the function object corresponding to a state.

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

// Fill the constant dispatch map like so:
//
//   ... map{{state_literal1, &function1},
//           {state_literal2, &function2},
//           {...}};
//
const std::map<State, std::function<void()>> dispatch_map{/* ... */};

void dispatch(State s) {
  switch (s) {
  case State::Idle:
    state_idle_impl();
    break;

  case State::Initialize:
    state_init_impl();
    break;

  case State::Receive:
    state_recv_impl();
    break;

  case State::Done:
    state_done_impl();
    break;
  }
}

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
    dispatch(s);
  }
}

// Compiler Explorer: https://www.godbolt.org/z/bxM78Mx8n
