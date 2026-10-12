#include <stdio.h>

double get_median_value(double num1, double num2, double num3) {
  // check if num2 is median
  if (((num1 <= num2) <= num3) || ((num3 <= num2) <= num1)) {
    return num2;
  }
  // check if num1 is median
  else if (((num2 <= num1) <= num3) || (num3 <= num1) <= num2) {
    return num1;
  }
  // if not num1 or num2 it has to be num3
  return num3;
}

int main() {
  double num1 = 4.1;
  double num2 = 1.5;
  double num3 = 3.2;
  double median = get_median_value(num1, num2, num3);
  printf("The median of {%f, %f, %f} is: %f\n", num1, num2, num3, median);
}
