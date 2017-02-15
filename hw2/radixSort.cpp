#include "sort.h"
#include <vector>

using namespace std;

int getLargest(vector <int> &v) {
  int largest = v[0];
  for (int i = 0; i < v.size(); i++) {
    if (v[i] > largest)
      largest = v[i];
  }
  return largest;
}

void combine(int * v, int size, int digit) {
  vector<int> bucket(size, 0); // init new vector with the same size
  int counter = 0;

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < size; j++) {
      if ((v[j] / digit) % 10 == i) {
        bucket[counter] = v[j]; // add number to bucket
        counter++;
      }
    }
  }
  for(int idx = 0; idx < size; idx++)
    // copy our bucket back to our vector
    v[idx] = bucket[idx];
}

void radixSort(vector<int> &v)
{
  int largest = getLargest(v); // get the largest number
  vector<int> bucket;

  for (int digit = 1; largest/digit > 0; digit *= 10) { // divide by the correct digit every cycle
    combine(&v[0], v.size(), digit);
  }
}
