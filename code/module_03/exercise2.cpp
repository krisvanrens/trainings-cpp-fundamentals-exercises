// C++ Fundamentals: exercise mod03-ex2

#include <cassert>
#include <iostream>
#include <string>

// Exercise: work through the evolution of a function as the requirements change. Each of
//            the five function version iterations have their own data fields, found in
//            the 'Inputs' namespace. However the code is set up such that e.g. for the
//            first version, v1, we can just call: 'validate_v1(data)' in 'main'. See the
//            'main' function for the explanation/goal for each sub-exercise.

struct DataV2 {
  unsigned long values;
  unsigned int  crc;
};

struct DataV3 {
  unsigned long values;
  unsigned int  crc;
  bool          validated{};
};

namespace Inputs {

// clang-format off
namespace v1 { const unsigned long data{7815349426721095};        }
namespace v2 { const DataV2        data{7815349426721095, 37311}; }
namespace v3 {       DataV3        data{7815349426721095, 37311}; }
namespace v4 { const DataV2        data{7815349426721095, 37311}; }
namespace v5 { const DataV2        data{7815349426721095, 37311}; }
// clang-format on

} // namespace Inputs

bool validate_v1(/* ... */) {
  return true;
}

bool validate_v2(/* ... */) {
  return true;
}

bool validate_v3(/* ... */) {
  return true;
}

bool validate_v4(/* ... */) {
  const std::string error{"Total system breakdown!"};
  return true;
}

bool validate_v5(/* ... */) {
  const std::string error{"Total system breakdown!"};
  return true;
}

int main() {
  {
    // Version 1:
    using namespace Inputs::v1;

    // Story: we must implement a data validation function.

    // Goal: implement function 'validate_v1' prototype such that we can call it with
    //        the 'data' argument. Think about how the parameter should be passed.

    validate_v1(/* ... */);
  }
  {
    // Version 2:
    using namespace Inputs::v2;

    // Story: the signature of the data to be validated changed.

    // Goal: implement function 'validate_v2' prototype such that we can call it with
    //        the 'data' argument. Think about how the parameter should be passed.

    validate_v2(/* ... */);
  }
  {
    // Version 3:
    using namespace Inputs::v3;

    // Story: the signature of the data to be validated changed again, but now the
    //         validation status must be stored in the data structure as well. This means
    //         after the validation function is called, the 'validated' field of the
    //         'data' structure must be true.

    // Goal: implement function 'validate_v3' prototype such that we can call it with
    //        the 'data' argument. Think about how the parameter should be passed.

    assert(!data.validated);

    validate_v3(/* ... */);

    // Uncomment the following assertion when working on v3:
    // assert(data.validated);
  }
  {
    // Version 4:
    using namespace Inputs::v4;

    // Story: it was decided that storing the validation state inside the 'data' element
    //         was not a good idea after all. This change is reverted to the version of
    //         'data' equal to the version 2 implementation. There is an extra require-
    //         ment though: the validation can now fail with a message.

    // Goal: implement function 'validate_v4' prototype such that we can call it with
    //        the 'data' argument. Also add a way to get the error message generated from
    //        the function to the call site.

    validate_v4(/* ... */);

    // std::cerr << "V4: Error message: " << /* ... */ << '\n';
  }
  {
    // Version 5:
    using namespace Inputs::v5;

    // Story: the function is fine now. However, your colleagues make a mess committing
    //         code where they forget to deal with the validation function result.

    // Goal: make sure there is at least a warning if 'validate_v5' is called without
    //        handling the result value.

    const auto result = validate_v5(/* ... */); // OK.
    validate_v5(/* ... */);                     // Warning/error.

    // std::cerr << "V5: Error message: " << /* ... */ << '\n';
  }
}

// Compiler Explorer: https://www.godbolt.org/z/8Mr3afjG5
