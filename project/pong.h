#ifndef _PONG_
#define _PONG_

typedef struct Player {
  char prev_x;
  char prev_y;
  char pos_x;
  char pos_y;
  char vel;
  unsigned char score;
} Player;

typedef struct Ball {
  char prev_x;
  char prev_y;
  char pos_x;
  char pos_y;
  char vel_x;
  char vel_y;
} Ball;

extern Player p1, p2;
extern Ball ball;

char canMove(unsigned char player, signed char vel);

char withinBounds();

char outOfBounds();

char detectCollision();

void setVelocity(unsigned char player, char vel);

void setBallVelocity(char vel_x, char vel_y);

void setScore(unsigned char player, unsigned char score);

void addScore(unsigned char player);

void resetPosition();

#endif
