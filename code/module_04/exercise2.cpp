// C++ Fundamentals: exercise mod04-ex2

#include <string>
#include <string_view>
#include <vector>

// Exercise: model an organization. Within an organization, employees are hired for one
//            specific role. In their role, they fulfill one or more functions. Model
//            the 'Employee' data structure to correctly represent these relations.
//           The employee type should have a member function 'print' that prints the
//            employee information including role and functions. The mappings of each
//            employee/role/function is given in 'main'.
//
// Difficulty rating for this exercise: ⭐

// Organization role; e.g. 'developer', 'manager', etc.
class Role {
public:
  Role(std::string_view name)
    : name_{name} {
  }

  [[nodiscard]] std::string_view get() const {
    return name_;
  }

private:
  std::string name_;
};

// Function; e.g. 'IT administrator', 'sales engineer', etc.
class Function {
public:
  Function(std::string_view name)
    : name_{name} {
  }

  [[nodiscard]] std::string_view get() const {
    return name_;
  }

private:
  std::string name_;
};

using Functions = std::vector<Function>;

class Employee {
public:
  void print() const {
    // ...
  }

private:
  std::string name_;
};

int main() {
  // Within the organization, "Alice" was hired as a "manager".
  Employee a;

  // Within the organization, "Bob" was hired as a "developer".
  Employee b;

  // Within the organization, "Charlie" was hired as a "developer".
  Employee c;

  // Function: "IT administrator" // Alice, Charlie.
  // Function: "sales engineer"   // Bob.
  // Function: "test engineer"    // Bob, Charlie.
  // Function: "director"         // Alice.

  a.print();
  b.print();
  c.print();
}

// Compiler Explorer: https://www.godbolt.org/z/s938Pdr95
