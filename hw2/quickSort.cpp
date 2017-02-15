#include "sort.h"
#include <vector>
#include <iostream>

using namespace std;

int PivotList( int *list, int first, int last) {
  // first  the index of the first element
  // last   the index of the last element
  int PivotValue = list[ first ];
  int PivotPoint = first;
  for (int index = first + 1; index <= last; index++) {
    if (list[ index ] < PivotValue) {
      PivotPoint++;
      swap( list[ PivotPoint ], list[ index ]); // swap if the number is less than the pivot
    }
  }
  swap(list[first], list[PivotPoint]); // we know the value is less
  return PivotPoint;
}

void myqs(int *list, int first, int last) {
  if (first < last) {
    int pivot = PivotList(list, first, last);
    myqs(list, first, pivot - 1);
    myqs(list, pivot + 1, last);
  }
}

void quickSort(vector<int> &v) {
  myqs(&v[0], 0, v.size() - 1); // the books qs used a list, first, and last as pram's
}
