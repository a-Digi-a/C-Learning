#include "GeoDraw.h"
#include <stdlib.h>
#include <time.h>
// Define Constants
#define CANVAS_WIDTH 700
#define CANVAS_HEIGHT 500
#define PARTICLE_RADIUS 5
#define TIME_STEP 0.01
#define FRAME_AMOUNT 500
#define PARTICLE_COUNT 25
#define MIN_SPEED 100.0
#define MAX_SPEED 300.0

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

// Function to get a random number between a range
double randRange(double low, double high) {
  return low + (high - low) * rand() / RAND_MAX;
}

void initialiseParticles(Particle particles[], int n) {
  for (int i = 0; i < n; i++) {
    // get a random x and y coordinate
    particles[i].x = randRange(PARTICLE_RADIUS, CANVAS_WIDTH - PARTICLE_RADIUS);
    particles[i].y =
        randRange(PARTICLE_RADIUS, CANVAS_HEIGHT - PARTICLE_RADIUS);
    // gets a speed between min and max speed then either multiplies it by 1 or
    // -1 to randomise it being positive or negative
    particles[i].vx = randRange(MIN_SPEED, MAX_SPEED) * (rand() % 2 ? 1 : -1);
    particles[i].vy = randRange(MIN_SPEED, MAX_SPEED) * (rand() % 2 ? 1 : -1);
    // random colours, dont start from 0 to make sure they are not too dark so
    // you can see on the black background
    particles[i].colour.r = randRange(0.3, 1.0);
    particles[i].colour.g = randRange(0.3, 1.0);
    particles[i].colour.b = randRange(0.3, 1.0);
  }
}

void stepSimulation(Particle particles[], int n) {
  // loops over each particle in the array and steps it
  for (int i = 0; i < n; i++) {
    stepParticle(&particles[i], TIME_STEP);
  }
}

void checkCollisions(Particle particles[], int n) {
  // minimum distance between particles
  double minDistance = 2 * PARTICLE_RADIUS;
  // loop over each particle
  for (int i = 0; i < n - 1; i++) {
    // loop over each particle to the right of currently selected particle to
    // not have particles be checked twice
    for (int j = i + 1; j < n; j++) {
      // get difference in position of particles
      double dx = particles[j].x - particles[i].x;
      double dy = particles[j].y - particles[i].y;
      // calculate the distance between the particles
      double distance = hypot(dx, dy);

      // check if they are colliding, distance > 0 is there to prevent a divide
      // by 0
      if (distance < minDistance && distance > 0) {
        // reverse the particles velocities
        particles[i].vx = -particles[i].vx;
        particles[i].vy = -particles[i].vy;
        particles[j].vx = -particles[j].vx;
        particles[j].vy = -particles[j].vy;

        // gets the overlap of the particles and adds a little extra to push
        // away to prevent buggy behaviour when rounding
        double push = (minDistance - distance) / 2 + 0.01;
        // push the particles apart
        particles[i].x -= dx / distance * push;
        particles[i].y -= dy / distance * push;
        particles[j].x -= dx / distance * push;
        particles[j].y -= dy / distance * push;
      }
    }
  }
}

void runParticleChamberSimulation() {
  // set up canvas
  gd_resetCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
  gd_setCanvasColor(BLACK);
  gd_clear();

  // create particles
  Particle particles[PARTICLE_COUNT];
  srand(time(NULL));
  initialiseParticles(particles, PARTICLE_COUNT);

  // draw frames
  for (int frame = 0; frame < FRAME_AMOUNT; frame++) {
    gd_clear();
    stepSimulation(particles, PARTICLE_COUNT);
    checkCollisions(particles, PARTICLE_COUNT);
    drawParticles(particles, PARTICLE_COUNT);
    gd_pause(TIME_STEP * 1000);
  }
  // save html file
  gd_save("q9particles.html");
}

int main() { runParticleChamberSimulation(); }
