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
  // x axis of graph is from 35 to 975
  // y axis of graph is from 30 to 770
  gd_resetCanvasSize(1000, 800);
  gd_setCanvasColor(BLACK);
  gd_setPenColor(GRAY);
  gd_quad(35, 30, 975, 30, 975, 770, 30, 770);
  gd_setTextColor(WHITE);
  gd_setTextSize(11);
  gd_setFont(Arial);
  gd_text("0%", 10, 765);
  gd_text("100%", 5, 35);
  gd_text("0V", 35, 785);
  gd_text("3.3V", 960, 785);
  gd_setTextSize(14);
  gd_text("Sensor Transfer Characteristic", 400, 15);

  // Draw data
  gd_setPenColor(WHITE);
  // x axis scales i to the 940 pixel width of the graph then offsets it by 30
  // to make it fit y axis scales the sensor percentage to the 740 pixel height
  // of the graph then takes it away from 770 to make it fit
  for (double i = 0.0; i < 3.3; i = i + 0.01) {
    gd_line((((i / 3.3) * 940) + 30),
            (770 - ((sensor_percentage(i) / 100.0) * 740)),
            ((((i + 0.01) / 3.3) * 940) + 30),
            (770 - ((sensor_percentage(i) / 100.0) * 740)));
  }

  gd_save("sensor_graph");
}

int main() {
  double voltage = 2;
  int percentage = sensor_percentage(voltage);
  printf("%f scaled is: %i\n", voltage, percentage);
  draw_sensor_graph();
}
