// C++ Fundamentals: exercise mod04-ex1b

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

// Exercise: 1) Add a class member variable 'id' of type 'unsigned long' to StateMachine.
//           2) The constructor should take an argument that initializes this ID field.
//           3) Extend each message printing statement with the class ID value.
//           4) The function 'state_machine' does not use any class member variables. How
//              can we express in C++ that it is independent of a class instance?
//              Bonus question: can we apply the same to the dispatch map? Why? Or why not?

class StateMachine {
public:
  StateMachine() {
    while (state_now_ != State::Done) {
      state_now_  = state_next_;
      state_next_ = state_machine(state_now_);
      dispatch_map.at(state_now_)();
    }
  }

private:
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

  State state_now_{State::Idle};
  State state_next_{State::Idle};

  // clang-format off
  const std::map<State, std::function<void()>> dispatch_map{
    {State::Idle,       std::bind_front(&StateMachine::state_idle_impl, this)},
    {State::Initialize, std::bind_front(&StateMachine::state_init_impl, this)},
    {State::Receive,    std::bind_front(&StateMachine::state_recv_impl, this)},
    {State::Done,       std::bind_front(&StateMachine::state_done_impl, this)}};
  // clang-format on
};

int main() {
  // StateMachine s1{1};
  // StateMachine s2{2};
}

// Compiler Explorer: https://www.godbolt.org/z/TEGhsYqe9