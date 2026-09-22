#include <stdio.h>

void print_ascii_readout_display(double voltage, double current, int channel) {
  printf("+----------------------------+\n%-8c%-21s%c\n%-8c%-21s%c\n%-29c%c\n%-"
         "2c%s%-17i%c\n%-2c%s%-11.3f%-6c%c\n%-2c%s%-11.3f%-6c%c\n+-------------"
         "---------------+\n",
         '|', "SENSOR MONITOR", '|', '|', "INPUT \\ ADC", '|', '|', '|', '|',
         "Channel : ", channel, '|', '|', "Voltage : ", voltage, 'V', '|', '|',
         "Current : ", current, 'A', '|');
}

int main() {
  double voltage = 2.735;
  double current = 0.418;
  int channel = 3;
  print_ascii_readout_display(voltage, current, channel);
}
