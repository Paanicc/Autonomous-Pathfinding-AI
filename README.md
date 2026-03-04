# 🤖 Autonomous Pathfinding AI: A* vs Uniform Cost Search

This project features a C program that implements and compares two fundamental pathfinding algorithms: **Uniform Cost Search (UCS)** and **A* Search**. The algorithms are tested on randomly generated $N \times N$ grids. 

Developed by Panagiotis Christodoulou.

## Features
- **Random Maze Generation**: Creates an $N \times N$ environment based on user-defined dimensions, where cells are mapped as free or blocked based on a user-defined probability.
- **8-Directional Movement**: The agent evaluates paths traversing horizontally, vertically, and diagonally (cost is 1 per step).
- **Teleporters**: Special teleportation transition between the bottom-left corner `(0, size-1)` and the top-right corner `(size-1, 0)` with a fixed traversal cost of 2.
- **Search Algorithms Compared**:
  - **Uniform Cost Search (UCS)**: Explores the state space uniformly based on path cost.
  - **A* Search**: Uses the Manhattan distance heuristic function `f(n) = g(n) + h(n)` to explore paths more efficiently towards the goal.

## Compilation & Execution

To compile the C source code, you can use a standard C compiler such as `gcc`.

```bash
gcc askisi1.c -o askisi1
```

Once compiled, run the executable:

On Windows:
```bash
./askisi1.exe
```

On Linux/macOS:
```bash
./askisi1
```

## Usage

Upon executing the program, you will be prompted to enter the following grid arguments:
1. **Maze size**: An integer $N$ for the $N \times N$ matrix (maximum allowed is 100).
2. **Probability (0-1)**: A float indicating the probability that any given cell is a "free space" (e.g., `0.8` for dense open space, `0.3` for many obstacles).
3. **Start (x y)**: The starting `$x$` and `$y$` coordinates (0-indexed).
4. **Goal (x y)**: The target `$x$` and `$y$` coordinates (0-indexed).

> **Note**: Regardless of initial generation, the starting point and goal point are always enforced to be free to ensure valid testing.

## Sample Output

The program evaluates the grid for both algorithms sequentially. For each search method, it outputs a visualization of the path taken and statistics on execution efficiency.

### Map Legend
- `S`: Start Position
- `G`: Goal Position
- `*`: Algorithm Path Traversal
- `.`: Free Block (Open Space)
- `#`: Blocked Node (Wall/Obstacle)

```bash
Enter maze size: 10
Enter probability (0-1): 0.7
Enter start (x y): 1 1
Enter goal (x y): 2 6

--- Uniform Cost Search ---
# . . . . . . . # .
# S . # . # # # . #
# # * . # . # # # .
. * . . . . # . . .
* # . # . # . # # .
. * # # . . . . . #
. # G . # . . . . .
. # . # . . # . . #
# # # . . . . . . .
. . . . . . . . . .
Cost: 5
Expansions: 28

--- A* Search ---
# . . . . . . . # .
# S . # . # # # . #
# # * . # . # # # .
. . * . . . # . . .
. # * # . # . # # .
. * # # . . . . . #
. # G . # . . . . .
. # . # . . # . . #
# # # . . . . . . .
. . . . . . . . . .
Cost: 5
Expansions: 9
```

### Search Statistics
- **Cost**: The total uniform step cost evaluated to reach the goal.
- **Expansions**: The number of node expansions required to generate the final path. This serves as a core metric for demonstrating the efficiency of A* over UCS.

