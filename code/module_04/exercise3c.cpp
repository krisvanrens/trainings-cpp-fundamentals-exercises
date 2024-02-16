// C++ Fundamentals: exercise mod04-ex3c

#include <cassert>
#include <format>
#include <iostream>

// Macro definitions (text replacements) used in the 'Noisy' type.
#define LOG std::cout << __PRETTY_FUNCTION__ << '\n';
#define RET return *this;

// Exercise: Move the member variable 'original_', and the corresponding getter
//            member function from class 'Base' to 'Derived'. The end result
//            output should be the same as for the previous exercise. In the
//            implementation of the member functions for the derived class,
//            call the base class implementations instead of reimplementing it.

struct Noisy {
  // clang-format off
  Noisy()                        { LOG }     // Default constructor.
  ~Noisy()                       { LOG }     // Destructor.
  Noisy(const Noisy&)            { LOG }     // Copy constructor.
  Noisy& operator=(const Noisy&) { LOG RET } // Copy assignment operator.
  Noisy(Noisy&&)                 { LOG }     // Move constructor.
  Noisy& operator=(Noisy&&)      { LOG RET } // Move assignment operator.
  // clang-format on
};

class Base {
public:
  Base(int id)
    : id_{id} {
  }

  Base(const Base& other)
    : id_{other.id_ + 1}
    , original_{false} {
  }

  Base& operator=(const Base& other) {
    id_       = other.id_ + 1;
    original_ = false;
    return *this;
  }

  [[nodiscard]] int id() const {
    return id_;
  }

  [[nodiscard]] bool original() const {
    return original_;
  }

private:
  int  id_{-1};
  bool original_{true};
};

class Derived : public Base {
public:
  Derived()
    : Base{-1} {
  }

  Derived(int id)
    : Base{id} {
  }
};

int main() {
  Derived d1{5};   // Calls single-argument constructor.
  Derived d2{d1};  // Calls copy constructor.
  Derived d3 = d2; // Calls copy constructor.
  Derived d4;      // Calls default constructor.
  d4 = d2;         // Calls copy assignment operator.

  const auto print = [](const Derived& d) {
    std::cout << std::format("Derived ID: {} (original? {})\n", d.id(), d.original() ? "yes" : "no");
  };

  print(d1);
  print(d2);
  print(d3);
  print(d4);

  // The following assertions can be enabled to test the end result:
#if 1
  assert(d1.id() == 5);
  assert(d2.id() == 6);
  assert(d3.id() == 7);
  assert(d4.id() == 7);
  assert(d1.original() == true);
  assert(d2.original() == false);
  assert(d3.original() == false);
  assert(d4.original() == false);
#endif
}

// Compiler Explorer: https://www.godbolt.org/z/WsjT6Tfna
