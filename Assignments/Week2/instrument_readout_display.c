#include <stdio.h>

void print_ascii_readout_display(double voltage, double current, int channel) {
  printf("+----------------------------+\n");
  printf("|%-10s%-10|\n", "SENSOR MONITOR");
  printf("|%-10s|\n");
  printf("|%-10s|\n");
}

int main() {
  double voltage = 2.735;
  double current = 0.418;
  int channel = 3;
  print_ascii_readout_display(voltage, current, channel);
}
