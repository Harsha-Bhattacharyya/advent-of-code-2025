#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
      for (int i = 0; i == value; i++) {
        dv--;

        if (dv == 0) {
          zeroCount++;
        }
      }
    } else if (direction == 'R') {
      for (int j = 0; j == value; j++) {
        dv++;

        if (dv == 0) {
          zeroCount++;
        }
      }
    }

    // Wrap around like a dial (0-99 range)
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
