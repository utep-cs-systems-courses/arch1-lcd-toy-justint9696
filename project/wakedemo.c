#include <msp430.h>
#include <libTimer.h>
#include <stdio.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buttons.h"
#include "pong.h"

#define LED_GREEN BIT6             // P1.6

char collision = 0;
char score[32];
short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;


void wdt_c_handler()
{
  static int secCount = 0;
  static int dsecCount = 0;
  
  secCount ++;
  dsecCount ++;
  if (secCount == 250) { /* once/sec */
    secCount = 0;
    redrawScreen = 1;
  }
  if (dsecCount == 25) {
    dsecCount = 0;
    collision = detectCollision();
    switch (collision) {
    case 1: // Collision with top of screen 
      if (ball_vel_x > 0)
	setBallVelocity(1, 1);
      else 
	setBallVelocity(-1, 1);
      break;
    case 2: // Collision with bottom of screen
      if (ball_vel_x > 0)
	setBallVelocity(1, -1);
      else
	setBallVelocity(-1, -1);
      break;
    case 3: // Collision with player 1
      if (p1_vel > 0)
	setBallVelocity(1, 1);
      else
	setBallVelocity(1, -1);
      break;
    case 4:
      break;
    default:
      setBallVelocity(ball_vel_x, ball_vel_y);
      break;
    }
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

  resetPosition();
  clearScreen(COLOR_BLUE);
  sprintf(score, "Score: %i - %i", p1_score, p2_score);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      clearScreen(COLOR_BLUE);
      fillRectangle(ball_pos_x, ball_pos_y, 5, 5, COLOR_ORANGE); // Ball
      fillRectangle(p1_pos_x, p1_pos_y, 5, 50, COLOR_ORANGE);    // Player 1
      fillRectangle(p2_pos_x, p2_pos_y, 5, 50, COLOR_ORANGE);    // Player 2
      drawString5x7((screenWidth / 2) - 35, (screenHeight / 2) - 65, score, COLOR_ORANGE, COLOR_BLUE);
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    



