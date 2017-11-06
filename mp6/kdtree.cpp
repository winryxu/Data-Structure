/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    // check for boundary
    //if (curDim <= Dim && curDim >= 0)
    //{
      // if there is a tie
      if (first[curDim] == second[curDim]) return first < second;
      return first[curDim] < second[curDim];
    //}
    // else return false;
    /**
     * @todo Implement this function!
     */
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    int dis_p = 0;
    int dis_c = 0;
    for (int i = 0; i < Dim; i++)
    {
      dis_p += pow(potential[i] - target[i], 2);
      dis_c += pow(currentBest[i] - target[i], 2);
    }
    // dis_p = sqrt(dis_p);
    // dis_c = sqrt(dis_c);
    // no need to do square root, just compare
    if (dis_p != dis_c)
      return dis_p < dis_c;
    return potential < currentBest;
    /**
     * @todo Implement this function!
     */
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& target, int left, int right, int pivotIndex, int currDim)
{
  Point<Dim> pivot = target[pivotIndex];
  std::swap(target[pivotIndex],target[right]);
  int index = left;
  for (int i = left; i < right; i++)
  {
    if (smallerDimVal(target[i],pivot,currDim))
    {
      std::swap(target[index],target[i]);
      index++;
    }
  }
  std::swap(target[index],target[right]);
  return index;
}


template <int Dim>
int KDTree<Dim>::quickselect(vector<Point<Dim>>& target, int left, int right, int m, int currDim)
{
  if (left == right) return left;

  int pivotIndex = partition(target,left,right,(left+right)/2,currDim);
  if (pivotIndex > m)
  {
    return quickselect(target, left, pivotIndex - 1, m, currDim);
  }
  else if (pivotIndex < m)
  {
    return quickselect(target, pivotIndex + 1, right, m, currDim);
  }
  else return pivotIndex;
}



template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
  points = newPoints;

  buildtree(points,0,newPoints.size()-1,0);

    /**
     * @todo Implement this function!
     */
}

template <int Dim>
void KDTree<Dim>::buildtree(vector<Point<Dim>>& target, int left, int right, int currDim)
{
  if (left > right) return;
  int index = (right + left)/2;
  int pivot = quickselect(points,left,right,index,currDim);

  if (left < pivot)
    buildtree(target,left,index-1,(currDim+1)%Dim);
  if (right > pivot)
    buildtree(target,index+1,right,(currDim+1)%Dim);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     // check boundary
     if (points.size()>0)
     {
     Point<Dim> currentBest = points[(points.size()-1)/2];
     int currDim = 0;
     return findNeighborHelper(query,currentBest,0,points.size()-1,currDim);
   }
   return Point<Dim>();

}

template <int Dim>
Point<Dim> KDTree<Dim>::findNeighborHelper(const Point<Dim>& query,Point<Dim> currentBest,int left,int right, int currDim) const
{
  // it goes down to leaf node
  //if (left > right) return Point<Dim>();
  //cout<<points[(left+right)/2]<<endl;
  if (left >= right)
  {
    if (shouldReplace(query,currentBest,points[left]))
    {
      currentBest = points[left];
    }
    return currentBest;
  }

  //if it is not leaf node
  Point<Dim> best;
  int mid = (left+right)/2;
  // check direction
  if (smallerDimVal(points[mid],query,currDim))
  // go  right
    best = findNeighborHelper(query,currentBest,mid+1,right,(currDim+1)%Dim);
    // go left
  else best = findNeighborHelper(query,currentBest,left,mid-1,(currDim+1)%Dim);

  if (shouldReplace(query,currentBest,best))
  {
    //cout<<"here@!!!!!!!!!!!!!!!"<<endl;
    currentBest = best;
  }
  // whether it can be replaced
  if (shouldReplace(query,currentBest,points[mid]))
  {
    //cout<<"this one?????????????????"<<endl;
    currentBest = points[mid];
  }

  int distance = 0;
  int back_distance = 0;

  for (int i = 0; i<Dim; i++)
  {
    distance += pow(currentBest[i] - query[i], 2);
  }
  back_distance = pow(points[mid][currDim] - query[currDim], 2);
  //cout<<"checking distance  && node             "<< points[mid]<<endl;
  //check distance
  if (back_distance <= distance)
  {
    //if right side already checked
    if (smallerDimVal(points[mid],query,currDim))
    {
      best = findNeighborHelper(query,points[mid],left,mid-1,(currDim+1)%Dim);
    }
    //if left side already checked
    else best = findNeighborHelper(query,points[mid],mid+1,right,(currDim+1)%Dim);
  //  cout<<"current best: "<<currentBest<<endl;
  //  cout<<"best: "<<best<<endl;
  // check whether it can be replaced
    if (shouldReplace(query,currentBest,best))
    {
      //cout<<"       reach replace        "<<endl;
      currentBest = best;
    }
  }
//  cout<<"current return :      " <<currentBest<<endl;
  return currentBest;
}
