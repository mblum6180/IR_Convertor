#include <IRremote.h>
int RECV_PIN = 11;
long NECVolUp = 412553965;
long NECVolDown = 412586605;
IRrecv irrecv(RECV_PIN);
decode_results results;
IRsend irsend;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
pinMode(RECV_PIN,INPUT);

irrecv.enableIRIn();
Serial.println("IR code");

}

void loop() {

  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    irrecv.enableIRIn();
    irrecv.resume(); {
       if(results.value == NECVolUp ){
   //delay(50);
   volUp();  
      }
         if(results.value == NECVolDown ){
     volDown();  
      }
    }
  }

}


void volUp(){
      for (int i = 0; i < 2; i++) {
      int khz = 38; // 38kHz carrier frequency for the NEC protocol
      unsigned int irSignal[] = {1200,450, 1200,450, 1250,450, 1200,450, 400,1300, 400,1250, 400,1300, 400,1300, 350,1300, 1200,450, 400,1300, 400};
      irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz);

      delay(40);
  }
     irrecv.enableIRIn();
}

void volDown(){
    for (int i = 0; i < 2; i++) {
      int khz = 38; // 38kHz carrier frequency for the NEC protocol
      unsigned int irSignal[] = {1250,450, 1250,450, 1200,450, 1250,450, 350,1300, 400,1300, 350,1300, 400,1300, 1200,450, 400,1250, 400,1300, 400};
  
      irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz);

      delay(40);
   }
     irrecv.enableIRIn();
}
