#include <stdio.h>

void calculate_and_print_power(double voltage, double current) {
  double power = voltage * current;
  // Seperate print statements for readability
  printf("%-10s%-5.2f V\n", "Voltage:", voltage);
  printf("%-10s%-5.2f A\n", "Current:", current);
  printf("%-10s%-5.2f W\n", "Power:", power);
}

int main() {
  double voltage = 12.00;
  double current = 1.25;
  calculate_and_print_power(voltage, current);
}
