#include <math.h>
#include <stdio.h>

double calculate_parallel_lc_voltage(double R, double L, double C, double f) {
  const double PI = acos(-1);
  double B = (2 * PI * f * C) - (1 / (2 * PI * f * L));
  double V = 1 / (sqrt(1 + (pow(R, 2) * pow(B, 2))));
  return V;
}

int main() {
  double resistor = 200;
  double inductor = 1 * pow(10, -6);
  double capacitor = 3 * pow(10, -6);
  double frequency = 100 * pow(10, 3);
  double voltage =
      calculate_parallel_lc_voltage(resistor, inductor, capacitor, frequency);
  printf("The Voltage is: %.6f\n", voltage);
}
