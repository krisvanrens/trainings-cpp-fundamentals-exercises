// C++ Fundamentals: exercise mod06-ex1b

#include <fmt/core.h>
#include <iostream>
#include <tl/expected.hpp>

// Exercise: Implement error handling and propagation using the 'tl::expected' type.
//           This type is a preview of the C++23-accepted type 'std::expected' im-
//            plemented for C++11/14/17. It is a header-only library, meaning the only
//            thing that one requires to do is include the library header, that's it.
//
//           Read about 'tl::expected' here:  https://github.com/TartanLlama/expected
//           Read about 'std::expected' here: https://en.cppreference.com/w/cpp/utility/expected

// Global error configuration: set to generate an error on a deep level.
const bool ERROR = true;

[[nodiscard]] static float read_sensor_value(unsigned int id) {
  if (ERROR) {
    // TODO: Error handling..
  }

  return static_cast<float>(id) * 12.23f;
}

class SensorSubsystem {
public:
  SensorSubsystem(unsigned int id)
    : id_{id} {
  }

  void read() {
    value_ = read_sensor_value(id_);
  }

  [[nodiscard]] float value() const {
    return value_;
  }

private:
  unsigned int id_{};
  float        value_{};
};

class System {
public:
  System()
    : sensor1_{1},
      sensor2_{2} {
  }

  void execute() {
    sensor1_.read();
    sensor2_.read();
  }

  void report() const {
    std::cout << fmt::format("Sensor readings: [s1, s2] = [{}, {}]\n",
                             sensor1_.value(), sensor2_.value());
  }

private:
  SensorSubsystem sensor1_;
  SensorSubsystem sensor2_;
};

int main() {
  System s;

  s.execute();
  s.report();
}

// Compiler Explorer: https://www.godbolt.org/z/z7nYnGY63
