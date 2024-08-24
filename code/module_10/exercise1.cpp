// C++ Fundamentals: exercise mod10-ex1

#include <string_view>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

// Exercise: Create a function 'validate' that validates a string for correctness. It
//            must return a boolean value that represents the validation result. All the
//            test cases below must succeed.
//
//           Validation rules:
//
//            A) The provided string must be between 8 and 24 characters long.
//            B) The provided string must not contain any spaces.
//            C) The provided string must not end with ".ro".
//
// Difficulty rating for this exercise: ⭐

// TODO: Implement 'validate'..

TEST_SUITE("Module 10 - Working with strings") {
  TEST_CASE("Exercise 1 - Rule A") {
    SUBCASE("Empty string") {
      CHECK_FALSE(validate(""));
    }

    const std::string_view alphanum{"abcdefghijklmnopqrstuvwxyz0123456789"};
    REQUIRE(alphanum.length() >= 26); // Test validation predicate.

    SUBCASE("Too short a string") {
      for (unsigned int i = 0; i < 8; i++) {
        CHECK_FALSE(validate({alphanum.data(), i}));
      }
    }

    SUBCASE("Proper length string") {
      for (unsigned int i = 8; i < 25; i++) {
        CHECK(validate({alphanum.data(), i}));
      }
    }

    SUBCASE("Too long a string") {
      for (unsigned int i = 25; i < alphanum.length(); i++) {
        CHECK_FALSE(validate({alphanum.data(), i}));
      }
    }
  }

  TEST_CASE("Exercise 1 - Rule B") {
    CHECK(validate("ThisIsAnOkString"));

    CHECK_FALSE(validate("This IsAnNotOkString"));
    CHECK_FALSE(validate(" ThisIsAnNotOkString"));
    CHECK_FALSE(validate("ThisIsAnNotOkString "));
    CHECK_FALSE(validate("This Is An Not Ok String"));
  }

  TEST_CASE("Exercise 1 - Rule C") {
    CHECK(validate("ThisIsAnOkString"));

    CHECK_FALSE(validate("ThisIsAnOkStr.ro"));
    CHECK_FALSE(validate("ThisIsAnOkString.ro"));
  }
}

// Compiler Explorer: https://www.godbolt.org/z/35fa1bqYh
