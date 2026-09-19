#include <stdio.h>

void print_ascii_readout_display(double voltage, double current, int channel) {
  printf("+----------------------------+\n");
  printf("%-8c%-21s%c\n", '|', "SENSOR MONITOR", '|');
  printf("%-8c%-21s%c\n", '|', "INPUT \\ ADC", '|');
  printf("%-29c%c\n", '|', '|');
  printf("%-2c%s%-17i%c\n", '|', "Channel : ", channel, '|');
  printf("%-2c%s%-11.3f%-6c%c\n", '|', "Voltage : ", voltage, 'V', '|');
  printf("%-2c%s%-11.3f%-6c%c\n", '|', "Current : ", current, 'A', '|');
  printf("+----------------------------+\n");
}

int main() {
  double voltage = 2.735;
  double current = 0.418;
  int channel = 3;
  print_ascii_readout_display(voltage, current, channel);
}
