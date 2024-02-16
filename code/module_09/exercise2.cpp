// C++ Fundamentals: exercise mod09-ex2

#include <cstdint>
#include <iostream>
#include <string>

// Exercise: Consider this custom type 'Pixel'. It is a very basic representation of a
//            three-channel pixel with a color resolution of eight bits per channel.
//
//           In order to be able to conveniently work with this type, we want to add sup-
//            port for iterating color channels. This means we should be able to do
//            things like: 'for (auto channel : pixel) { /* ... */ }'
//
//           To do this, one must add an iterator type to the Pixel class that complies
//            with the design rules that C++ iteration expects. Implement this iterator
//            type and add the minimal mechanics required to have the example in function
//            main work. Use the internet to find a resource that properly explains how
//            to go about this. NOTE: Don't use std::iterator -- this was deprecated.

struct Pixel {
public:
  Pixel() = default;

  Pixel(uint8_t r, uint8_t g, uint8_t b)
    : channels_{r, g, b} {
  }

private:
  uint8_t channels_[3] = {};
};

int main() {
  Pixel p = {12, 34, 56};

  for (auto c : p) {
    std::cout << std::to_string(c) << '\n';
  }

  // Expected result:
  //   12
  //   34
  //   56
}

// Compiler Explorer: https://www.godbolt.org/z/14e61ozaa
