/*
 * This is a simple pir based light control.
 *
 * I got tired of walking in to the basement to hack and having to
 * walk around to plug in the light so I put this together so I just
 * walk in and lights come on automagically
 * 
 */

// Pin 9 is connected to the pir data
byte pir = 9;
// pin 10 is connected to the ? port on the power strip
byte relay = 12;
boolean light_status = false; // true == on false == off
long max_idle_millis = 300000; // 5 minutes
int loop_iterator = 1000; // millis
long idle_millis = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  Serial.begin(115200);
  pinMode(pir, INPUT);
  pinMode(relay, OUTPUT);
}

void light_on() {
  if ( ! light_status ) {
    Serial.println("Turning on lights");
    digitalWrite(relay, LOW); // this seems backwards
    light_status = true;
  } else {
    Serial.println("Lights should already be on");
  }
}

void light_off() {
  if ( light_status ) {
    Serial.println("Turning off lights");
    digitalWrite(relay, HIGH); // this seems backwards
    light_status = false;
  } else {
    Serial.println("Lights should already be off");
  }
}

void loop() {
  byte pir_status = digitalRead(pir);
  Serial.print("Current reading: ");
  Serial.print(pir_status);
  Serial.print(" Lights are: ");
  Serial.println(light_status);
  if ( pir_status == 0 ) {
    Serial.print("Incr idle_millis from: ");
    Serial.print(idle_millis);
    idle_millis += loop_iterator;
    Serial.print(" to: ");
    Serial.println(idle_millis);
    if ( idle_millis >= max_idle_millis ) {
      Serial.print("Turning lights off - max_idle_millis = ");
      Serial.println(max_idle_millis);
      light_off();
    }
  } else {
    light_on();
    idle_millis = 0;
  }
  Serial.print("delay for ");
  Serial.println(loop_iterator);
  delay(loop_iterator); 
}
