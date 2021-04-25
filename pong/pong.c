#include <msp430.h>
#include "lcdutils.h"
#include "pong.h"

struct Player p1, p2;
struct Ball ball;

char canMove(unsigned char player, signed char vel) {
  switch (player) {
  case 1:
    return vel > 0 ? p1.pos_y < screenHeight - 50 : p1.pos_y > 0;
  case 2:
    return vel > 0 ? p2.pos_y < screenHeight - 50 : p2.pos_y > 0;
  }
}

char withinBounds() {
  return (ball.pos_x > 0 && ball.pos_x < screenWidth);
}

char detectCollision() {
  if (ball.pos_y <= 0)
    return 1; // Collision with top of screen
  else if (ball.pos_y >= screenHeight - 5)
    return 2; // Collision with bottom of screen
  else if (ball.pos_x == p1.pos_x && (ball.pos_y > p1.pos_y && ball.pos_y < p1.pos_y + 50))
    return 3; // Collision with p1
  else if (ball.pos_x == p2.pos_x && (ball.pos_y > p2.pos_y && ball.pos_y < p2.pos_y + 50))
    return 4; // Collision with p2
  return 0;
}

void setVelocity(unsigned char player, char vel) {
  switch (player) {
  case 1:
    p1.vel = vel;
    p1.prev_y = p1.pos_y;
    p1.pos_y += vel;
    break;
  case 2:
    p2.vel = vel;
    p2.prev_y = p2.pos_y;
    p2.pos_y += vel;
    break;
  default:
    break;
  }
}

void setBallVelocity(char vel_x, char vel_y) {
  ball.vel_x = vel_x;
  ball.prev_x = ball.pos_x;
  ball.pos_x += vel_x;

  ball.vel_y = vel_y;
  ball.prev_y = ball.pos_y;
  ball.pos_y += vel_y;
}

void setScore(unsigned char player, unsigned char score) {
  switch (player) {
  case 1:
    p1.score = score;
    break;
  case 2:
    p2.score = score;
    break;
  default:
    break;
  }
}

void resetPosition() {
  p1.pos_x = 5;
  p1.pos_y = (screenHeight / 2) - 25;

  p1.prev_x = p1.pos_x;
  p1.prev_y = p1.pos_y;
  
  p2.pos_x = (screenWidth - 10);
  p2.pos_y = (screenHeight / 2) - 25;

  p2.prev_x = p2.pos_x;
  p2.prev_y = p2.pos_y;
  
  ball.pos_x = (screenWidth / 2) - 5;
  ball.pos_y = (screenHeight / 2) - 5;

  ball.prev_x = ball.pos_x;
  ball.prev_y = ball.pos_y;
}
