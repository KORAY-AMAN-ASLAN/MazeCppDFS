# C++ Maze Generator and Solver

## Description
This project includes a C++ application that dynamically generates mazes and finds all possible paths from a specified start point ('S') to an end point ('E'). 
The program uses object-oriented programming principles to encapsulate functionalities related to maze generation, pathfinding, and visualization.

## Features
- **Maze Generation**: Implements a depth-first search algorithm to create mazes.
- **Pathfinding**: Determines all possible paths from the start to the end of the maze.
- **Visualization**: Displays the maze in the terminal, highlighting paths and marking the start ('S') and end points ('E').

## How to Build and Run
Ensure you have a C++ compiler like g++ and optionally CMake for building the project.

### Building the Project
1. **Clone the Repository**:
git clone https://github.com/KORAY-AMAN-ASLAN/MazeCppDFS.git
cd MazeCppDFS

2. **Compile the Code**:
- Using g++:
  ```
  g++ -o MazeSolver main.cpp -std=c++11
  ```
- Or using CMake:
  ```
  cmake .
  make
  ```

### Running the Application
- Run the compiled application:
./MazeSolver



## License
This project is open-sourced under the [MIT License](LICENSE).


