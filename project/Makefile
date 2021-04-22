# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all: wakedemo.elf

#additional rules for files
wakedemo.elf: ${COMMON_OBJECTS} color.o wakedemo.o pong.o wdt_handler.o p1_interrupt_handler.o buttons.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load: wakedemo.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

wakedemo.o: wakedemo.c

pong.o: pong.h pong.c 

buttons.o: buttons.h buttons.c

color.o: color.s color.h
