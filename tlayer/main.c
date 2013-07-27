#include <stdint.h>
#include <stdio.h>

#include <board.h>
#include <at86rf231.h>

#include "destiny/destiny.h"
//#include "shell.h"
//#include "posix_io.h"
//#include "board_uart0.h"

#define MSEC (1000)
#define SEC (1000 * MSEC)


#include "tlayer.h"

int main(void)
{
  	LED_RED_OFF();
    LED_GREEN_OFF();
    printf("Hello World!\n");

    printf("6LoWPAN Transport Layers\n");
    //posix_open(uart0_handler_pid, 0);

    init_transport_layer();
    printf("6LoWPAN Transport Layers init complete\n");


    //shell_t shell;
    //shell_init(&shell, shell_commands, uart0_readc, uart0_putc);

    //shell_run(&shell);

    //init(0);
    //vtimer_usleep(2 * SEC);
    //at86rf231_set_channel(26);
    //printf("Channel set\n");
    //bootstrapping(0);

    while (1)
    {
      vtimer_usleep(1 * SEC);

      //send_packet();

      LED_GREEN_TOGGLE();
    }

    return 0;
}
