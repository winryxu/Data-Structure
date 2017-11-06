/* Your code here! */

#ifndef DSETS_H
#define DSETS_H

#include <vector>

using namespace std;
using std::vector;


class DisjointSets
{
private:
  vector<int> elements;

public:
  void 	addelements (int num);
  int 	find (int elem);
  void 	setunion (int a, int b);

};

#endif
