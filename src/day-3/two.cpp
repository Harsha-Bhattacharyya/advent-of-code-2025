#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Program that reads lines from input.txt, extracts digits,
 * and finds the maximum 12-digit joltage by selecting exactly twelve digits
 * where the digits are arranged from largest to smallest.
 *
 * For each line:
 * - Extract all digit characters
 * - Select the 12 largest digits
 * - Arrange them in descending order to form the largest possible joltage
 * - Add to total
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

    // Extract digits from the line into a vector
    std::vector<int> digits;

    for (char c : line) {
      if (c >= '0' && c <= '9') {
        digits.push_back(c - '0');
      }
    }

    if (digits.size() >= 12) {
      // Sort digits in descending order
      std::sort(digits.begin(), digits.end(), std::greater<int>());

      // Take the 12 largest digits and form the largest joltage
      long long joltage = 0;
      for (int i = 0; i < 12; i++) {
        joltage = joltage * 10 + digits[i];
      }
      total += joltage;
    } else if (digits.size() > 0) {
      // If fewer than 12 digits, use all available digits
      std::sort(digits.begin(), digits.end(), std::greater<int>());
      long long joltage = 0;
      for (size_t i = 0; i < digits.size(); i++) {
        joltage = joltage * 10 + digits[i];
      }
      total += joltage;
    }
  }

  file.close();
  std::cout << "The total joltage is " << total << std::endl;

  return 0;
}
