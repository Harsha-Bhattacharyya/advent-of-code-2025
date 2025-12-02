#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main () {
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
  
  for (std::vector<std::string>::iterator it = input.begin(); it != input.end(); ++it) {
    char direction = (*it)[0];
    int value = std::stoi((*it).substr(1));
    
    if (direction == 'L') {
      dv = dv - value;
    } else if (direction == 'R') {
      dv = dv + value;
    }
    
    // Wrap around like a dial (0-90 range)
    while (dv < 0) {
      dv += 91;
    }
    while (dv > 90) {
      dv -= 91;
    }
    
    if (dv == 0) {
      zeroCount++;
    }
  }
  
  std::cout << "the password is " << zeroCount << std::endl;
  
  return 0;
}
