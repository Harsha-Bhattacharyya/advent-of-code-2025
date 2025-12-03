#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Program that reads lines from input.txt, extracts digits,
 * sorts them in descending order, combines the top 2 digits into
 * a 2-digit number, and sums them up.
 *
 * For each line:
 * - Extract all digit characters into an int array
 * - Sort the array in descending order
 * - Take the first two digits (highest values)
 * - Combine them into a 2-digit number (first * 10 + second)
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

    // Sort digits in descending order to get highest first
    std::sort(digits.begin(), digits.end(), std::greater<int>());

    // Combine the first 2 digits into a 2-digit number
    if (digits.size() >= 2) {
      int twoDigitNumber = digits[0] * 10 + digits[1];
      total += twoDigitNumber;
    } else if (digits.size() == 1) {
      // If only one digit, treat it as single digit
      total += digits[0];
    }
  }

  file.close();
  std::cout << "The total joltage is " << total << std::endl;

  return 0;
}
