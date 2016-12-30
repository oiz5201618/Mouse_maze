# Mouse_maze
The repo that mouse search path for maze just for fun.
The mouse will search path with the order by top, right, down and left.
At the end of program it will show the how many coin the mouse collect.

# Usage
```
make
./main
```
* The "maze.txt" should follow the rule
  * The first line define the maze size.
  * The four numbers in the second line define the coordinate of entrance and exit(e.g. en_x en_y ex_x ex_y).
  * The third line define the maze, 0 for path, 1 for wall, 2 for coin.
