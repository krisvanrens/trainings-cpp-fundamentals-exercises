// C++ Fundamentals: exercise mod04-ex3b

#include <cassert>
#include <format>
#include <iostream>

// Macro definitions (text replacements) used in the 'Noisy' type.
#define LOG std::cout << __PRETTY_FUNCTION__ << '\n';
#define RET return *this;

// Exercise: Add a boolean field 'original' (plus getter) to the 'Base' class.
//           This field indicates whether or not the class instantiation in
//            question is an "original" (i.e. not copied). Make sure the field
//            value is set correctly (validate using the assertions in 'main').

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
    : id_{other.id_ + 1} {
  }

  Base& operator=(const Base& other) {
    id_ = other.id_ + 1;
    return *this;
  }

  [[nodiscard]] int id() const {
    return id_;
  }

private:
  int id_{-1};
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

  const auto print = [](const Derived& d) { std::cout << std::format("Derived ID: {}\n", d.id()); };

  print(d1);
  print(d2);
  print(d3);
  print(d4);

  // The following assertions can be enabled to test the end result:
#if 0
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

// Compiler Explorer: https://www.godbolt.org/z/5Ynza4zeM
