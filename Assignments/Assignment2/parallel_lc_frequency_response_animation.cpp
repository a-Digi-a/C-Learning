#include "GeoDraw.h"
#include <math.h>

double calculate_parallel_lc_voltage(double R, double L, double C, double f) {
  double B = (2 * PI * f * C) - (1 / (2 * PI * f * L));
  double V = 1 / (sqrt(1 + (pow(R, 2) * pow(B, 2))));
  return V;
}

void draw_frequency_response(double R, double L, double C, double f_start,
                             double f_end) {
  static const double left = 60, right = 740, top = 60, bottom = 450,
                      PI = acos(-1);
  const int total_points = 200;

  // find and save units
  double divisor;
  int unit; // 0 is Hz, 1 is kHz, 2 = MHz

  if (f_end >= 1e6) {
    divisor = 1e6;
    unit = 2;
  } else if (f_end >= 1e3) {
    divisor = 1e3;
    unit = 1;
  } else {
    divisor = 1.0;
    unit = 0;
  }

  // label for the correct unit
  switch (unit) {
  case 0:
    gd_text("Frequency (Hz)", 350, bottom + 35);
    break;
  case 1:
    gd_text("Frequency (kHz)", 350, bottom + 35);
    break;
  case 2:
    gd_text("Frequency (MHz)", 350, bottom + 35);
    break;
  }

  // labels for the numbers themselves
  gd_text("0 Vpp", left - 40, bottom - 5);
  gd_text("1 Vpp", left - 40, top + 5);
  gd_text(gd_to_string(f_start / divisor, 3), left - 10, bottom + 20);
  gd_text(gd_to_string(f_end / divisor, 3), right - 15, bottom + 15);
  // draw axis
  gd_setPenColor(GRAY);
  gd_line(left, top, left, bottom);
  gd_line(left, bottom, right, bottom);

  double frequency_hz = 1.0 / (2.0 * PI * sqrt(L * C));
  double x_frequency =
      left + (frequency_hz - f_start) / (f_end - f_start) * (right - left);

  // draw curve
  gd_setPenColor(PINK);
  double prev_x = 0, prev_y = 0;
  for (int i = 0; i < total_points; i++) {
    double f = f_start + i * (f_end - f_start) / (total_points - 1);
    double v = calculate_parallel_lc_voltage(R, L, C, f);
    double x = left + (f - f_start) / (f_end - f_start) * (right - left);
    double y = bottom - v * (bottom - top);
    if (i > 0) {
      gd_line(prev_x, prev_y, x, y);
    }
    prev_x = x;
    prev_y = y;
  }

  // draw resonance line and label
  gd_setPenColor(GREEN);
  gd_line(x_frequency, bottom, x_frequency, top);
  gd_text(gd_to_string(frequency_hz / divisor, 3), x_frequency - 15,
          bottom + 15);
}

void animate_lc_response() {
  // declare variables for the calculation
  const double R = 1000.0;
  const double L = 2e-6;
  const double c_min = 10e-12;
  const double c_max = 100e-12;
  const double f_start = 5e6;
  const double f_end = 45e6;
  const int frames = 100;

  // size canvas
  gd_resetCanvasSize(800, 500);

  for (int frame = 0; frame < frames; frame++) {
    // draw canvas and title
    gd_setCanvasColor(BLACK);
    gd_setTextColor(WHITE);
    gd_setTextSize(18);
    gd_setFont(Arial);
    gd_text("Parallel LC Frequency Response", 250, 30);
    gd_setTextSize(12);

    double C = c_min + frame * (c_max - c_min) / (frames - 1);

    draw_frequency_response(R, L, C, f_start, f_end);

    // label for current capacitance
    gd_setTextColor(WHITE);
    gd_text("C =", 600, 80);
    gd_text(gd_to_string(C * 1e12), 630, 80);
    gd_text("pF", 680, 80);

    gd_pause(50);
    // make it so the graph doesnt dissapear after the last frame
    if (frame < frames - 1) {
      gd_clear();
    }
  }
  gd_save("parallel_lc_frequency_response_animation.html");
}

int main() { animate_lc_response(); }
