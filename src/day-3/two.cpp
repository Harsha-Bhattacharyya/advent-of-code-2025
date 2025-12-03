#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Program that reads lines from input.txt, extracts digits,
 * and finds the maximum 12-digit joltage by selecting exactly twelve digits
 * while preserving their original order (as a subsequence).
 *
 * For each line:
 * - Extract all digit characters
 * - Find the lexicographically largest subsequence of exactly 12 digits
 * - Form the joltage from this subsequence
 * - Add to total
 *
 * The greedy algorithm: for each of the 12 positions, pick the largest
 * available digit that still leaves enough digits for remaining positions.
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

    size_t n = digits.size();
    size_t k = 12;  // Number of digits to select

    if (n >= k) {
      // Find the lexicographically largest subsequence of length k
      // Greedy approach: for each position, pick the largest digit
      // from the available range that leaves enough digits for remaining positions
      long long joltage = 0;
      size_t start = 0;

      for (size_t i = 0; i < k; i++) {
        // We need to pick (k - i) more digits including this one
        // So we can search from 'start' to 'n - (k - i - 1) - 1' = 'n - k + i'
        size_t end = n - k + i;

        // Find the maximum digit in range [start, end]
        int maxDigit = -1;
        size_t maxPos = start;
        for (size_t j = start; j <= end; j++) {
          if (digits[j] > maxDigit) {
            maxDigit = digits[j];
            maxPos = j;
          }
        }

        joltage = joltage * 10 + maxDigit;
        start = maxPos + 1;  // Next search starts after the selected position
      }

      total += joltage;
    } else if (n > 0) {
      // If fewer than 12 digits, use all available digits in order
      long long joltage = 0;
      for (size_t i = 0; i < n; i++) {
        joltage = joltage * 10 + digits[i];
      }
      total += joltage;
    }
  }

  file.close();
  std::cout << "The total joltage is " << total << std::endl;

  return 0;
}
