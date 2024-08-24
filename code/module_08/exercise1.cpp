// C++ Fundamentals: exercise mod08-ex1

#include <iostream>
#include <set>
#include <string>
#include <string_view>

// Consider this custom type 'Classification' and the associative set. Can you reason
//  about how the ordering in the set is determined? Does it make sense with the output
//  at the command-line?
//
// Exercise: Define an enumerator type called 'Visibility' with two possible values:
//            'Hidden' and 'Visible'. Add a member variable of type Visibility to the
//            Classification class type. Add it _before_ the 'name_' member. Extend the
//            class constructor to take a visibility value, using as default value
//            'Visible', so that the emplace calls in the main function don't break.
//           Now, change the visibility of the 'object.zwuxl' classification to 'Hidden'.
//           What changes? Is the set ordering and command-line output still correct?
//           Make the set ordering use lexigraphical ordering again.
//
// Difficulty rating for this exercise: ⭐⭐

class Classification {
private:
  std::string name_;

public:
  Classification(std::string_view name)
    : name_{name} {
  }

  [[nodiscard]] const std::string& name() const noexcept {
    return name_;
  }

  auto operator<=>(const Classification&) const = default;
};

using ClassificationSet = std::set<Classification>;

int main() {
  ClassificationSet s;

  s.emplace("object.person");
  s.emplace("object.robot");
  s.emplace("object.zwuxl");
  s.emplace("object.animal.dog");
  s.emplace("object.car");
  s.emplace("object.bicycle");

  for (const auto& item : s) {
    std::cout << item.name() << '\n';
  }
}

// Compiler Explorer: https://www.godbolt.org/z/T6bdarPEq
