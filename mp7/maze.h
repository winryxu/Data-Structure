/* Your code here! */
#ifndef MAZE_H
#define MAZE_H
#include "png.h"
#include "dsets.h"

class SquareMaze{
private:
  int w;
  int h;
  DisjointSets mazes;
  vector<vector<bool>> rightWalls;
  vector<vector<bool>> downWalls;
  bool circle( int a, int b);

public:
  SquareMaze();

  void makeMaze	(int 	width, int 	height);

  bool canTravel(	int x, int y,int dir)	const;

  void setWall(int x, int y, int	dir, bool exists);

  vector< int > solveMaze();

  PNG * drawMaze()	const;

  PNG * drawMazeWithSolution();
};

#endif
