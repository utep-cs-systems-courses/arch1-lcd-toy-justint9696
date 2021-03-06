#include <msp430.h>

#include "buttons.h"
#include "pong.h"

char sw1 = 0, sw2 = 0, sw3 = 0, sw4 = 0;

void buttons_init() {
  P2REN |= BUTTONS;
  P2IE |= BUTTONS;
  P2OUT |= BUTTONS;
  P2DIR &= ~BUTTONS;

  button_handler();
}

static char button_handler() {
  char p2val = P2IN;
  
  P2IES |= (P2IN & BUTTONS);
  P2IES &= (P2IN | ~BUTTONS);

  return p2val;
}

char button_pressed(unsigned char button) {
  char p2val = button_handler();
  switch (button) {
  case 1:
    return (p2val & BTN1) ? 0 : 1;
  case 2:
    return (p2val & BTN2) ? 0 : 1;
  case 3:
    return (p2val & BTN3) ? 0 : 1;
  case 4:
    return (p2val & BTN4) ? 0 : 1;
  default:
    return 0;
  }
}

void button_interrupt_handler() {
  char p2val = button_handler();
  sw1 = (p2val & BTN1) ? 0 : 1;
  sw2 = (p2val & BTN2) ? 0 : 1;
  sw3 = (p2val & BTN3) ? 0 : 1;
  sw4 = (p2val & BTN4) ? 0 : 1;
}

void __interrupt_vec(PORT2_VECTOR) Port2() {
  if (P2IFG & BUTTONS) {
    P2IFG &= ~BUTTONS;
    button_interrupt_handler();
  }
}
