// C++ Fundamentals: exercise mod04-ex1a

#include <cassert>
#include <iostream>

// Macro definitions (text replacements) used in the 'Noisy' type.
#define LOG std::cout << __PRETTY_FUNCTION__ << '\n';
#define RET return *this;

// Exercise: Create two classes 'Base' and 'Derived' where 'Derived' publicly
//            inherits from 'Base'. The base class should have an integer prop-
//            erty 'id' that signifies some kind of...ID. This ID field should
//            be part of the 'Base' class.
//
//           The derived class should have a getter function 'id' to retrieve
//            the ID field value. If a copy is made of any of the classes, the
//            copy result ID should be incremented by one (w.r.t. original one).
//
//           The function 'main' below shows the code that must be able to run,
//            a block of assertions shows the expected results for the IDs.
//           Also, be sure to annotate the comments in the first lines of 'main'.
//
// Difficulty rating for this exercise: ⭐

struct Noisy {
  Noisy()                        { LOG }     // Default constructor.
  ~Noisy()                       { LOG }     // Destructor.
  Noisy(const Noisy&)            { LOG }     // Copy constructor.
  Noisy& operator=(const Noisy&) { LOG RET } // Copy assignment operator.
  Noisy(Noisy&&)                 { LOG }     // Move constructor.
  Noisy& operator=(Noisy&&)      { LOG RET } // Move assignment operator.
};

int main() {
  // Derived d1{5};   // Calls ...
  // Derived d2{d1};  // Calls ...
  // Derived d3 = d2; // Calls ...
  // Derived d4;      // Calls ...
  // d4 = d2;         // Calls ...

  // The following assertions can be enabled to test the end result:
#if 0
  assert(d1.id() == 5);
  assert(d2.id() == 6);
  assert(d3.id() == 7);
  assert(d4.id() == 7);
#endif
}

// Compiler Explorer: https://www.godbolt.org/z/YxfcPGx38
