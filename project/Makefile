# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all: wakedemo.elf

#additional rules for files
wakedemo.elf: ${COMMON_OBJECTS} wakedemo.o pong.o color.o wdt_handler.o buttons.o buzzer.o shape.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load: wakedemo.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

wakedemo.o: wakedemo.c

pong.o: pong.h pong.c 

buzzer.o: buzzer.h buzzer.c

buttons.o: buttons.h buttons.c

color.o: color.h color.s

shape.o: shape.h shape.s
