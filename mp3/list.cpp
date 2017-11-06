/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
#include <iostream>
template <class T>
List<T>::~List()
{
  clear();
    /// @todo Graded in MP3.1
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
  ListNode* he = this->head;
  // loop until NULL
  while (he != NULL)
  {
    head = head->next;
    // delete head
    delete he;
    he = head;
  }
    tail = NULL;
    head = NULL;
    /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
  ListNode* newNode = new ListNode(ndata);
  // if length == 0, node become head and tail
  if (length == 0)
  {
    head = newNode;
    tail = newNode;
  }
  else
  {
    head -> prev = newNode;
    newNode -> next = head;
    head = newNode;
    newNode -> prev = NULL;
  }
  // increase length
  length ++;
    /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
  ListNode* nNode = new ListNode(ndata);
  // if length == 0, ndata become head and tail
  if (length == 0)
  {
    this -> tail = nNode;
    this -> head = nNode;
  }
  else
  {
    tail -> next = nNode;
    nNode -> prev = tail;
    tail = nNode;
    nNode = NULL;
  }
  length++;
    /// @todo Graded in MP3.1
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
  if (startPoint == endPoint || startPoint == NULL || endPoint == NULL || length <= 1)
    return;
    // store in case we need later
  ListNode* current = endPoint->prev;
  ListNode* end = endPoint;
  ListNode* temp = NULL;
  ListNode* start = startPoint->prev;
  ListNode* endnext = endPoint->next;
  startPoint = endPoint;
  // reverse the whole list
  while (current != start)
  {
    endPoint->next = current;
    current = current->prev;
    endPoint->next->prev = endPoint;
    endPoint = endPoint->next;
  }
  startPoint->prev = start;
  endPoint->next = endnext;
  // in case head -> prev and end->next is NULL
  if (start != NULL)
  {
    start->next = startPoint;
  }
  if (endnext != NULL)
  {
    endnext->prev = endPoint;
  }

    /// @todo Graded in MP3.1
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)////does not work for backward
{
  if (length <= 1 || head == tail || head == NULL || tail == NULL || n == 0)
    return;
  ListNode* startPoint = head;
  ListNode* endpoint = NULL;
  ListNode* start = head;
  ListNode* temp = head;
  while (startPoint != NULL)
  {
    temp = startPoint;
    for (int i=1; i<n; ++i)
    {
      if (temp->next != NULL)
      temp = temp->next;
    }
    reverse(startPoint,temp);
    if (startPoint->prev == NULL)
    {
        head = startPoint;
    }
    startPoint = temp->next;
  }
  tail = temp;

    /// @todo Graded in MP3.1
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
  if (head == tail || head == NULL || tail == NULL || length==0) return;
  ListNode* temp;
  ListNode* current= head;
  while (current->next != tail && current->next->next != NULL)
  {
    temp = current->next;
    // remove from list
    current->next = temp->next;
    current->next->prev=current;
    // append to the tail
    tail->next = temp;
    temp->prev = tail;
    temp->next = NULL;
    tail = temp;
    current = current->next;
  }
    /// @todo Graded in MP3.1
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    /// @todo Graded in MP3.2
    ListNode* startpoint =  start;

    for (int i=0; i < splitPoint; i++)
    {
      if (start == NULL) return NULL;
      start = start->next;
    }
    // set up the previous and next node
    start->prev->next = NULL;
    start->prev = NULL;
    return start; // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    if (first == NULL) return second;
    if (second == NULL) return first;
    ListNode* fnode = first;
    ListNode* snode = second;
    ListNode* node = NULL;
    ListNode* previous = NULL;
    // compare the data values of two lists
    if ((fnode->data) < (snode->data))
    {
      node = fnode;
      fnode = fnode->next;
    }
    else
    {
      node = snode;
      snode = snode->next;
    }
    head = node;
    while (fnode != NULL && snode != NULL)
    {
      if (fnode->data < snode->data)
      {
          node->next = fnode;
          fnode->prev = node;
          fnode = fnode->next;
      }
      else{
        node->next = snode;
        snode->prev = node;
        snode = snode->next;
      }
      node = node->next;
    }
    if (fnode != NULL)
    {
      node->next = fnode;
      fnode->prev = node;
    }
    if (snode != NULL)
    {
      node->next = snode;
      snode->prev = node;
    }
    while (node->next != NULL)
    {
      node = node->next;
    }
    tail = node;
    node = head;

    /// @todo Graded in MP3.2
    return node; // change me!
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    if (chainLength <= 1)
      return start;
    int mid = chainLength/2;
    ListNode* list;
    ListNode* right;
    // split from middle
    right = split(start, mid);
    start = mergesort(start,mid);
    right = mergesort(right,chainLength-mid);
    // merge back two lists
    list = merge(start,right);
    /// @todo Graded in MP3.2
    return list; // change me!
}
