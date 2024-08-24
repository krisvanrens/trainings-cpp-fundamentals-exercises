// C++ Fundamentals: exercise mod05-ex1b

#include <cmath>
#include <format>
#include <iostream>

// Exercise: Improve the safety of the use of type 'Lut'. Legacy-style function
//            'create_lut' returns a raw pointer to memory that we must destroy manually.
//           Implement a function 'create_lut_safe' that returns a safe object that will
//            automatically destroy underlying memory upon destruction. Assume single
//            ownership of the LUT object. Don't forget to call the visualization.
//
//           For this exercise we are not allowed to change the function prototypes or
//            implementations of the existing functions 'create_lut' or 'visualize_lut'.
//           You are allowed to augment the 'Lut' type.
//
// Difficulty rating for this exercise: ⭐⭐

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

// TODO: Implement 'create_lut_safe'.

int main() {
  // auto lut = create_lut_safe();

  // TODO: Visualize LUT.
}

// Compiler Explorer: https://www.godbolt.org/z/P4hnsboTY
