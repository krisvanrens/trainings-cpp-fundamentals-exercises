// C++ Fundamentals: exercise mod05-ex2a

#include <cmath>
#include <format>
#include <iostream>

// Exercise: Study the code below. It implements a lookup table (LUT) type, generator and
//            LUT data visualizer. Try to understand how memory is managed.
//
//           Implement function 'main' to allocate a LUT and visualize its data. The com-
//            piler flags are set such that memory address- and leak-sanitizers are built
//            into the output executable. These are mechanisms that can detect memory
//            management errors at runtime (will be displayed in the output). This way
//            your implementation will immediately be tested for validity.

struct Lut {
  static const std::size_t LUT_SIZE = 20;

  float* data = nullptr;
};

Lut* create_lut() {
  Lut* lut = new Lut{};

  lut->data = new float[Lut::LUT_SIZE];

  // Gaussian function with x = 0.0 .. 3.0
  for (std::size_t index{0}; index < Lut::LUT_SIZE; ++index) {
    const float x{3.0f * static_cast<float>(index) / static_cast<float>(Lut::LUT_SIZE)};
    lut->data[index] = std::exp(-1.0f * static_cast<float>(x * x));
  }

  return lut;
}

void visualize_lut(const Lut* const lut) {
  for (std::size_t index{0}; index < Lut::LUT_SIZE; ++index) {
    std::cout << std::format("{}: {:#>{}}\n", index, ':', static_cast<unsigned int>(100.0f * lut->data[index]));
  }
}

int main() {
  // TODO: Create LUT + visualize..
}

// Compiler Explorer: https://www.godbolt.org/z/M9Kv8f8zx
