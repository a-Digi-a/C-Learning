#include "GeoDraw.h"
#include <math.h>

void draw_spiral(double radius, double rotation_rate, double radius_factor) {}

int main() {
  gd_resetCanvasSize(500, 500);
  gd_setCanvasColor(BLACK);
  gd_setPenColor(WHITE);
  gd_point(250, 250);
  gd_save("spiral");
}
