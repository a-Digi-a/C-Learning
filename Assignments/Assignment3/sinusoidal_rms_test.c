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

void sineRMS(double v_pp, double dc_offset) {
  double v_peak = v_pp / 2.0;
  // create array containing 20 double values
  double sineArr[20];
  // populate the array with a for loop
  for (int i = 0; i < 20; i++) {
    sineArr[i] = v_peak * sin(2.0 * M_PI * i / 20.0) + dc_offset;
  }
  // calculate RMS using the function
  double RMS = arrayRMS(sineArr, 20);
  // calculate RMS using the formula given
  double theory_RMS = sqrt(pow(dc_offset, 2) + (pow(v_peak, 2) / 2));
  // print values
  printf(
      "Peak to Peak Sine Voltage: %f\nDC Offset: %f\nArray RMS Value: %f\nTheory RMS Value: %f\n",
      v_pp, dc_offset, RMS, theory_RMS);
}

int main() { sineRMS(3, 1); }
