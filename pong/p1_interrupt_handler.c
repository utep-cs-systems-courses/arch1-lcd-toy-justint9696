#include <msp430.h>

#include "buttons.h"

void __interrupt_vec(PORT2_VECTOR) Port2() {
  if (P2IFG & BUTTONS) {
    P2IFG &= ~BUTTONS;
    button_interrupt_handler();
  }
}
