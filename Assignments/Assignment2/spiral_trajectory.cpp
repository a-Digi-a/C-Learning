#include "GeoDraw.h"
#include <math.h>

void draw_spiral(double radius, double rotation_rate, double radius_factor) {
  const double cx = 250;
  const double cy = 250;
  const double PI = acos(-1);
}

int main() {
  gd_resetCanvasSize(500, 500);
  gd_setCanvasColor(BLACK);
  gd_setPenColor(WHITE);
  gd_circleFilled(250, 250, 3);
  gd_setPenColor(GREEN);
  draw_spiral(50, 1.0, 1.2);
  gd_save("spiral");
}
