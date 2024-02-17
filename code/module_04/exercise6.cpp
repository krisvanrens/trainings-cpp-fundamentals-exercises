// C++ Fundamentals: exercise mod04-ex6

#include <array>
#include <cstddef>

// Exercise: Read the documentation for the 'find_coefficient' function API, find the flaws and
//            improve it. Consider all angles relevant for caller and callee.

// Implementation details -- don't touch.
namespace Lut {

static constexpr std::size_t SIZE = 1024u;

struct Element {};

using Size = std::size_t;
using Lut  = std::array<Element, SIZE>;

} // namespace Lut

///
/// Find the coefficient given the LUT offset and memory range.
///
/// \param c              The resulting coefficient.
/// \param lut_offset_el  The element in the LUT where the memory range offset starts.
/// \param lut_range_size The LUT memory range size.
/// \param begin_incl     Whether or not the begin element of the memory range must be included.
/// \param end_incl       Whether or not the end element of the memory range must be included.
/// \param correct_tco    Whether or not to correct for transfer call oscillation.
/// \param normalization  Indicates if normalization must be applied (default: on).
///
void find_coefficient(double&             c,
                      const Lut::Element& lut_offset_el,
                      const Lut::Size     lut_range_size,
                      bool                begin_incl,
                      bool                end_incl,
                      bool                correct_tco,
                      bool                normalization = true) {
  // ..uninteresting implementation..
}

int main() {
  const Lut::Lut lut;

  double          c1{}, c2{}, c3{};
  const auto&     offset_el1  = lut[50];
  const auto&     offset_el2  = lut[20];
  const auto&     offset_el3  = lut[80];
  const Lut::Size range1_size = 16;
  const Lut::Size range2_size = 4;
  const Lut::Size range3_size = 12;

  find_coefficient(c1, offset_el1, range1_size, true, true, false);
  find_coefficient(c2, offset_el2, range2_size, true, false, false, false);
  find_coefficient(c3, offset_el2, range3_size, false, false, true);
}

// Compiler Explorer: https://www.godbolt.org/z/3YMvTW1b1