#include <stdio.h>

void calculate_and_print_power() {
  double voltage = 12.00;
  double current = 1.25;
  double power = voltage * current;
  printf("%-10s%-5.2f V\n%-10s%-5.2f A\n%-10s%-5.2f W\n", "Voltage:", voltage,
         "Current:", current, "Power:", power);
}

int main() { calculate_and_print_power(); }
