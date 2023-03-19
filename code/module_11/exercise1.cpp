// C++ Fundamentals: exercise mod11-ex1

#include <cassert>
#include <concepts>
#include <numeric>
#include <stdexcept>
#include <type_traits>

// Exercise: Extend custom type Fraction to support the following operations:
//
//           A) Equality comparison, e.g. 'a == b' and 'a != b'.
//           B) Ordering based on real value, e.g. 'a > b', 'a < b', 'a >= b' and 'a <= b'.
//           C) The implicit conversion operator to type 'double'.
//           D) Addition of Fraction values, e.g. 'c = a + b' and 'a += b'.
//           E) Subtraction of Fraction values, e.g. 'c = a - b' and 'a -= b'.
//           F) Multiplication with a scalar number (i.e. a non-Fraction integer).
//           G) Division by a scalar number (i.e. a non-Fraction integer).
//           H) Multiplication with another Fraction value.
//           I) Division by another Fraction value.
//           J) Output stream operator '<<' to print a Fraction value.
//           K) (BONUS) {fmt} library formatter output support.

//
// Type traits
//

namespace detail
{
  template<typename From, typename To, typename = void>
  struct is_narrowing_conversion_impl : std::true_type {};

  template<typename From, typename To>
  struct is_narrowing_conversion_impl<From, To, std::void_t<decltype(To{std::declval<From>()})>> : std::false_type {};
}  // namespace detail

template<typename From, typename To>
struct is_narrowing_conversion : detail::is_narrowing_conversion_impl<From, To> {};

template<typename From, typename To>
inline constexpr bool is_narrowing_conversion_v = is_narrowing_conversion<From, To>::value;

//
// Concepts
//

template<typename Type>
concept nonbool_integral = std::integral<Type> && !std::same_as<bool, Type>;

template<typename From, typename To>
concept safely_convertible_to = !is_narrowing_conversion_v<From, To>;

template<typename Op, typename Arg>
concept binary_op = std::invocable<Op, Arg, Arg>;

//
// Fraction
//

template<nonbool_integral Type>
class Fraction final {
public:
  template<safely_convertible_to<Type> Type_>
  Fraction(Type_ numerator, Type_ denominator)
    : numerator_{numerator},
      denominator_{denominator} {
    if (denominator == 0) {
      throw std::invalid_argument("Denominator must be non-zero");
    }

    simplify();
  }

  template<safely_convertible_to<Type> Type_>
  explicit constexpr Fraction(Type_ numerator) noexcept
    : numerator_{numerator},
      denominator_{1} {
  }

  constexpr Type numerator() const noexcept {
    return numerator_;
  }

  constexpr Type denominator() const noexcept {
    return denominator_;
  }

  constexpr double real() const noexcept {
    return static_cast<double>(numerator_) / static_cast<double>(denominator_);
  }

private:
  void simplify() noexcept {
    if (const auto gcd{std::gcd(numerator_, denominator_)}; gcd != 0) {
      numerator_   /= gcd;
      denominator_ /= gcd;
    }
  }

  Type numerator_;
  Type denominator_;
};

//
// Type deduction guides
//

template<typename Type>
Fraction(Type, Type) -> Fraction<Type>;

template<typename Type>
Fraction(Type) -> Fraction<Type>;

//
// Main
//

int main() {
  Fraction f1{22, 7};

  assert(f1.numerator() == 22);
  assert(f1.denominator() == 7);
}

// Compiler Explorer: https://www.godbolt.org/z/1xa5fc9qc
