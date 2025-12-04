#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Program that reads a grid from input.txt and counts how many paper
 * rolls (@) can be accessed by a forklift.
 *
 * A forklift can access a roll of paper if there are fewer than 4 rolls of
 * paper in the 8 adjacent positions (up, down, left, right, and 4 diagonals).
 *
 * @return int 0 on successful completion, 1 if input.txt could not be opened.
 */
int main() {
  std::ifstream file("input.txt");
  if (!file.is_open()) {
    std::cerr << "Error: Could not open input.txt" << std::endl;
    return 1;
  }

  std::vector<std::string> grid;
  std::string line;

  while (std::getline(file, line)) {
    grid.push_back(line);
  }
  file.close();

  if (grid.empty()) {
    std::cout << 0 << std::endl;
    return 0;
  }

  int rows = static_cast<int>(grid.size());
  int accessibleCount = 0;

  // 8 directions: up, down, left, right, and 4 diagonals
  int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (int r = 0; r < rows; r++) {
    int cols = static_cast<int>(grid[r].size());
    for (int c = 0; c < cols; c++) {
      if (grid[r][c] == '@') {
        // Count adjacent paper rolls
        int adjacentCount = 0;
        for (int d = 0; d < 8; d++) {
          int nr = r + dr[d];
          int nc = c + dc[d];
          if (nr >= 0 && nr < rows && nc >= 0 &&
              nc < static_cast<int>(grid[nr].size())) {
            if (grid[nr][nc] == '@') {
              adjacentCount++;
            }
          }
        }
        // Forklift can access if fewer than 4 adjacent rolls
        if (adjacentCount < 4) {
          accessibleCount++;
        }
      }
    }
  }

  std::cout << accessibleCount << std::endl;

  return 0;
}
