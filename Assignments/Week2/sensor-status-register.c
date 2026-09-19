#include <stdio.h>

int find_bit_value(unsigned char status, int position) {
  unsigned int bit_mask = 1 << position;
  int bit;
  bit = status & bit_mask;
  bit = bit >> position;
  return bit;
}

int find_range(int bit0, int bit1, int bit2, int bit3) {
  // add range bits together
  int range = (bit0 * 1) + (bit1 * 2) + (bit2 * 4) + (bit3 * 8);
  return range;
}

void print_bit_values(int range, int bit4, int bit5, int bit6, int bit7,
                      unsigned int status) {
  // multiple print statements to keep the code readable
  printf("%-16s: 0x%x\n", "Status Register", status);
  printf("%-16s: %i\n", "Sensor fault", bit7);
  printf("%-16s: %i\n", "Over-temperature", bit6);
  printf("%-16s: %i\n", "Data ready", bit5);
  printf("%-16s: %i\n", "Battery low", bit4);
  printf("%-16s: %i\n", "Range", range);
}

int main() {
  unsigned char status = 0xB5;
  // I would use a for loop or something similar but we havent done that yet

  // bit 0 to 3 are range
  int bit0 = find_bit_value(status, 0);
  int bit1 = find_bit_value(status, 1);
  int bit2 = find_bit_value(status, 2);
  int bit3 = find_bit_value(status, 3);
  int range = find_range(bit0, bit1, bit2, bit3);
  // bit 4 battery low
  int bit4 = find_bit_value(status, 4);
  // bit 5 data ready
  int bit5 = find_bit_value(status, 5);
  // bit 6 over-temperature
  int bit6 = find_bit_value(status, 6);
  // bit 7 sensor fault
  int bit7 = find_bit_value(status, 7);
  print_bit_values(range, bit4, bit5, bit6, bit7, status);
}
