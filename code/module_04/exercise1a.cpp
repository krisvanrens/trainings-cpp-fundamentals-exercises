// C++ Fundamentals: exercise mod04-ex1a

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

// Exercise: create a class 'StateMachine' that encapsulates all of the machinery of the
//            state machine. Currently all types, functions and variables are global, and
//            the run loop is spelled out in the main function. Move all of this into the
//            StateMachine class. Make everything "private" that can be. The state ma-
//            chine should start and run to completion immediately once it is constructed.
//
// Note: all state machine related functions can be kept intact, they will only be relocated.

// Hint 1: The dispatch map, the associative container that maps a state enumerator to a
//          function, will need some modifications if the functions move into a class
//          type. Use the following notation to change it:
//
//            class MyClass {
//              void func();
//              std::map<..enum_type.., std::function<void()>> mymap = {
//                {..enum_value.., std::bind_front(&MyClass::func, this)},
//                {...}
//              };
//            };
//
// Bonus question: can you reason why this modification is required?

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
  // clang-format off
  const std::map<State, State> next_state{
    {State::Idle,       State::Initialize},
    {State::Initialize, State::Receive},
    {State::Receive,    State::Done},
    {State::Done,       State::Done}};
  // clang-format on

  if (advance()) {
    return next_state.at(s);
  }

  return s;
}

int main() {
  State s{State::Idle}, s_next{State::Idle};

  while (s != State::Done) {
    s      = s_next;
    s_next = state_machine(s);
    dispatch_map.at(s)();
  }

  // StateMachine s; // Will run the state machine at construction.
}

// Compiler Explorer: https://www.godbolt.org/z/T59G7nTjz
