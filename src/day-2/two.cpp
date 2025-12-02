#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

/**
 * @brief Checks if a number string is made of a repeating pattern at least
 * twice.
 *
 * A number is invalid if it consists of some sequence of digits repeated at
 * least twice. For example:
 * - 12341234 (1234 repeated 2 times)
 * - 123123123 (123 repeated 3 times)
 * - 1111111 (1 repeated 7 times)
 *
 * @param numStr The number as a string
 * @return true if the number is made of a repeating pattern, false otherwise
 */
bool isRepeatingPattern(const std::string& numStr) {
  size_t len = numStr.length();

  // Try all possible pattern lengths from 1 to len/2
  for (size_t patLen = 1; patLen <= len / 2; patLen++) {
    if (len % patLen == 0) {
      std::string pattern = numStr.substr(0, patLen);
      bool isRepeating = true;

      // Check if the entire string is made of this pattern
      for (size_t i = patLen; i < len; i += patLen) {
        if (numStr.substr(i, patLen) != pattern) {
          isRepeating = false;
          break;
        }
      }

      if (isRepeating) {
        return true;
      }
    }
  }

  return false;
}

/**
 * @brief Program that reads comma-separated number ranges from input.txt,
 * generates all numbers in each range, and sums numbers that are invalid.
 *
 * A number is invalid if it consists of some sequence of digits repeated
 * at least twice.
 *
 * @return int 0 on successful completion, 1 if input.txt could not be opened.
 */
int main() {
  std::ifstream file("input.txt");
  if (!file.is_open()) {
    std::cerr << "Error: Could not open input.txt" << std::endl;
    return 1;
  }

  long long total = 0;
  std::string line;

  while (std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }

    std::stringstream lineStream(line);
    std::string range;

    while (std::getline(lineStream, range, ',')) {
      size_t dashPos = range.find('-');
      if (dashPos == std::string::npos) {
        continue;
      }

      long long start, end;
      try {
        start = std::stoll(range.substr(0, dashPos));
        end = std::stoll(range.substr(dashPos + 1));
      } catch (const std::exception& e) {
        std::cerr << "Error parsing range: " << range << std::endl;
        continue;
      }

      for (long long num = start; num <= end; num++) {
        std::string numStr = std::to_string(num);

        if (isRepeatingPattern(numStr)) {
          total += num;
        }
      }
    }
  }

  file.close();
  std::cout << total << std::endl;

  return 0;
}
