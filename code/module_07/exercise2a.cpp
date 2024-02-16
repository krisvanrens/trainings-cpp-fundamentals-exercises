// C++ Fundamentals: exercise mod07-ex2a

#include <type_traits>

// Exercise: Implement the "positive case" of the custom type trait to validate that a
//            given template type corresponds to type 'A'.

template<typename Type>
struct A {};

template<typename Type>
struct B {};

template<typename Type>               // General case.
struct is_typeA : std::false_type {}; // Provides bool 'value'.

// TODO: Positive case.

int main() {
  static_assert(/* Check: A<int>   */); // OK
  static_assert(/* Check: A<float> */); // OK
  static_assert(/* Check: B<int>   */); // FAIL
  static_assert(/* Check: int      */); // FAIL
}

// Compiler Explorer: https://www.godbolt.org/z/dd8q86zMr
