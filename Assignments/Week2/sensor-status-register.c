#include <stdio.h>

void decode_register(unsigned char status) {
  unsigned char range = (((1 << 0) & status) * 1) + (((1 << 1) & status) * 2) +
                        (((1 << 2) & status) * 4) + (((1 << 3) & status) * 8);
  unsigned char bit4 = (1 << 4) & status;
  unsigned char bit5 = (1 << 5) & status;
  unsigned char bit6 = (1 << 6) & status;
  unsigned char bit7 = (1 << 7) & status;

  printf("%-16s: 0x%x\n%-16s: %i\n%-16s: %i\n%-16s: %i\n%-16s: %i\n%-16s: %i\n",
         "Status Register", status, "Sensor fault", bit7, "Over-temperature",
         bit6, "Data ready", bit5, "Battery low", bit4, "Range", range);
}

int main() {
  unsigned char status = 0xB5;
  decode_register(status);
}
