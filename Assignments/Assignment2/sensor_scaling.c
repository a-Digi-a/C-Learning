#include <math.h>
#include <stdio.h>

int sensor_scaling(double voltage) {
  // 0.5 to 2.8V
  int result = round(voltage);
  return result;
}

int main() {
  double voltage = 2;
  int percentage = sensor_scaling(voltage);
  printf("%f scaled is: %i\n", voltage, percentage);
}
