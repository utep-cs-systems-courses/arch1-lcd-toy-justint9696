#ifndef _BUTTONS_
#define _BUTTONS_

#define BTN1 BIT0
#define BTN2 BIT1
#define BTN3 BIT2
#define BTN4 BIT3
#define BUTTONS (BTN1 | BTN2 | BTN3 | BTN4)

extern char sw1, sw2, sw3, sw4;

void buttons_init();

static char button_handler();

char button_pressed(unsigned char button);

void button_interrupt_handler();

#endif
