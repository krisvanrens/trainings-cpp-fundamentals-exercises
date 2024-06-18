// C++ Fundamentals: exercise mod02-ex2

#include <iostream>
#include <string>

int main() {
  std::string text;

  std::cout << "Please enter some text:\n";
  std::getline(std::cin, text);

  // NOTE: Assign a value here if you're in Compiler Explorer!
  // text = "Good luck to all!";

  // Exercise: implement ROT13 encoding for string 'text'..

  std::cout << "Encoded result: " << text << '\n';
}

// Compiler Explorer: https://www.godbolt.org/z/bvMvzcaPz
