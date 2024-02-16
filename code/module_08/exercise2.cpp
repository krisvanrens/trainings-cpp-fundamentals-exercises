// C++ Fundamentals: exercise mod08-ex2

#include <format>
#include <iostream>
#include <string_view>
#include <unordered_map>

// Exercise: Print the 'GAMES' map contents. Try to find as many possible ways to do so!

enum class Game {
  CommanderKeen,
  Doom,
};

using Title   = std::string_view;
using GameMap = std::unordered_multimap<Game, Title>;

using namespace std::literals;

const std::unordered_map<Game, Title> GAME2STR = {
  {Game::CommanderKeen, "Commander Keen"sv},
  {Game::Doom, "Doom"sv},
};

const GameMap GAMES = {
  {Game::CommanderKeen, "Invasion of the Vorticons"sv},
  {Game::CommanderKeen, "Keen Dreams"sv},
  {Game::CommanderKeen, "Goodbye, Galaxy"sv},
  {Game::CommanderKeen, "Aliens Ate My Babysitter"sv},
  {Game::Doom, "Doom"sv},
  {Game::Doom, "Doom II: Hell on Earth"sv},
  {Game::Doom, "Final Doom"sv},
};

int main() {
  const auto example = *GAMES.cbegin();
  std::cout << std::format("{}: {}\n", GAME2STR.at(example.first), example.second);

  // TODO: Print all map contents..
}

// Compiler Explorer: https://www.godbolt.org/z/xj8W7v8fY
