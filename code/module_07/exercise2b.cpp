// C++ Fundamentals: exercise mod07-ex2b

#include <type_traits>

// Exercise: Building on the result of the previous exercise, add a convenience name for
//            the compile-time boolean result of the type trait: 'is_typeA_v'.
//
// Difficulty rating for this exercise: ⭐⭐

template<typename Type>
struct A {};

template<typename Type>
struct B {};

template<typename Type>               // General case.
struct is_typeA : std::false_type {}; // Provides bool 'value'.

// TODO: Add the "positive case" from exercise 2a here..

// TODO: Shorthand result name 'is_typeA_v'..

int main() {
  static_assert(is_typeA_v<A<int>>);   // OK
  static_assert(is_typeA_v<A<float>>); // OK
  static_assert(is_typeA_v<B<int>>);   // FAIL
  static_assert(is_typeA_v<int>);      // FAIL
}

// Compiler Explorer: https://www.godbolt.org/z/qfProadsb
