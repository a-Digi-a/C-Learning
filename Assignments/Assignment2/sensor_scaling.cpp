#include "GeoDraw.h"
#include <math.h>
#include <stdio.h>

int sensor_percentage(double voltage) {
  // 0.5 to 2.8V
  // take away .5 from top and bottom to make calculations easier
  int result = round(((voltage - 0.5) / (2.8 - 0.5)) * 100.0);

  // make sure result is from 0-100
  if (result > 100) {
    result = 100;
  } else if (result < 0) {
    result = 0;
  }
  return result;
}

void draw_sensor_graph() {
  // Draw graph
  // x axis of graph is from 30 to 970
  // y axis of graph is from 30 to 770
  gd_resetCanvasSize(1000, 800);
  gd_setCanvasColor(BLACK);
  gd_setPenColor(GRAY);
  gd_quad(30, 30, 970, 30, 970, 770, 30, 770);
  gd_setTextColor(WHITE);
  gd_setTextSize(12);
  gd_setFont(Arial);
  gd_text("0%", 10, 765);
  gd_text("0V", 35, 785);
  gd_text("3.3V", 960, 785);
  gd_save("sensor_graph");
}

int main() {
  double voltage = 2;
  int percentage = sensor_percentage(voltage);
  printf("%f scaled is: %i\n", voltage, percentage);
  draw_sensor_graph();
}
