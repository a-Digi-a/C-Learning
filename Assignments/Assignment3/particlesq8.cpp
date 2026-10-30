#include "GeoDraw.h"
// Define Constants
#define CANVAS_WIDTH 700
#define CANVAS_HEIGHT 500
#define PARTICLE_RADIUS 5
#define TIME_STEP 0.01
#define FRAME_AMOUNT 500

// Make structs
struct Colour {
  double r;
  double g;
  double b;
};
typedef struct Colour Colour;

struct Particle {
  double x;
  double y;
  double vx;
  double vy;
  Colour colour;
};
typedef struct Particle Particle;

void stepParticle(Particle *p, double dt) {
  // step the particles
  p->x += p->vx * dt;
  p->y += p->vy * dt;

  // Bounce off left and right walls
  if (p->x < PARTICLE_RADIUS) {
    p->x = PARTICLE_RADIUS;
    p->vx = -p->vx;
  } else if (p->x > CANVAS_WIDTH - PARTICLE_RADIUS) {
    p->x = CANVAS_WIDTH - PARTICLE_RADIUS;
    p->vx = -p->vx;
  }

  // Bounce off top and bottom walls
  if (p->y < PARTICLE_RADIUS) {
    p->y = PARTICLE_RADIUS;
    p->vy = -p->vy;
  } else if (p->y > CANVAS_HEIGHT - PARTICLE_RADIUS) {
    p->y = CANVAS_HEIGHT - PARTICLE_RADIUS;
    p->vy = -p->vy;
  }
}

void drawParticles(const Particle particles[], int n) {
  for (int i = 0; i < n; i++) {
    gd_setFillColor(particles[i].colour.r, particles[i].colour.g,
                    particles[i].colour.b);
    gd_circleFilled(particles[i].x, particles[i].y, PARTICLE_RADIUS);
  }
}

void particleTest() {
  // draw canvas
  gd_resetCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
  gd_setCanvasColor(BLACK);
  gd_clear();
  // make particle structs and array
  Particle particle1 = {265, 123, 300, 250, {1.0, 0.0, 0.0}};
  Particle particle2 = {400, 456, -250, -200, {0.0, 1.0, 0.0}};
  Particle pArray[] = {particle1, particle2};

  // loop over every frame and draw the particles then step the particles
  for (int i = 0; i < FRAME_AMOUNT; i++) {
    gd_clear();
    drawParticles(pArray, 2);
    gd_pause(TIME_STEP * 1000);
    for (int j = 0; j < 2; j++) {
      stepParticle(&pArray[j], TIME_STEP);
    }
  }
  // save the drawing
  gd_save("q8particles.html");
}

int main() { particleTest(); }
