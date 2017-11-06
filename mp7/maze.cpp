/* Your code here! */
#include "maze.h"
#include <queue>
#include <map>
#include <stack>
SquareMaze::SquareMaze()
{
  w = 0;
  h = 0;
}

/* check for circle
  if the parent is the same, return true
*/
bool SquareMaze::circle( int a, int b)
{
  int first = mazes.find(a);
  int second = mazes.find(b);
  if (first == second) return true;
  else return false;
}
/*Makes a new SquareMaze of the given height and width.

If this object already represents a maze it will clear all
the existing data before doing so. You will start with a square grid (like graph paper)
with the specified height and width. You will select random walls to delete without creating a cycle,
until there are no more walls that could be deleted without creating a cycle. Do not delete walls on the perimeter of the grid.

Hints: You only need to store 2 bits per square: the "down" and "right" walls.
 The finished maze is always a tree of corridors.)

Parameters
@width	The width of the SquareMaze (number of cells)
@height	The height of the SquareMaze (number of cells)

*/
// 2*2 delete 3; 2*3 delete 5; 3*3 delete 8;  4*4 delete 15; 5*5 delete 24; 6*6 delete 25; 7*7 delete 48

void SquareMaze::makeMaze(int	width, int height)
{
  w = width;
  h = height;
  mazes.addelements(w*h);
  // 2D vector for rightWalls and downWalls
  rightWalls.resize(width, std::vector<bool>(height, true));
  downWalls.resize(width, std::vector<bool>(height, true));
  // positions of all elements
  vector<int> positions;
    for (int i = 1; i <= w*h; i++)
    {
      positions.push_back(i);
    }
  //randomly remove walls

  while(positions.size() != 1)
  {
    // get the location of the elements
    int position = rand()%(positions.size());
    int loc = positions[position];
    // get the row and column index
    int x = (loc-1)%w;
    int y = (loc - x)/w;
    // count++;
    // cout<<"position:   x:      y:     "<<loc<<"    "<<x<<"      "<<y<<"    "<<count<<endl;
    // delete the position from the vector
    //positions.erase(positions.begin()+position);
    // in case the element is access again
    std::swap(positions[position],positions[positions.size()-1]);
    positions.pop_back();
    // go right first or go down first
    int firstRight = rand()%2;
    if (firstRight)
    {
      // check right first
      if (x != width-1 && !circle(y*width+x,y*width+x+1) && rightWalls[x][y] )
      {
        //cout<<"here?"<<endl;
            rightWalls[x][y] = false;
            mazes.setunion(y*width+x,y*width+x+1);
            //walls--;
      }
      // check down
      if (y != height-1 && !circle(y*width+x,(y+1)*width+x) && downWalls[x][y] )
      {
            downWalls[x][y] = false;
            mazes.setunion(y*width+x,(y+1)*width+x);
            //walls--;
      }
    }
    else
    {
      if (y != height-1 && !circle(y*width+x,(y+1)*width+x) && downWalls[x][y] )
      {
        //cout<<"here here here?"<<endl;
            downWalls[x][y] = false;
            mazes.setunion(y*width+x,(y+1)*width+x);
      }
      if (x != width-1 && !circle(y*width+x,y*width+x+1) && rightWalls[x][y] )
      {
            rightWalls[x][y] = false;
            mazes.setunion(y*width+x,y*width+x+1);
      }
    }

  }


  // run time would be longer in this one
  // int walls = w*h-1;
  // while(walls != 0)
  // {
  //   int x = rand()%w;
  //   int y = rand()%(h-1);
  //   int goingdown = rand()%2;
  //   //if (x == width-1 || y == height) continue;
  //   // if remove right wall
  //   if (!goingdown)
  //   {
  //     if (!circle(y*width+x,y*width+x+1) && rightWalls[x][y] && x != width-1)
  //     {
  //       rightWalls[x][y] = false;
  //       mazes.setunion(y*width+x,y*width+x+1);
  //       walls--;
  //     }
  //   }
  //   else
  //   {
  //     if (!circle(y*width+x,(y+1)*width+x) && downWalls[x][y] && y != height-1)
  //     {
  //       downWalls[x][y] = false;
  //       mazes.setunion(y*width+x,(y+1)*width+x);
  //       walls--;
  //     }
  //   }
  // }

}

