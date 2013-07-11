#include <stdio.h>
#include "vtimer.h"
#include "board.h"

#define MSEC (1000)
#define SEC (1000 * MSEC)

uint8_t pkt_buff[128] = {8, 'H', 'E', 'L', 'L', 'O', '!'};


int main(void) {
	LED_RED_OFF();
	LED_GREEN_OFF();
	printf("Hello World!\n");

  at86rf231_init();
  at86rf231_set_channel(26);
  puts("rf init ok");

  while (1)
  {
    puts(".");
	  vtimer_usleep(1 * SEC);
    at86rf231_xmit(pkt_buff, 7);

	  LED_GREEN_TOGGLE();
  }

	return 0;
}
