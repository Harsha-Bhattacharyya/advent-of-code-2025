#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Program that reads lines from input.txt, extracts digits,
 * finds the two highest digits, and combines them into a 2-digit number
 * where the digit appearing first in the original line is in the tens place.
 *
 * For each line:
 * - Extract all digit characters with their positions
 * - Sort to find the two highest digits
 * - Combine them: the one appearing first in original line is in tens place
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

    // Extract digits from the line into a vector with their positions
    std::vector<std::pair<int, size_t>> digits;  // (digit value, position)

    for (size_t i = 0; i < line.length(); i++) {
      if (line[i] >= '0' && line[i] <= '9') {
        digits.push_back({line[i] - '0', i});
      }
    }

    if (digits.size() >= 2) {
      // Sort by digit value in descending order to find the two highest
      // For ties, prefer the earlier position for consistent behavior
      std::sort(digits.begin(), digits.end(),
                [](const std::pair<int, size_t>& a,
                   const std::pair<int, size_t>& b) {
                  return a.first > b.first ||
                         (a.first == b.first && a.second < b.second);
                });

      // Get the two highest digits
      std::pair<int, size_t> first = digits[0];
      std::pair<int, size_t> second = digits[1];

      // The one that comes first in the original line is in tens place
      int twoDigitNumber;
      if (first.second < second.second) {
        twoDigitNumber = first.first * 10 + second.first;
      } else {
        twoDigitNumber = second.first * 10 + first.first;
      }
      total += twoDigitNumber;
    } else if (digits.size() == 1) {
      // If only one digit, treat it as single digit
      total += digits[0].first;
    }
  }

  file.close();
  std::cout << "The total joltage is " << total << std::endl;

  return 0;
}
