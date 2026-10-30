#include <math.h>
#include <stdio.h>

// RMS is the square root of: the square of each value / how many values there
// are
double arrayRMS(const double arr[], int length) {
  double numerator = 0;
  // add each element squared together
  for (int i = 0; i < length; i++) {
    numerator += pow(arr[i], 2);
  }
  // finish calculation (divide by length then sqrt it all)
  double RMS = sqrt(numerator / length);
  return RMS;
}

void testArrayRMS() {
  const double dArr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  // use pointer arithmetic to offset array by 5
  double testRMS = arrayRMS(dArr + 5, 5);
  printf("The RMS is: %f\n", testRMS);
}

int main() { testArrayRMS(); }
