#include <stdio.h>

void adc_to_voltage(int adc_code) {
  double deltav = 3.3 / 4096;
  double low_voltage = deltav * adc_code;
  double high_voltage = deltav * (adc_code + 1);
  printf("ADC Code: %i\n", adc_code);
  printf("Voltage range: %f V <= Vin < %f V\n", low_voltage, high_voltage);
}

int main() {
  int adc_code = 2745;
  adc_to_voltage(adc_code);
}
