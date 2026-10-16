#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned char sensor_simulator() {
  static unsigned char sensors = 0;
  static unsigned char seeded = 0;

  // seeds from current time only if it hasnt before
  if (seeded == 0) {
    srand(time(NULL));
    seeded = 1;
  }

  // loop over each position in sensors
  for (int i = 0; i < 4; i++) {
    // 1 in 5 numbers are divisible by 5, so we can use that to tell wether to
    // flip a bit or not
    if (rand() % 5 == 0) {
      // XOR used to flip the bits
      sensors ^= 1 << i;
    }
  }
  return sensors;
}

int main() {
  // test 100 times then get the average of those tests to make sure it works
  unsigned int test = 0;
  unsigned char s = sensor_simulator();
  for (int i = 0; i < 100; i++) {
    printf("Sensor Values:%b\n", s);
    s = sensor_simulator();
    test += s;
  }
  test = test / 100;
  printf("test: %b\n", test);
}
