#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buttons.h"
#include "color.h"
#include "pong.h"

#define LED_GREEN BIT6             // P1.6

short redrawScreen = 1;
u_int shapeColor = COLOR_ORANGE;

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
      setBallVelocity(5, -5);
    else
      setBallVelocity(-5, -5);
    break;
  case 3: // Collision with player 1
    if (p1.vel > 0)
      setBallVelocity(5, 5);
    else
      setBallVelocity(5, -5);
    break;
  case 4: // Collision with player 2
    if (p2.vel > 0)
      setBallVelocity(-5, 5);
    else
      setBallVelocity(-5, -5);
    break;
  default:
    setBallVelocity(ball.vel_x, ball.vel_y);
    break;
  }
}

void wdt_c_handler()
{
  static char dsecCount = 0;
  
  if (++dsecCount == 25) {
    dsecCount = 0;
    redrawScreen = 1;
    collision_handler();
    if (withinBounds()) {
      if (button_pressed(1) && canMove(1, -5))
	setVelocity(1, -5);
      if (button_pressed(2) && canMove (1, 5))
	setVelocity(1, 5);
      if (button_pressed(3) && canMove(2, -5))
	setVelocity(2, -5);
      if (button_pressed(4) && canMove(2, 5))
	setVelocity(2, 5);
    } else {
      clearScreen(COLOR_BLUE);
      resetPosition();
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
  setBallVelocity(-5, -5);
  clearScreen(COLOR_BLUE);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;

      shapeColor = COLOR_BLUE;
      fillRectangle(ball.prev_x, ball.prev_y, 5, 5, shapeColor); // Ball
      fillRectangle(p1.prev_x, p1.prev_y, 5, 50, shapeColor);    // Player 1
      fillRectangle(p2.prev_x, p2.prev_y, 5, 50, shapeColor);    // Player 2

      shapeColor = COLOR_ORANGE;
      fillRectangle(ball.pos_x, ball.pos_y, 5, 5, shapeColor); // Ball
      fillRectangle(p1.pos_x, p1.pos_y, 5, 50, shapeColor);    // Player 1
      fillRectangle(p2.pos_x, p2.pos_y, 5, 50, shapeColor);    // Player 2
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    



