// C++ Fundamentals: exercise mod02-ex4

#include <random>
#include <utility>

// Generates a double dice throw value.
[[nodiscard]] auto throw_dice() {
  static std::random_device              rd;
  static std::mt19937                    generator(rd());
  static std::uniform_int_distribution<> dist(1, 6);
  return std::pair{dist(generator), dist(generator)};
}

// Exercise: implement "Game of the Goose" for four players..

int main() {
  // Rule 1: Bridge: if position is 6, proceed to position 12 immediately.
  // Rule 2: Tavern: if position is 19, pass a turn.
  // Rule 3: Well: if position is 31, must wait until another freed by another player.
  // Rule 4: Maze: if position 42, go back to position 37 immediately.
  // Rule 5: Prison: if position is 52, pass three turns.
  // Rule 6: Death: if position 58, go back to the beginning immediately.
  // Rule 7: End: the player who reaches position 63 as first, wins.

  // Extra rule I: There is a "Goose" on each position that is:
  //                - a multiple of 9     (i.e.: 9, 18, 27, 36, 45, 54),
  //                - a multiple of 9, -4 (i.e.: 5, 14, 23, 32, 41, 50, 59).
  // For each of these positions, double the score as thrown in this turn.

  // Extra rule II: if position 63 is not exactly reached, and it is passed, the surplus
  //                 score must be counted backward. E.g. at position 60 the player throws
  //                 9 in total, the next position is then 63 - (9 - 3) = 57.

  // Extra rule III: If the first throw is [5, 4]/[4, 5], immediately go to position 53.

  // Extra rule IV: If the first throw is [6, 3]/[3, 6], immediately go to position 26.
}

// Compiler Explorer: https://www.godbolt.org/z/Y4GcPMecP
