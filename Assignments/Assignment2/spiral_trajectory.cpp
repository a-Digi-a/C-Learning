#include "GeoDraw.h"
#include <math.h>

void draw_spiral(double radius, double rotation_rate, double radius_factor) {
  // draw canvas
  gd_resetCanvasSize(500, 500);
  gd_setCanvasColor(BLACK);
  gd_setPenColor(WHITE);
  gd_circleFilled(250, 250, 3);
  gd_setTextColor(WHITE);
  gd_setTextSize(14);
  gd_text("Spiral Trajectory", 200, 30);

  // variables to do calculations with
  const double cx = 250;
  const double cy = 250;
  const double PI = acos(-1);
  const int total_frames = 600;
  const int frames_per_revolution = 100;
  const double ms_per_frame = 1000.0 / (rotation_rate * frames_per_revolution);

  // calculate and draw spiral
  gd_setPenColor(GREEN);
  for (int frame = 0; frame < total_frames; ++frame) {
    double n = (double)frame / frames_per_revolution;
    double theta = 2.0 * PI * n;
    double r = radius * pow(radius_factor, n);

    double x = cx + r * cos(theta);
    double y = cy + r * -sin(theta);

    gd_point(x, y);
    gd_pause(ms_per_frame);
  }
  gd_save("spiral");
}

int main() { draw_spiral(20, 1.0, 1.5); }
