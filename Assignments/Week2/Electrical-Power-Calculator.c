#include <stdio.h>

void calculate_and_print_power(double voltage, double current) {
  double power = voltage * current;
  printf("%-10s%-5.2f V\n%-10s%-5.2f A\n%-10s%-5.2f W\n", "Voltage:", voltage,
         "Current:", current, "Power:", power);
}

int main() {
  double voltage = 12.00;
  double current = 1.25;
  calculate_and_print_power(voltage, current);
}
