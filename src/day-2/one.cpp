#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief Program that reads comma-separated number ranges from input.txt,
 * generates all numbers in each range, and totals numbers where the first
 * half of digits equals the second half.
 *
 * For each number in a range:
 * - Convert to string
 * - Check if digit length is even
 * - If even, split in half and compare both halves
 * - If halves are equal, increment the total
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
        size_t len = numStr.length();

        if (len % 2 == 0) {
          std::string firstHalf = numStr.substr(0, len / 2);
          std::string secondHalf = numStr.substr(len / 2);
          if (firstHalf == secondHalf) {
            total = num + total;
          }
        }
      }
    }
  }

  file.close();
  std::cout << total << std::endl;

  return 0;
}
