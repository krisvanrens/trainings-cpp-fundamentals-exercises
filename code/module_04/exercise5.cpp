// C++ Fundamentals: exercise mod04-ex5

#include <cassert>

// Exercise: Create a class type 'Processor' that has an internal member of
//            type 'Resource'. Class 'Processor' has a member function 'run'
//            that calls 'Resource::use' on its resource. Make sure all init-
//            ialization is fail- and exception-safe.

// ============================================================================
// Immobile resource (uncopyable and unmovable).
class Resource {
public:
  Resource() = default;
  ~Resource();

  [[nodiscard]] bool init();
  [[nodiscard]] bool destroy();

  void use() const;

  Resource(const Resource&)            = delete;
  Resource& operator=(const Resource&) = delete;
  Resource(Resource&&)                 = delete;
  Resource& operator=(Resource&&)      = delete;

private:
  bool initialized_{false};
};

// ============================================================================
// Processor.

// TODO

// ============================================================================
// Main program entry:
int main() {
  Processor p;
  p.run();
}

// ============================================================================
// Resource implementation.

Resource::~Resource() {
  assert(!initialized_);
}

bool Resource::init() {
  assert(!initialized_);
  initialized_ = true;
  return initialized_;
}

void Resource::use() const {
  assert(initialized_);
}

bool Resource::destroy() {
  assert(initialized_);
  initialized_ = false;
  return !initialized_;
}

// Compiler Explorer: https://www.godbolt.org/z/7WxWE3vaK