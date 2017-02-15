#include "sort.h"
#include <vector>
#include <iostream>

using namespace std;

void insertionSort(vector<int> &v)
{
  // insert # into correct position
  for (int i = 1; i < v.size(); i++) {
    int newElement = v[i];
    int location = i - 1;
    // continue swaping while the left value is greater than the right
    while ((location >= 0) && (v[location] > newElement)) {
      v[location + 1] = v[location];
      location = location - 1;
    }
    v[location + 1] = newElement;
  }
}
