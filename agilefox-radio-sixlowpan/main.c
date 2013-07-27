#include <stdio.h>

#include <transceiver.h>
#include <thread.h>
#include <msg.h>
#include <vtimer.h>
#include <board.h>
#include <at86rf231.h>

#include "sixlowmac.h"
#include "sixlowip.h"
#include "sixlowborder.h"
#include "sixlowpan.h"
#include "sixlowerror.h"


#define MSEC (1000)
#define SEC (1000 * MSEC)

uint8_t pkt_buff[128] = {'H', 'E', 'L', 'L', 'O', '!'};

//#define RADIO_STACK_SIZE    (2048)
//char radio_stack_buffer[RADIO_STACK_SIZE];

//#define RCV_BUFFER_SIZE     (128)

//msg_t msg_q[RCV_BUFFER_SIZE];

static msg_t mesg;
static transceiver_command_t tcmd;

static radio_packet_t p;





void init_six(void)
{
    char command = 'b';
    uint16_t r_addr;
    ipv6_addr_t std_addr;

    int res;
    
   
    ipv6_init_address(&std_addr,0xABCD,0,0,0,0x1034,0x00FF,0xFE00,r_addr);


    switch (command) {
        case 'h':
            printf("INFO: Initialize as host on radio address %hu\n", r_addr);
            if (r_addr > 255) {
                printf("ERROR: radio_address not an 8 bit integer\n");
                return;
            }
            sixlowpan_init(TRANSCEIVER_AT86RF231,r_addr,0);
            break;
        case 'r':
            printf("INFO: Initialize as router on radio address %hu\n", r_addr);
            if (r_addr > 255) {
                printf("ERROR: radio_address not an 8 bit integer\n");
                return;
            }
            sixlowpan_init(TRANSCEIVER_AT86RF231, r_addr,0);
            ipv6_init_iface_as_router();
            break;
        case 'a':
            printf("INFO: Initialize as adhoc router on radio address %hu\n", r_addr);
            if (r_addr > 255) {
                printf("ERROR: radio_address not an 8 bit integer\n");
                return;
            }
            sixlowpan_adhoc_init(TRANSCEIVER_AT86RF231, &std_addr, r_addr);
            break;
        case 'b':
            printf("INFO: Initialize as border router on radio address %hu\n", r_addr);
            if (r_addr > 255) {
                printf("ERROR: radio_address not an 8 bit integer\n");
                return;
            }
            res = border_initialize(TRANSCEIVER_AT86RF231, &std_addr);
            switch (res) {
                case (SUCCESS): printf("INFO: Border router initialized.\n"); break;
                case (SIXLOWERROR_ADDRESS): printf("ERROR: Illegal IP address: "); 
                        ipv6_print_addr(&std_addr); break;
                default: printf("ERROR: Unknown error (%d).\n", res); break;
            }
            break;
        default:
            printf("ERROR: Unknown command '%c'\n", command);
            break;
    }
}

void bootstrapping()
{
    sixlowpan_bootstrapping();
}

void send_packet(void)
{
  uint8_t test[2];
  test[0] = 30;
  test[1] = 98;

  ipv6_addr_t ipaddr;
  ipv6_init_address(&ipaddr, 0xabcd, 0x0, 0x0, 0x0, 0x3612, 0x00ff, 0xfe00, 0x0005); 
  ipv6_print_addr(&ipaddr);
  
  test[0] = 0xAB;
  sixlowpan_send(&ipaddr, test, 2, 0);
}



int main(void)
{
  int radio_pid;

	LED_RED_OFF();
	LED_GREEN_OFF();
	printf("Hello World!\n");

  init_six();

  at86rf231_set_channel(26);

  //bootstrapping();
  //switch2rx();

  while (1)
  {
	  vtimer_usleep(1 * SEC);

    //send_packet();

	  LED_GREEN_TOGGLE();
  }

	return 0;
}
