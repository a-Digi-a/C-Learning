#include <stdio.h>

void columnMaxima(int m, int n, const double readings[m][n], double maxima[n]) {
  // loop  over each column
  for (int j = 0; j < n; j++) {
    // set the initial value of maxima to the first row, so it will compare
    // properly if negative (instead of maxima[j] = 0)
    maxima[j] = readings[0][j];
    // loop over each row
    for (int i = 0; i < m; i++) {
      // check if the current number is greater than the current maxima
      if (readings[i][j] > maxima[j]) {
        // if it is make the current number the new maxima
        maxima[j] = readings[i][j];
      }
    }
  }
}

void test_maxima() {
  double array[3][3] = {{-2.3, 4.5, 1.2}, {-7.1, 2.4, 1.4}, {-3.5, 8.9, 0.7}};
  double maxima_array[3];
  columnMaxima(3, 3, array, maxima_array);

  printf("Maxima:\n");
  for (int i = 0; i <= 2; i++) {
    printf("Column %i: %.3f\n", i, maxima_array[i]);
  }
}

int main() { test_maxima(); }
