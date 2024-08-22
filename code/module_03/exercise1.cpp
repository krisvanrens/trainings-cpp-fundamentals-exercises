// C++ Fundamentals: exercise mod03-ex1

#include <cmath>
#include <format>
#include <iostream>

const float gravity_constant{9.81f}; // In [meters/second^2].

// Exercise: create the following functions:
//
//  1) A global function to calculate the potential energy given an object mass and a height value.
//  2) A global function to calculate the velocity of an object from the kinetic energy and mass.
//  3) A local function to convert energy from joules to Watt-hour.
//  4) A local function to convert velocity from m/s to km/h.
//
// Using these functions, reimplement the equations from module 01: exercise 1.
//
// Difficulty rating for this exercise: ⭐

// Reminders:
//
//   - Potential energy in [joule]: mass * gravity_constant * height
//   - Kinetic energy in [joule]  : 1/2 * mass * velocity^2
//   - Velocity in [meters/second]: sqrt((kinetic_energy * 2) / mass)
//
//   - Joules to Watt-hour     : [Watt.hour] = [joules] / 3600
//   - Meters/second to km/hour: [km/hour]   = [meters/second] * 3.6
//

int main() {
  const float anvil_weight_kg{226.0f};
  const float drop_height_m{58.0f};

  std::cout << std::format("Energy of the anvil at impact: ... Watt-hour\n");
  std::cout << std::format("Speed of the anvil at impact: ... Kilometers/hour\n");
}

// Compiler Explorer: https://www.godbolt.org/z/bh9KWccPM
