#include <stdio.h>

#include <transceiver.h>
#include <thread.h>
#include <msg.h>
#include <vtimer.h>
#include <board.h>
#include <at86rf231.h>


#define MSEC (1000)
#define SEC (1000 * MSEC)

uint8_t pkt_buff[128] = {6, 'H', 'E', 'L', 'L', 'O', '!'}; // first byte is the size, but it is dummy. Just for compatibility with the rest of the stack.

#define RADIO_STACK_SIZE    (2048)
char radio_stack_buffer[RADIO_STACK_SIZE];

#define RCV_BUFFER_SIZE     (128)

msg_t msg_q[RCV_BUFFER_SIZE];

static msg_t mesg;
static transceiver_command_t tcmd;

static radio_packet_t p;

void radio(void) {
  msg_t m;
  radio_packet_t *p;
  uint8_t i;

  msg_init_queue(msg_q, RCV_BUFFER_SIZE);

  while (1) {
    msg_receive(&m);
    if (m.type == PKT_PENDING) {
      p = (radio_packet_t*) m.content.ptr;
      printf("Packet waiting, process %p...\n", p);
      printf("\tLength:\t%u\n", p->length);
      printf("\tSrc:\t%u\n", p->src);
      printf("\tDst:\t%u\n", p->dst);
      printf("\tLQI:\t%u\n", p->lqi);
      printf("\tRSSI:\t%u\n", p->rssi);

      for (i = 0; i < p->length; i++) {
        printf("%02X ", p->data[i]);
      }
      p->processing--;
      printf("\n");
    }
    else if (m.type == ENOBUFFER) {
      puts("Transceiver buffer full");
    }
    else {
      puts("Unknown packet received");
    }
  }
}

void switch2rx(void) {
  mesg.type = SWITCH_RX;
  mesg.content.ptr = (char*) &tcmd;

  tcmd.transceivers = TRANSCEIVER_AT86RF231;
  puts("Turning transceiver on, RX mode");
  if (msg_send(&mesg, transceiver_pid, 1)) {
    puts("\tsuccess");
  }
}

void sender(uint8_t c) {
  unsigned int i;

  mesg.type = SND_PKT;
  mesg.content.ptr = (char*) &tcmd;

  tcmd.transceivers = TRANSCEIVER_AT86RF231;
  tcmd.data = &p;

  //p.length = AT86RF231_MAX_DATA_LENGTH;
  p.length = 6;
  p.dst = 0;

  for (i = 0; i < c; i++) {
    puts(".");
    p.data = pkt_buff; 
    msg_send(&mesg, transceiver_pid, 1);
    vtimer_usleep(1 * SEC);
  }
}

int main(void) {
  int radio_pid;

	LED_RED_OFF();
	LED_GREEN_OFF();
	printf("Hello World!\n");

  radio_pid = thread_create(radio_stack_buffer, RADIO_STACK_SIZE, 
                            PRIORITY_MAIN-2, CREATE_STACKTEST, radio, "radio");

  transceiver_init(TRANSCEIVER_AT86RF231);
  transceiver_start();
  transceiver_register(TRANSCEIVER_AT86RF231, radio_pid);

  at86rf231_set_channel(26);

  //switch2rx();

  while (1)
  {
    //puts(".");
	  vtimer_usleep(1 * SEC);
    sender(1);

	  LED_GREEN_TOGGLE();
  }

	return 0;
}
