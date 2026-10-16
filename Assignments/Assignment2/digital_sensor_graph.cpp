#include "GeoDraw.h"
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

static void draw_trace(const double top, const double spacing,
                       const double height, unsigned char row, double x0,
                       double x1, int frame, unsigned char sx,
                       unsigned char sx_old) {
  // calculate the top and bottom of the trace
  double low = top + row * spacing + height;
  double high = low - height;
  // calculate both the old and new heights of the trace
  double y0 = sx ? high : low;
  double y1 = sx_old ? high : low;

  // draw vertical line (not on first frame as their is no previous value to
  // draw from)
  if (frame > 0 && sx != sx_old) {
    gd_line(x0, y0, x0, y1);
  }
  // draw horizontal line
  gd_line(x0, y0, x1, y0);
}

void animate_sensors() {
  // declare variables for calculations and plotting
  static const double left = 80, dx = 4, top = 120, spacing = 140, height = 50;
  const int total_frames = 200;
  static unsigned char s;
  unsigned char s0 = 0, s1 = 0, s2 = 0, s3 = 0, sAND = 0, s0_old = 0,
                s1_old = 0, s2_old = 0, s3_old = 0, sAND_old = 0;

  // draw background and text for graph
  gd_resetCanvasSize(900, 800);
  gd_setCanvasColor(BLACK);
  gd_setTextColor(WHITE);
  gd_setTextSize(18);
  gd_setFont(Arial);
  gd_text("S0", left - 40, top + 20);
  gd_text("S1", left - 40, top + 20 + spacing);
  gd_text("S2", left - 40, top + 20 + spacing * 2);
  gd_text("S3", left - 40, top + 20 + spacing * 3);
  gd_text("AND", left - 40, top + 20 + spacing * 4);
  gd_text("Four Noisy Digital Sensors and Four-Input AND", 250, 30);

  // loop over frames
  for (int frame = 0; frame < total_frames; frame++) {
    // get sensor values and extract each into its own variable
    s = sensor_simulator();
    s0 = (s & (1 << 0)) >> 0;
    s1 = (s & (1 << 1)) >> 1;
    s2 = (s & (1 << 2)) >> 2;
    s3 = (s & (1 << 3)) >> 3;
    sAND = s0 && s1 && s2 && s3;

    // get x values for current frame (current and previous to draw a line)
    double x0 = left + frame * dx;
    double x1 = x0 + dx;

    // call function to draw the traces (all variables are needed, would
    // probably use #define but we havent covered that) also set colours before
    // each traces function
    gd_setPenColor(LIGHT_BLUE);
    draw_trace(top, spacing, height, 0, x0, x1, frame, s0, s0_old);
    gd_setPenColor(YELLOW);
    draw_trace(top, spacing, height, 1, x0, x1, frame, s1, s1_old);
    gd_setPenColor(PINK);
    draw_trace(top, spacing, height, 2, x0, x1, frame, s2, s2_old);
    gd_setPenColor(ORANGE);
    draw_trace(top, spacing, height, 3, x0, x1, frame, s3, s3_old);
    gd_setPenColor(GREEN);
    draw_trace(top, spacing, height, 4, x0, x1, frame, sAND, sAND_old);

    // store the value of the current frame before the next loop (so it can be
    // used for the lines)
    s0_old = s0;
    s1_old = s1;
    s2_old = s2;
    s3_old = s3;
    sAND_old = sAND;

    // pause to make it animated
    gd_pause(50);
  }
  // save graph
  gd_save("noisy_sensor_graph.html");
}

int main() { animate_sensors(); }
