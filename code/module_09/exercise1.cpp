// C++ Fundamentals: exercise mod09-ex1

#include <iostream>
#include <source_location>
#include <tuple>
#include <vector>

enum class EventType { Error, Info };

struct Event {
  unsigned long id{};
  EventType     type{EventType::Info};
  std::string   message;

  [[nodiscard]] bool operator==(const Event& other) const noexcept {
    return std::tie(type, message) == std::tie(other.type, other.message);
  }

  [[nodiscard]] bool operator!=(const Event& other) const noexcept {
    return !operator==(other);
  }

  [[nodiscard]] bool operator<(const Event& other) const noexcept {
    return std::tie(type, message) < std::tie(other.type, other.message);
  }

  auto operator<=>(const Event&) const = default;
};

using Events = std::vector<Event>;

std::ostream& operator<<(std::ostream& os, const Event& e) {
  const auto type_str = e.type == EventType::Error ? "Error" : "Info";
  os << "[" << e.id << ", " << type_str << ", " << e.message << "]";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Events& e) {
  for (const auto& event : e) {
    os << event << '\n';
  }
  return os;
}

// Exercise: A) Use function 'process_A' to hand-write an algorithm that, in order:
//                1. Filters out (i.e. extracts) errors from the event log.
//                2. Filters out (i.e. extracts) sensor errors with 'id' >= 5.
//                3. Removes events with duplicate messages.
//              Use no standard library algorithms for implementation of this step.
//
//              Difficulty rating for this exercise step: ⭐⭐
//
//           B) Reimplement the algorithm of step A using "classic" (non-ranges) algo-
//               rithms from the standard library. Aim for conciseness and readability.
//
//              Difficulty rating for this exercise step: ⭐⭐
//
//           C) Reimplement the algorithm of step B using "constrained" (range-based)
//               algorithms from the standard library.
//
//              Difficulty rating for this exercise step: ⭐⭐
//
//           D) (BONUS!) Reimplement the algorithm of step C using the Ranges library,
//               either from the C++23 standard library or using the Range-v3 library.
//
//              Difficulty rating for this exercise step: ⭐⭐⭐

// A) The hand-written approach:
void process_A(const Events& events) {
  std::cout << std::source_location::current().function_name() << " result:\n";

  // TODO
}

// B) The classic standard library algorithm approach:
void process_B(const Events& events) {
  std::cout << std::source_location::current().function_name() << " result:\n";

  // TODO
}

// C) The standard library "constrained" algorithm approach:
void process_C(const Events& events) {
  std::cout << std::source_location::current().function_name() << " result:\n";

  // TODO
}

// D) The ranges functional-style approach:
void process_D(const Events& events) {
  std::cout << std::source_location::current().function_name() << " result:\n";

  // TODO
}

int main() {
  const Events event_log = {
    {0, EventType::Info,  "motor1: start"},
    {1, EventType::Info,  "motor2: start"},
    {2, EventType::Info,  "motor1: OK"   },
    {3, EventType::Error, "sensor1: FAIL"},
    {4, EventType::Error, "motor2: FAIL" },
    {5, EventType::Info,  "sensor2: OK"  },
    {6, EventType::Info,  "motor1: stop" },
    {7, EventType::Error, "motor2: FAIL" },
    {8, EventType::Error, "sensor1: FAIL"},
    {9, EventType::Error, "motor2: FAIL" },
    // ...
  };

  process_A(event_log);
  process_B(event_log);
  process_C(event_log);
  process_D(event_log);
}

// Compiler Explorer: https://www.godbolt.org/z/jE4j4nes7
