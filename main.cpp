#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <set>
struct Cell {
    int x, y;
    Cell(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator<(const Cell& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

class Maze {
private:
    std::vector<std::vector<int>> maze;
    int dim;
    Cell start;
    Cell end;

    bool isValid(int nx, int ny) const {
        return nx >= 0 && ny >= 0 && nx < dim && ny < dim && maze[2 * nx + 1][2 * ny + 1] == 1;
    }

    void findAllPathsUtil(Cell current, std::vector<Cell>& path, std::vector<std::vector<Cell>>& paths, std::vector<std::vector<bool>>& visited) {
        int x = current.x, y = current.y;
        visited[x][y] = true;
        path.push_back(current);

        if (current.x == end.x && current.y == end.y) {
            paths.push_back(path);
        } else {
            std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for (auto& dir : directions) {
                int nx = x + dir.first, ny = y + dir.second;
                if (nx >= 0 && ny >= 0 && nx < maze.size() && ny < maze[0].size() && maze[nx][ny] == 0 && !visited[nx][ny]) {
                    findAllPathsUtil({nx, ny}, path, paths, visited);
                }
            }
        }

        path.pop_back();
        visited[x][y] = false;
    }

public:
    Maze(int dim) : dim(dim), maze(2 * dim + 1, std::vector<int>(2 * dim + 1, 1)), start(1, 0), end(2 * dim - 1, 2 * dim - 1) {
        srand(time(nullptr));
    }

    void createMaze() {
        std::stack<Cell> stack;
        Cell init(0, 0);
        maze[2 * init.x + 1][2 * init.y + 1] = 0;
        stack.push(init);

        while (!stack.empty()) {
            Cell current = stack.top();
            stack.pop();

            std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            std::random_shuffle(directions.begin(), directions.end());

            for (auto& dir : directions) {
                int nx = current.x + dir.first;
                int ny = current.y + dir.second;

                if (isValid(nx, ny)) {
                    maze[2 * nx + 1][2 * ny + 1] = 0;
                    maze[2 * current.x + 1 + dir.first][2 * current.y + 1 + dir.second] = 0;
                    stack.push(current);
                    stack.push({nx, ny});
                    break;
                }
            }
        }

        maze[1][0] = 0; // Entrance
        maze[2 * dim - 1][2 * dim] = 0; // Exit
    }

    std::vector<std::vector<Cell>> findAllPaths() {
        std::vector<Cell> path;
        std::vector<std::vector<Cell>> paths;
        std::vector<std::vector<bool>> visited(maze.size(), std::vector<bool>(maze[0].size(), false));
        findAllPathsUtil(start, path, paths, visited);
        return paths;
    }

    void printMaze(const std::set<Cell>& path) const {
        for (int i = 0; i < maze.size(); ++i) {
            for (int j = 0; j < maze[i].size(); ++j) {
                if (i == start.x && j == start.y) {
                    std::cout << 'S'; // Start
                } else if (i == end.x && j == end.y) {
                    std::cout << 'E'; // End
                } else if (path.find({i, j}) != path.end()) {
                    std::cout << '.';  // Path
                } else {
                    std::cout << (maze[i][j] == 1 ? '#' : ' ');  // Walls and paths
                }
            }
            std::cout << '\n';
        }
    }
};

int main() {
    int dim;
    std::cout << "Enter the dimension of the maze: ";
    std::cin >> dim;

    Maze myMaze(dim);
    myMaze.createMaze();
    auto allPaths = myMaze.findAllPaths();

    std::cout << "Total paths found: " << allPaths.size() << std::endl;

    for (const auto& path : allPaths) {
        std::set<Cell> path_set(path.begin(), path.end());
        myMaze.printMaze(path_set);
        std::cout << "------\n";
    }

    return 0;
}