bool SquareMaze::canTravel(int x,int y, int dir)	const
{
  //going right
  if (dir == 0)
  {
    return x != w -1 && !rightWalls[x][y];
  }
  //going down
  else if (dir == 1)
  {
    return y != h - 1 && !downWalls[x][y];
  }
  //going left
  else if (dir == 2)
  {
    return x != 0 && !rightWalls[x-1][y];
  }
  //going up
  else if (dir == 3)
  {
    return y != 0 && !downWalls[x][y-1];
  }
  return false;
}
/*
Sets whether or not the specified wall exists.

This function should be fast (constant time).
You can assume that in grading we will not make your maze a non-tree
and then call one of the other member functions.
setWall should not prevent cycles from occurring,
but should simply set a wall to be present or not present.
Our tests will call setWall to copy a specific maze into your implementation.

Parameters
x	The x coordinate of the current cell
y	The y coordinate of the current cell
dir	Either 0 (right) or 1 (down),
which specifies which wall to set (same as the encoding explained in canTravel).
You only need to support setting the bottom and right walls of every square in the grid.
exists	true if setting the wall to exist, false otherwise
*/

void SquareMaze::setWall(int x, int y, int	dir, bool exists)
{

    if (dir == 0)
    {
      rightWalls[x][y] = exists;
    }
    else
    {
      downWalls[x][y] = exists;
    }
}

/*
For each square on the bottom row (maximum y coordinate),
there is a distance from the origin (i.e. the top-left cell),
which is defined as the length (measured as a number of steps) of the only path through the maze
 from the origin to that square.

Select the square in the bottom row with the largest
distance from the origin as the destination of the maze.
solveMaze() returns the winning path from the origin to the destination
as a vector of integers, where each integer represents the direction of a step,
using the same encoding as in canTravel().

If multiple paths of maximum length exist, use the one with the destination cell
that has the smallest x value.

Hint: this function should run in time linear in the number of cells in the maze.

Returns
a vector of directions taken to solve the maze
*/

vector< int > SquareMaze::solveMaze()
{
    vector<int> route;
    vector<vector<bool>> visited;
    visited.resize(w, std::vector<bool>(h, false));
    vector<int> positions;
    for (int i = 0; i < w*h; i++)
    {
        positions.push_back(i);
    }
    // int x = (loc-1)%w;
    // int y = (loc - x)/w;
    visited[0][0] = true;
    int x = 0;
    int y = 0;
    // record the cell we visited
    queue<int> record;
    map<int,int> map_route;
    record.push(0);
    // use BFS
    while (!record.empty())
    {
      int loc = record.front();
      int x = loc%w;
      int y = (loc - x)/w;
      record.pop();
      // check right
      if (canTravel(x,y,0) && !visited[x+1][y])
      {
        int pos = y*w+x+1;
        record.push(pos);
        visited[x+1][y] = true;
        map_route[pos] = loc;
      }
      // check down
      if (y != h -1 && canTravel(x,y,1) && !visited[x][y+1])
      {
        int pos = (y+1)*w+x;
        record.push(pos);
        visited[x][y+1] = true;
        map_route[pos] = loc;
      }
      // check left
      if (x != 0 && canTravel(x,y,2) && !visited[x-1][y])
      {
        int pos = y*w+x-1;
        record.push(pos);
        visited[x-1][y] = true;
        map_route[pos] = loc;
      }
      // check up
      if (canTravel(x,y,3) && !visited[x][y-1])
      {
        int pos = (y-1)*w+x;
        record.push(pos);
        visited[x][y-1] = true;
        map_route[pos] = loc;
      }
    }
    // for (int i = 0 ; i<w; i++)
    // {
    //   for (int j = 0; j < h; j++)
    //   {cout<<visited[i][j]<<endl;}
    // }
    // find the destination, check for largest path
    int max_count = 0;
    int dest = 0;
    //cout<<"line 283"<< endl;
    for (int i = 0; i < w; i++)
    {
      int count = 0;
      int pos = (h-1)*w+i;
      //int temp = pos;
      //cout<<"pos:  "<<pos<<endl;
      if (circle(pos,0))
      {
        while(map_route[pos] != 0)
        {
          count++;
          //cout<<"line 291"<<endl;
          pos = map_route[pos];
          //cout<<"pos :::"<<pos<<endl;
        }
        //update max
        if (count > max_count)

        {
          max_count = count;
          dest = (h-1)*w+i;
        }
      }

    }

    //cout<<"dest :  "<<dest<<endl;
    int dest_x = dest%w;
    int dest_y = (dest - dest_x)/w;
    downWalls[dest_x][dest_y] = false;
    // traverse to get the directions
    int pos = dest;
    stack<int> s;
    //cout<<"parent of 1 :"<<map_route[1]<<endl;
    while (pos != 0)
    {
      //cout<<"line 333:    "<<pos<<endl;
      int curr_x = pos%w;
      int curr_y = (pos - x)/w;
      pos = map_route[pos];
      int x = pos%w;
      int y = (pos - x)/w;
      // go right
      if (curr_x - x == 1)
      {
        s.push(0);
      }
      // go left
      if (curr_x - x == -1)
      {
        s.push(2);
      }
      // go down
      if (curr_y - y == 1)
      {
        s.push(1);
      }
      // go up
      if (curr_y - y == -1)
      {
         s.push(3);
      }
    }
    // push back to vector
    while (!s.empty())
    {
      route.push_back(s.top());
      s.pop();
    }
    // for (auto it :route)
    // {
    //   cout<<"route:      "<<it<<endl;
    // }
    return route;
    //return vector<int>();

}




