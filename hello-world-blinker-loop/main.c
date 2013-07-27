#include <stdio.h>
#include "vtimer.h"
#include "board.h"

#define MSEC (1000)
#define SEC (1000 * MSEC)

int main(void) {
	LED_RED_OFF();
	LED_GREEN_OFF();
	printf("Hello World!\n");

  hwtimer_wait(10);

  while (1)
  {
	  vtimer_usleep(1 * SEC);

	  LED_GREEN_TOGGLE();
  }

	return 0;
}
