// C++ Fundamentals: exercise mod03-ex4

#include <iostream>

// Exercise: Consider the 'api' function below. It takes three arguments, it _always_
//            takes three arguments; we cannot leave one argument out.
//
//           The idea of "currying" (a functional programming technique) is that we can
//            turn any function taking multiple arguments into a series of nested
//            functions, all of which only take a single argument ("unary functions").
//
//           For the given function 'api' below this means we can build a curried version
//            'api_curried' that can be used as follows:
//
//             api_curried(17)(42)(56);  // Equal to 'api(17, 42, 56)'.
//
//           The benefit of currying is that we can simply create function "shortcuts"
//            that already fix one or more arguments:
//
//             auto api1 = api_curried(17); // Fixes argument 1.
//             api1(42, 56);                // Equal to 'api(17, 42, 56)'.
//
//             auto api2 = api_curried(17)(42); // Fixes argument 1 and 2.
//             api1(56);                        // Equal to 'api(17, 42, 56)'.
//
//           Implement this curried version of 'api' called 'api_curried'.

void api(int arg1, int arg2, int arg3) {
  std::cout << arg1 << ", " << arg2 << ", " << arg3 << '\n';
}

// TODO: 'api_curried'..

int main() {
  api(17, 42, 56);
}

// Compiler Explorer: https://www.godbolt.org/z/Yfdbev54h
