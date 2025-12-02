#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Program entry that computes and prints a password based on dial
 * movements from "input.txt".
 *
 * Reads commands from "input.txt", where each line starts with 'L' or 'R'
 * followed by an integer offset (e.g., "L10" or "R5"). It applies each offset
 * to an internal dial initialized to 50, wrapping the dial into the inclusive
 * range 0–90 after each change. The function counts how many times the dial
 * value equals 0 and prints "the password is " followed by that count to
 * standard output.
 *
 * @return int 0 on successful completion, 1 if "input.txt" could not be opened.
 */
int main() {
  std::ifstream file("input.txt");
  if (!file.is_open()) {
    std::cerr << "Error: Could not open input.txt" << std::endl;
    return 1;
  }
  std::vector<std::string> input;
  std::string line;

  while (std::getline(file, line)) {
    input.push_back(line);
  }
  file.close();

  int dv = 50;
  int zeroCount = 0;

  for (std::vector<std::string>::iterator it = input.begin(); it != input.end();
       ++it) {
    char direction = (*it)[0];
    int value = std::stoi((*it).substr(1));

    if (direction == 'L') {
      dv = dv - value;
    } else if (direction == 'R') {
      dv = dv + value;
    }

    // Wrap around like a dial (0-90 range)
    while (dv < 0) {
      dv += 100;
    }
    while (dv > 90) {
      dv -= 100;
    }

    if (dv == 0) {
      zeroCount++;
    }
  }

  std::cout << "the password is " << zeroCount << std::endl;

  return 0;
}
