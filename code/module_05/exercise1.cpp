// C++ Fundamentals: exercise mod05-ex1

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <utility>

// Exercise: Implement the move constructor and move assignment operator such
//            that the code in 'main' builds and the assertions pass. Use the
//            copy-and-swap idiom.

// Helpers to fake a "system device" infrastructure.
namespace System
{

struct Device {
  int handle{-1};
  int offset{-1};

  Device() = default;

  Device(Device&& other) {
    handle = other.handle;
    offset = other.offset;
    other.handle = -1;
    other.offset = -1;
  }

  Device& operator=(Device&& other) {
    if (&other == this) {
      return *this;
    }

    handle = other.handle;
    offset = other.offset;
    other.handle = -1;
    other.offset = -1;
    return *this;
  }

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

  CharDevice(const CharDevice& other)
    : device_{other.device_.clone()} {
  }

  CharDevice& operator=(CharDevice other) {
    std::swap(device_, other.device_);
    return *this;
  }

  // Move constructor..
  // Move assignment operator..

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

    // Move construction:
    CharDevice m1{std::move(x)};

    assert(!x.valid());
    assert(m1.valid());

    // Copy assignment:
    CharDevice m2;
    m2 = std::move(y);

    assert(!y.valid());
    assert(m2.valid());

  } catch(const std::exception& error) {
    std::cerr << "Error: " << error.what() << '\n';
  }
}

// Compiler Explorer: https://www.godbolt.org/z/Pjb71sv53