/*
Draws the maze without the solution.

First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1).
 where height and width were the arguments to makeMaze.
 Blacken the entire topmost row and leftmost column of pixels,
 except the entrance (1,0) through (9,0).
 For each square in the maze, call its maze coordinates (x,y). If the right wall exists,
 then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10.
 If the bottom wall exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.

The resulting PNG will look like the sample image,
except there will be no exit from the maze and the red line will be missing.

Returns
a PNG of the unsolved SquareMaze

*/
PNG * SquareMaze::drawMaze()	const
{
  int width = w*10+1;
  int height = h*10+1;
  PNG* temp = new PNG(width,height);
  //blacken top most row
  for (int i = 10; i < width; i++)
  {
    (*temp)(i,0)->red = 0;
    (*temp)(i,0)->green = 0;
    (*temp)(i,0)->blue = 0;
  }
  //blacken left most row
  for (int i = 0; i< height; i++)
  {
    (*temp)(0,i)->red = 0;
    (*temp)(0,i)->green = 0;
    (*temp)(0,i)->blue = 0;
  }

  for (int i = 0; i < w; i++)
  {
    for (int j = 0; j < h; j++)
    {
      //int count = 0;
      if (rightWalls[i][j])
      {
        // count++;
        // cout<<"reach:  "<<count<<endl;
        for (int k = 0; k < 11; k++)
        {
          (*temp)((i+1)*10,j*10+k)->red = 0;
          (*temp)((i+1)*10,j*10+k)->green = 0;
          (*temp)((i+1)*10,j*10+k)->blue = 0;
        }
      }
      // (x*10+k, (y+1)*10)
      if (downWalls[i][j])
      {
        for (int k = 0; k < 11; k++)
        {
          (*temp)(i*10+k,(j+1)*10)->red = 0;
          (*temp)(i*10+k,(j+1)*10)->green = 0;
          (*temp)(i*10+k,(j+1)*10)->blue = 0;
        }
      }
    }
  }

  return temp;
}


/*
This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit.

Start at pixel (5,5). Each direction in the solution vector corresponds to a trail of 11 red pixels in the given direction. If the first step is downward, color pixels (5,5) through (5,15) red. (Red is 255,0,0 in RGB). Then if the second step is right, color pixels (5,15) through (15,15) red. Then if the third step is up, color pixels (15,15) through (15,5) red. Continue in this manner until you get to the end of the solution vector, so that your output looks analogous the above picture.

Make the exit by undoing the bottom wall of the destination square: call the destination maze coordinates (x,y), and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.

Returns
a PNG of the solved SquareMaze
*/


PNG * SquareMaze::drawMazeWithSolution()
{
  PNG* temp = drawMaze();
  vector<int> route = solveMaze();
  size_t x = 5;
  size_t y = 5;
  for (auto dir : route)
  {
    // right
    if (dir == 0)
    {
        for (int i = 0; i < 11; i ++)
        {
          //x+=i;
          *((*temp)(x + i,y)) = RGBAPixel(255,0,0);
        }
        x+=10;
    }
    // down
    if (dir == 1)
    {
      //size_t tem = j;
      for (int j = 0; j < 11; j++)
      {
        *(*temp)(x,y+j) = RGBAPixel(255,0,0);
      }
      y+=10;
    }
    // left
    if (dir == 2)
    {
      //size_t tem = i;
      for (int i = 0; i < 11; i ++)
      {
        *(*temp)(x-i,y) = RGBAPixel(255,0,0);
      }
      x-=10;
    }
    // up
    if (dir == 3)
    {
      //size_t tem = j;
      for (int j = 0; j < 11 ;j ++)
      {
        *(*temp)(x,y-j) = RGBAPixel(255,0,0);
      }
      y-=10;
    }
  }
//  PNG* temp = new PNG();
  return temp;
}
