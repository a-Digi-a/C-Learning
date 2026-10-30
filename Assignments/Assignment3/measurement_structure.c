#include <stdio.h>

struct Measurement {
  char name[19];
  double value;
  double uncertainty;
};
typedef struct Measurement Measurement;

void printMeasurement(const Measurement *m) {
  printf("%s = %.3f +/- %.3f\n", m->name, m->value, m->uncertainty);
}

void measurement_test() {
  const Measurement measurement1 = {"Voltage", 3.3, 0.01};
  printMeasurement(&measurement1);
}

int main() { measurement_test(); }
