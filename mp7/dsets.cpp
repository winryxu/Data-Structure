/* Your code here! */

#include "dsets.h"
/*
Creates n unconnected root nodes at the end of the vector.
@Parameters: num	The number of nodes to create
*/
// add roots with representative number -1
void DisjointSets::addelements (int num)
{
  for (int i = 0; i < num; i++)
    elements.push_back(-1);
}
/*
This function should compress paths and works as described in lecture.
@Returns: the index of the root of the up-tree in which the parameter element resides.
*/
// find the root, not the representative number of root
int DisjointSets::find (int elem)
{
  if (elements[elem] < 0) return elem;

  return  elements[elem] = find(elements[elem]);
  //return elements[elem];
}

/*
This function should be implemented as union-by-size.
That is, when you setunion two disjoint sets, the smaller (in terms of number of nodes) should point at the larger.
This function works as described in lecture, except that you should not assume that the arguments to setunion are roots of existing uptrees.
Your setunion function SHOULD find the roots of its arguments before combining the trees.
If the two sets are the same size, make the tree containing the second argument point to the tree containing the first. (Note that normally we could break this tie arbitrarily, but in this case we want to control things for grading.)
@Parameters:
    a	Index of the first element to union
    b	Index of the second element to union
*/

//union by size
void DisjointSets::setunion (int a, int b)
{
  // find root of a and b
  int first = find(a);
  int second = find(b);
  // get the new size
  int size = elements[first] + elements[second];

  // point smaller one to larger one
  if(elements[first] > elements[second])
	{
		elements[first] = second;
		elements[second] = size;
	}

	else
	{
		elements[second] = first;
		elements[first] = size;
	}
}
