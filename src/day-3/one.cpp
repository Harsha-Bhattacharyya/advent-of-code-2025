#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Program that reads lines from input.txt, extracts digits,
 * and finds the maximum 2-digit joltage by selecting two digits
 * where the first chosen digit is in the tens place.
 *
 * For each line:
 * - Extract all digit characters
 * - For each digit at position i, find max digit at position j > i
 * - Combine as digit[i] * 10 + digit[j] to form joltage
 * - Find the maximum such joltage
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

    if (digits.size() >= 2) {
      // Find maximum joltage by trying each digit as tens place
      // and finding the max digit after it as ones place
      int maxJoltage = 0;
      size_t n = digits.size();

      for (size_t i = 0; i + 1 < n; i++) {
        // Find max digit after position i
        int maxAfter = -1;
        for (size_t j = i + 1; j < n; j++) {
          if (digits[j] > maxAfter) {
            maxAfter = digits[j];
          }
        }
        if (maxAfter >= 0) {
          int joltage = digits[i] * 10 + maxAfter;
          if (joltage > maxJoltage) {
            maxJoltage = joltage;
          }
        }
      }
      total += maxJoltage;
    } else if (digits.size() == 1) {
      // If only one digit, treat it as single digit
      total += digits[0];
    }
  }

  file.close();
  std::cout << "The total joltage is " << total << std::endl;

  return 0;
}
