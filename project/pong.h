#ifndef _PONG_
#define _PONG_

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 120

extern char p1_pos_x, p1_pos_y;
extern char p2_pos_x, p2_pos_y;
extern char p1_vel, p2_vel;
extern unsigned char p1_score, p2_score;
extern char ball_pos_x, ball_pos_y;
extern char ball_vel_x, ball_vel_y;

char canMove(unsigned char player, char vel);

char withinBounds();

char detectCollision();

void setVelocity(unsigned char player, char vel);

void setBallVelocity(char vel_x, char vel_y);

void setScore(unsigned char player, unsigned char score);

void resetPosition();

#endif
