#include <msp430.h>
#include "lcdutils.h"
#include "pong.h"

char p1_pos_x = 5;
char p1_pos_y = (screenHeight / 2) - 25;

char p2_pos_x = screenWidth - 10;
char p2_pos_y = (screenHeight / 2) - 25;

unsigned char p1_score = 0, p2_score = 0;

char ball_pos_x = (screenWidth / 2) - 5;
char ball_pos_y = (screenHeight / 2) - 5;

char canMove(unsigned char player, char vel) {
  switch (player) {
  case 1:
    return vel > 0 ? p1_pos_y < screenHeight - 50 : p1_pos_y > 0;
  case 2:
    return vel > 0 ? p2_pos_y < screenHeight - 50 : p2_pos_y > 0;
  }
}

void setVelocity(unsigned char player, char vel) {
  switch (player) {
  case 1:
    p1_pos_y += vel;
    break;
  case 2:
    p2_pos_y += vel;
    break;
  default:
    break;
  }
}

void setBallVelocity(char vel_x, char vel_y) {
  ball_pos_x += vel_x;
  ball_pos_y += vel_y;
}

void setScore(unsigned char player, unsigned char score) {
  switch (player) {
  case 1:
    p1_score = score;
    break;
  case 2:
    p2_score = score;
    break;
  default:
    break;
  }
}

void resetPosition() {
  p1_pos_x = 5;
  p1_pos_y = (screenHeight / 2) - 25;
  
  p2_pos_x = (screenWidth - 10);
  p2_pos_y = (screenHeight / 2) - 25;

  ball_pos_x = (screenWidth / 2) - 5;
  ball_pos_y = (screenHeight / 2) - 5;
}
