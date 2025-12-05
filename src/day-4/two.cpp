#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Program that reads a grid from input.txt and repeatedly removes
 * accessible paper rolls until none remain, then counts the remaining rolls.
 *
 * A forklift can access a roll of paper if there are fewer than 4 rolls of
 * paper in the 8 adjacent positions (up, down, left, right, and 4 diagonals).
 *
 * The process continues until no more paper rolls can be accessed, and then
 * the count of remaining paper rolls is printed.
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

  // 8 directions: up, down, left, right, and 4 diagonals
  int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  bool removed = true;

  // Keep removing accessible paper rolls until none can be removed
  while (removed) {
    removed = false;

    // Find all accessible paper rolls in this pass
    std::vector<std::pair<int, int>> toRemove;

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
            toRemove.push_back({r, c});
          }
        }
      }
    }

    // Remove all accessible paper rolls found in this pass
    for (const auto& pos : toRemove) {
      grid[pos.first][pos.second] = '.';
      removed = true;
    }
  }

  // Count remaining paper rolls
  int remainingCount = 0;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < static_cast<int>(grid[r].size()); c++) {
      if (grid[r][c] == '@') {
        remainingCount++;
      }
    }
  }

  std::cout << remainingCount << std::endl;

  return 0;
}
