// C++ Fundamentals: exercise mod11-ex2a

#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <tuple>
#include <utility>

// Exercise: Create a "memoized" version of a given function 'func'. Memoization is a
//            concept from functional programming. The idea is that a function, which
//            simply is considered a mapping of input values to output values, keeps a
//            local cache of previously calculated result values given a set of input
//            arguments. Each call will either be a cache lookup or a result calculation
//            (and a cache augmentation). Memoization can be a simple way to optimize
//            code has most impact on expensive functions called in hot loops, but there
//            are other considerations to be made.
//
//           The exercise setup code provides a set of test data and simple benchmark.
//           Implement a function named 'func_memoized' that wraps 'func' using the prin-
//           ciples of memoization described above.
//
// Difficulty rating for this exercise: ⭐⭐

constexpr unsigned int NUMBER_OF_INPUT_VALUES = 100;

using InputValue  = std::pair<unsigned int, unsigned int>;
using InputValues = std::array<InputValue, NUMBER_OF_INPUT_VALUES>;

class AutoTimer final {
  using Clock = std::chrono::steady_clock;

  Clock::time_point time_start_;
  Clock::time_point time_stop_;

public:
  AutoTimer() noexcept
    : time_start_{Clock::now()} {
  }

  ~AutoTimer() {
    time_stop_ = Clock::now();
    std::cout << "Elapsed time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(time_stop_ - time_start_).count() << " ms\n";
  }
};

// Create input values for testing. This will generate numbers according a normal
//  distribution with a histogram like this (mean: 0, stddev: 2):
//
//   0: *******************
//   1: ***************
//   2: *********
//   3: ****
//   4: *
//   5:
//   ...
//
static InputValues generate_input_values() {
  std::random_device         device;
  std::mt19937               engine{device()};
  std::normal_distribution<> distribution(0, 2);

  InputValues result;
  std::generate_n(result.begin(), result.size(), [&]() -> InputValue {
    return {std::abs(distribution(engine)), std::abs(distribution(engine))};
  });

  return result;
}

static float func(int arg1, int arg2) {
  const float result = static_cast<float>(arg1) / static_cast<float>(arg2);

  std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Artificial delay.

  // std::cout << __PRETTY_FUNCTION__ << ": (" << arg1 << ", " << arg2 << ") -> " << result << '\n';

  return result;
}

// TODO: Implement 'func_memoized'..

int main() {
  const auto values = generate_input_values();

  const auto test = [&values](const auto& function, const std::string& name) {
    std::cout << "\n=== " << name << ":\n";

    AutoTimer t;
    for (const auto& [x, y] : values) {
      function(x, y);
    }
  };

  test(func, "Regular function");
  test(func_memoized, "Memoized function");
}

// Compiler Explorer: https://www.godbolt.org/z/xsnfvrn5G
