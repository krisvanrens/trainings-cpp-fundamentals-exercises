// C++ Fundamentals: exercise mod06-ex1b

#include <format>
#include <iostream>

// Exercise: Implement error handling and propagation using C++23 'std::expected'.
//
//           Read about 'std::expected' here: https://en.cppreference.com/w/cpp/utility/expected
//
// Difficulty rating for this exercise: ⭐⭐

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
    : sensor1_{1}
    , sensor2_{2} {
  }

  void execute() {
    sensor1_.read();
    sensor2_.read();
  }

  void report() const {
    std::cout << std::format("Sensor readings: [s1, s2] = [{}, {}]\n", sensor1_.value(), sensor2_.value());
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

// Compiler Explorer: https://www.godbolt.org/z/Yfxbns9E7
