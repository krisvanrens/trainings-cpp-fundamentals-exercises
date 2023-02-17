// C++ Fundamentals: exercise mod05-ex2c

#include <cmath>
#include <fmt/core.h>
#include <iostream>
#include <memory>

// Exercise: Building on the previous exercise solution, create a version of function
//            'create_lut_safe' that works safely without a custom destructor for 'Lut'.
//
// Hint: Look at the reference page for std::unique_ptr, we can provide a custom deleter.

struct Lut {
  static const std::size_t LUT_SIZE = 20;

  // NOTE: For this exercise we are not allowed to use the destructor.
  //
  //~Lut() {
  //  delete[] data;
  //}

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
    std::cout << fmt::format("{}: {:#>{}}\n", index, ':', static_cast<unsigned int>(100.0f * lut->data[index]));
  }
}

std::unique_ptr<Lut> create_lut_safe() {
  return std::unique_ptr<Lut>{create_lut()};
}

int main() {
  auto lut = create_lut_safe();

  visualize_lut(lut.get());
}

// Compiler Explorer: https://www.godbolt.org/z/EM3TK8oEd