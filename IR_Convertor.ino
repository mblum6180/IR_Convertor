#include <IRremote.h>

const int RECV_PIN = 11;
const long NEC_VOL_UP = 412553965;
const long NEC_VOL_DOWN = 412586605;

void setup() {
  Serial.begin(9600);
  pinMode(RECV_PIN, INPUT);
  
  // Initialize IR receiver
  IRrecv irrecv(RECV_PIN);
  irrecv.enableIRIn();
  Serial.println("IR code");
  
  // Loop for receiving and processing IR signals
  while (true) {
    decode_results results;
    if (irrecv.decode(&results)) {
      Serial.println(results.value);
      irrecv.resume();
      
      if (results.value == NEC_VOL_UP) {
        volUp();
      } else if (results.value == NEC_VOL_DOWN) {
        volDown();
      }
    }
  }
}

void volUp() {
  IRsend irsend;
  for (int i = 0; i < 2; i++) {
    int khz = 38; // 38kHz carrier frequency for the NEC protocol
    unsigned int irSignal[] = {1200, 450, 1200, 450, 1250, 450, 1200, 450, 400, 1300, 400, 1250, 400, 1300, 400, 1300, 350, 1300, 1200, 450, 400, 1300, 400};
    irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz);

    delay(40);
  }
}

void volDown() {
  IRsend irsend;
  for (int i = 0; i < 2; i++) {
    int khz = 38; // 38kHz carrier frequency for the NEC protocol
    unsigned int irSignal[] = {1250, 450, 1250, 450, 1200, 450, 1250, 450, 350, 1300, 400, 1300, 350, 1300, 400, 1300, 1200, 450, 400, 1250, 400, 1300, 400};
    irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz);

    delay(40);
  }
}
