#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buttons.h"
#include "pong.h"

#define LED_GREEN BIT6             // P1.6

char *score;
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
    setBallVelocity(-1, 1);
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

  resetPosition();
  clearScreen(COLOR_BLUE);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      clearScreen(COLOR_BLUE);
      fillRectangle(ball_pos_x, ball_pos_y, 5, 5, COLOR_ORANGE); // Ball
      fillRectangle(p1_pos_x, p1_pos_y, 5, 50, COLOR_ORANGE);    // Player 1
      fillRectangle(p2_pos_x, p2_pos_y, 5, 50, COLOR_ORANGE);    // Player 2
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    



