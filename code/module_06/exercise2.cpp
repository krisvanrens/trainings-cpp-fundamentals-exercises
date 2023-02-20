// C++ Fundamentals: exercise mod06-ex2

// Exercise: Implement error handling for the 'System' class type. Errors handling should
//            cover construction/initialization and 'run' function calls. Also make sure
//            once an error has occured, the internal state of a 'System' marked invalid,
//            making subsequent calls fail.
//
//           You are free to use any error handling mechanism you see fit.

const bool ERROR_INIT = false;
const bool ERROR_RUN  = false;

class System {
public:
  System() {
    if (ERROR_INIT) {
      // ...
    }
  }

  void run() {
    if (ERROR_RUN) {
      // ...
    }
  }

private:
};

int main() {
  System s;

  s.run();
  s.run();
}

// Compiler Explorer: https://www.godbolt.org/z/4d6szfeWh
