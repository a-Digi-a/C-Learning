#include <stdio.h>

void countEvents() {
  static int count = 0;
  ++count;
  printf("Count: %i\n", count);
}

int main() {
  for (int i = 0; i < 5; ++i) {
    countEvents();
  }
}
