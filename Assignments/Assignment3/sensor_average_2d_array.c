#include <stdio.h>

void sensorAverages(int m, int n, const double readings[m][n],
                    double averages[m]) {
  // temp variable to store the added values of each row
  double temp = 0;
  // loop  over each row
  for (int i = 0; i < m; i++) {
    // loop over each column
    for (int j = 0; j < n; j++) {
      // add each value in a row together
      temp += readings[i][j];
    }
    // put the average of each row in the average array
    averages[i] = temp / (n + 1);
    // reset the temp variable for next loop
    temp = 0;
  }
}

void test_sensors() {
  double array[3][3] = {{2.3, 4.5, 1.2}, {7.1, 2.4, 1.4}, {3.5, 8.9, 0.7}};
  double average_array[3];
  sensorAverages(3, 3, array, average_array);

  printf("Averages:\n");
  for (int i = 0; i < 3; i++) {
    printf("Row %i: %f\n", i, average_array[i]);
  }
}

int main() { test_sensors(); }
