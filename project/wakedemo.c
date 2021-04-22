#include <msp430.h>
#include <libTimer.h>
#include <stdio.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buttons.h"
#include "pong.h"
#include "color.h"

#define LED_GREEN BIT6             // P1.6

char score[32];
short redrawScreen = 1;
u_int shapeFgColor = COLOR_ORANGE;

void collision_handler() {
  char collision = detectCollision();
  switch (collision) {
  case 1: // Collision with top of screen 
    if (ball.vel_x > 0)
      setBallVelocity(1, 1);
    else 
      setBallVelocity(-1, 1);
    break;
  case 2: // Collision with bottom of screen
    if (ball.vel_x > 0)
      setBallVelocity(1, -1);
    else
      setBallVelocity(-1, -1);
    break;
  case 3: // Collision with player 1
    if (p1.vel > 0)
      setBallVelocity(1, 1);
    else
      setBallVelocity(1, -1);
    break;
  case 4: // Collision with player 2
    if (p2.vel > 0)
      setBallVelocity(-1, 1);
    else
      setBallVelocity(-1, -1);
    break;
  default:
    setBallVelocity(ball.vel_x, ball.vel_y);
    break;
  }
}

void wdt_c_handler()
{
  static char secCount = 0;
  static char dsecCount = 0;
  
  secCount ++;
  dsecCount ++;
  if (secCount == 250) { /* once/sec */
    secCount = 0;
    redrawScreen = 1;
  }
  if (dsecCount == 25) {
    dsecCount = 0;
    collision_handler();
    if (withinBounds()) {
      if (button_pressed(1)) {
	if (canMove(1, -5)) {
	  setVelocity(1, -5);
	  redrawScreen = 1;
	}
      }
      if (button_pressed(2)) {
	if (canMove(1, 5)) {
	  setVelocity(1, 5);
	  redrawScreen = 1;
	}
      }	
      if (button_pressed(3)) {
	if (canMove(2, -5)) {
	  setVelocity(2, -5);
	  redrawScreen = 1;
	}
      }
      if (button_pressed(4)) {
	if (canMove(2, 5)) {
	  setVelocity(2, 5);
	  redrawScreen = 1;
	}
      }
    } else {
      resetPosition();
      redrawScreen = 1;
    }
  }
}
  

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */

  setScore(1, 0);
  setScore(2, 0);

  setBallVelocity(1, -1);
  resetPosition();
  clearScreen(COLOR_BLUE);
  sprintf(score, "Score: %i - %i", p1.score, p2.score);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      color_handler();
      fillRectangle(ball.pos_x, ball.pos_y, 5, 5, shapeFgColor); // Ball
      fillRectangle(p1.pos_x, p1.pos_y, 5, 50, shapeFgColor);    // Player 1
      fillRectangle(p2.pos_x, p2.pos_y, 5, 50, shapeFgColor);    // Player 2
      drawString5x7((screenWidth / 2) - 35, (screenHeight / 2) - 65, score, COLOR_ORANGE, COLOR_BLUE);
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    



