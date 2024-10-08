// C++ Fundamentals: exercise mod04-ex6

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <utility>

// Exercise: Imagine a class type 'CharDevice' that manages a system device as
//            an internal resource. This class 'CharDevice' will "open" the re-
//            source when 'init' is called on it, and will "close" it at des-
//            truction time. A function called 'valid' can be used to test state.
//
//           Implement the copy constructor and copy assignment operator such
//            that the code in 'main' builds and the assertions pass. Use the
//            copy-and-swap idiom. Note: use the 'clone' function to copy the
//            device resource.
//
// Difficulty rating for this exercise: ⭐⭐

// Helpers to fake a "system device" infrastructure.
namespace System {

struct Device {
  int handle{-1};
  int offset{-1};

  Device() = default;

  Device(Device&&)            = default;
  Device& operator=(Device&&) = default;

  [[nodiscard]] Device clone() const {
    return *this;
  }

  [[nodiscard]] bool operator==(const Device&) const = default;

private:
  Device(const Device&)            = default;
  Device& operator=(const Device&) = default;
};

[[nodiscard]] static bool open_device(Device& device) {
  device.handle = 10;
  device.offset = 123;
  return true;
}

[[nodiscard]] static bool close_device(Device& device) {
  device.handle = -1;
  device.offset = -1;
  return true;
}

[[nodiscard]] static bool is_device_open(const Device& device) {
  return (device != Device{});
}

} // namespace System

class CharDevice {
public:
  CharDevice() = default;

  void init() {
    if (!open_device(device_)) {
      throw std::runtime_error{"Failed to open device"};
    }
  }

  ~CharDevice() {
    if (!close_device(device_)) {
      std::cerr << "Failed to close device\n";
    }
  }

  // TODO: Copy constructor..
  // TODO: Copy assignment operator..

  [[nodiscard]] bool valid() const {
    return is_device_open(device_);
  }

private:
  System::Device device_;
};

int main() {
  try {
    // Default construction:
    CharDevice x;

    assert(!x.valid());

    x.init();

    assert(x.valid());

    // Copy construction:
    CharDevice y{x};

    assert(x.valid());
    assert(y.valid());

    // Copy assignment:
    CharDevice z;
    z = x;

    assert(x.valid());
    assert(y.valid());
    assert(z.valid());

  } catch (const std::exception& error) {
    std::cerr << "Error: " << error.what() << '\n';
  }
}

// Compiler Explorer: https://www.godbolt.org/z/G7xnv18Yd
