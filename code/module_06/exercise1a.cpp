// C++ Fundamentals: exercise mod06-ex1a

#include <format>
#include <iostream>

// Exercise: Consider a system setup with two sensors. In the current implementation,
//            there is no way a read error can propagate to the end user, only the sensor
//            read result can propagate. E.g. in case of a read error, the 'report' call
//            does not make much sense in the current form, as the reported data is in-
//            valid.
//
//           Refactor the implementation such that a sensor read error is properly pro-
//            pagated to the end user and can be handled. You are allowed to use any
//            mechanism native to C++ (e.g. error codes, fundamental types, exceptions,
//            etc.).
//
// Difficulty rating for this exercise: ⭐

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

// Compiler Explorer: https://www.godbolt.org/z/WfE5GnxdE
