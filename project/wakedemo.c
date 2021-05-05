#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buttons.h"
#include "buzzer.h"
#include "color.h"
#include "pong.h"

#define LED_GREEN BIT6             // P1.6

short redrawScreen = 1;
u_int shapeColor = COLOR_ORANGE;

void draw_shape(char size) {
  char x_offset = (screenWidth / 2);
  char y_offset = (screenHeight / 2) - 25;

  char n = size;
  
  while (--n > 0) {
    for (char i = 0; i < size; i++) {
      drawPixel(x_offset + i, y_offset, COLOR_ORANGE);
    }
    x_offset++;
    y_offset--;
  }
}

void collision_handler() {
  char collision = detectCollision();
  if (collision) set_buzzer(500);
  switch (collision) {
  case 1: // Collision with top of screen
    if (ball.vel_x > 0)
      setBallVelocity(3, 3);
    else
      setBallVelocity(-3, 3);
    break;
  case 2: // Collision with bottom of screen
    if (ball.vel_x > 0)
      setBallVelocity(3, -3);
    else
      setBallVelocity(-3, -3);
    break;
  case 3: // Collision with player 1
    if (p1.vel > 0)
      setBallVelocity(3, 3);
    else
      setBallVelocity(3, -3);
    break;
  case 4: // Collision with player 2
    if (p2.vel > 0)
      setBallVelocity(-3, 3);
    else
      setBallVelocity(-3, -3);
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
    set_buzzer(0);
    collision_handler();
    if (withinBounds()) {
      if (sw1 && canMove(1, -5))
	setVelocity(1, -5);
      if (sw2 && canMove (1, 5))
	setVelocity(1, 5);
      if (sw3 && canMove(2, -5))
	setVelocity(2, -5);
      if (sw4 && canMove(2, 5))
	setVelocity(2, 5);
    } else {
      resetPosition();
      clearScreen(COLOR_BLUE);
    }
  }
}
  

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  buzzer_init();
  buttons_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */

  setScore(1, 0);
  setScore(2, 0);
  resetPosition();
  setBallVelocity(-3, -3);
  clearScreen(COLOR_BLUE);

  draw_shape(15);
  
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;

      change_color();
      fillRectangle(ball.prev_x, ball.prev_y, 5, 5, shapeColor); // Ball
      fillRectangle(p1.prev_x, p1.prev_y, 5, 50, shapeColor);    // Player 1
      fillRectangle(p2.prev_x, p2.prev_y, 5, 50, shapeColor);    // Player 2

      change_color();
      fillRectangle(ball.pos_x, ball.pos_y, 5, 5, shapeColor); // Ball
      fillRectangle(p1.pos_x, p1.pos_y, 5, 50, shapeColor);    // Player 1
      fillRectangle(p2.pos_x, p2.pos_y, 5, 50, shapeColor);    // Player 2
    }
    
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    



