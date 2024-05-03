/*
  Simple glitching example for arduino

  At this first experiment we will only send some spiks in to the MOSFET after 10 seconds
  and check the behavious of microcontroller.

  mail : lord.feistel@gmail.com
  author : Antonio Silva 


*/


// Definitions

// I used also pin 12, please check which one is better for yui
// #define GLITCHING_PIN 12

#define GLITCHING_PIN 9
#define GLITCHING_ITERATIONS 100
#define GLITCHING_INTERVAL_SIGNAL_DOWN 100
#define GLITCHING_INTERVAL 1000
#define PRESENTATION_TIME 10000



void setup() {
  // Set glitching pin as output
  pinMode(GLITCHING_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  // The pin is connected to the gate of the MOSFET
  digitalWrite(GLITCHING_PIN, HIGH);  

  // Let 's wait 10 seconds to demonstrate how the software
  // normally works beore start tpo glitching
  // this is just to make presentantion better
  
  // wait 10 seconds
  delay(PRESENTATION_TIME); 

  while (1)
  {

  digitalWrite(GLITCHING_PIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(GLITCHING_INTERVAL); 

    // Energy oscilation that cause uncertain behaviour
    // I adjust it manually, but a random approach can be done

    for(int i = 0 ; i < GLITCHING_ITERATIONS ; i++)
    {
      digitalWrite(GLITCHING_PIN, LOW);   
      digitalWrite(GLITCHING_PIN, HIGH);  
      delayMicroseconds(GLITCHING_INTERVAL_SIGNAL_DOWN);  
    }   
  }
}
