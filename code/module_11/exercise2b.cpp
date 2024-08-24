// C++ Fundamentals: exercise mod11-ex2b

#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <tuple>
#include <utility>

// Exercise: Using the memoization solution of exercise 2a, build a class type that is
//            able to wrap function 'func' and creates a callable object implementing
//            memoization.
//
//           Bonus question: Why implement memoization in a wrapping callable type? Can
//                            you think of some pros/cons w.r.t. the wrapping function?
//
// Difficulty rating for this exercise: ⭐⭐⭐

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

// TODO: Implement class 'Memoized'..

static float func(int arg1, int arg2) {
  const float result = static_cast<float>(arg1) / static_cast<float>(arg2);

  std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Artificial delay.

  // std::cout << __PRETTY_FUNCTION__ << ": (" << arg1 << ", " << arg2 << ") -> " << result << '\n';

  return result;
}

int main() {
  const auto values = generate_input_values();

  const auto test = [&values](const auto& function, const std::string& name) {
    std::cout << "\n=== " << name << ":\n";

    AutoTimer t;
    for (const auto& [x, y] : values) {
      function(x, y);
    }
  };

  const Memoized func_memoized{func};

  test(func, "Regular function");
  test(func_memoized, "Memoized function");
}

// Compiler Explorer: https://www.godbolt.org/z/qYdMxKGe6
