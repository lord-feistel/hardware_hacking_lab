## Table of Contents

1. [Introduction](#introduction)
2. [Materials and Methods](#materials-and-methods)
3. [Assembling the Target](#assembling-the-target)
4. [Converting Arduino Nano to an ICSP Programmer](#converting-arduino-nano-to-an-icsp-programmer)
5. [Flashing the Bootloader onto the Breadboard with ICSP Programmer](#flashing-the-bootloader-onto-the-breadboard-with-icsp-programmer)
6. [Flashing the Test Firmware onto the Target](#flashing-the-test-firmware-onto-the-target)
7. [Assembly of Glitching Circuit](#assembly-of-glitching-circuit)
8. [The MOSFET Purpose](#the-mosfet-purpose)
9. [Process Explanation](#process-explanation)
10. [Results](#results)
11. [Conclusion](#conclusion)
12. [References](#references)

## Introduction

Glitching attacks, a form of hardware-based security vulnerability exploitation, pose significant threats to the integrity and confidentiality of computing systems [1].

This PoC (Proof of Concept) provides a glitching attack demonstration.

Glitching involves the intentional injection of transient faults or glitches into a device's hardware to disrupt its normal operation, potentially bypassing security measures or compromising sensitive information [1].

The disruption can affect features such as cryptography [2] or the secure boot process.

The PoC explores vulnerabilities in the Atmega 328P microcontroller, broadly used with Arduino, such as cryptographic algorithms and secure boot processes [3].

The glitching attack disrupts system stability, inducing unforeseen behaviors. It can manifest through manipulation of power or clock signals [3].

This proof-of-concept focuses on inducing glitches in the power line.

## Materials and Methods

The experimental setup comprised the following components:

| Quantity | Component                   | 
|----------|-----------------------------|
|     1    | MOSFET IRL540N              |
|     1    | Resistor (10K ohm)          | 
|     1    | Atmega 328P DIP (package)   |
|     1    | Large Breadboard            |
|     1    | 16 MHz Crystal Oscillator   |
|     2    | Capacitors (22 pF each)     |
|     -    | Power Supply (5V, minimum 500 mA) |
|     -    | Multiple wires              |
|     1    | Arduino Nano or equivalent  |
|     1    | LCD with I2C circuit        |

The **Figure 1** shows the artifacts used in this PoC.

**Note:** An Arduino Uno can be substituted, obviating the necessity for In Circuit Programming using the Arduino Nano (or Every).

![Figure 1: Arduino Flashing](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/components.jpg)

**Figure 1:** Components used in the breadboard's Arduino assembly.

## Assembling the Target

As previously mentioned, our goal is to introduce faults in the power line supply inducing the microcontroller to make mistakes which we can take advantage of.

Capacitors play a crucial role in stabilizing power supplies by smoothing out voltage fluctuations and reducing ripple [4,5].

They store and release electrical energy, ensuring a steady voltage output essential for the reliable operation of electronic devices [5].

Performing glitching directly on the Arduino Nano is unfeasible due to capacitors safeguarding against power supply fluctuations. 

The Arduino board incorporates numerous stabilizing capacitors and a power regulator, as illustrated in **Figure 2**.

![Figure 2: Arduino Flashing](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/capacitors.jpg)

**Figure 2:** Capacitors on the Arduino Nano board.

Removing the capacitor requires specialized equipment such as a hot air tool or a high-quality soldering station for surface-mount devices (SMD). 

Alternatively, listed components can be used to construct a new Arduino board on a breadboard without capacitors, streamlining the process and making it easier to manipulate connections if needed.

### Arduino Assembly

#### Connection Setup

The schematic depicted in **Figure 3** replaces the conventional Arduino board, and **Figure 4** shows the assembled circuit on the breadboard but still without the LCD connected.

![Figure 3: Arduino Flashing](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/arduino_flashing.PNG)

**Figure 3:** Schematics for flashing the Atmega328P on the breadboard.

![Figure 4: Arduino Flashing](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/atmel_stantd_alone.jpeg)

**Figure 4:** Breadboard assembly mimicking an Arduino Uno.

After the project started, it was decided to add an LCD to be easier to provide the results since it was not very user-friendly the oscilloscope presentation. 

The LCD display is a common display with I2C support, as shown in **Figure 5** and **Figure 6**.

![Figure 5: Arduino Flashing](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/lcd_front.jpg)

**Figure 5:** Front view of the LCD.

![Figure 6: Arduino Flashing](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/lcd_back.jpg)

**Figure 6:** Back view of the LCD.

The breadboard receives an external power supply as the Arduino Nano lacks sufficient power to keep the breadboard's circuit energized. 

The firmware is flashed into the breadboard via SPI connection [6] after the conversion of the Arduino Nano to an ICSP (In-Circuit Serial Programmer).

**Note:** As our intention is to cause instability in the power line supply, no capacitors are inserted in the breadboard. However, if in the future the correct usage is the purpose, it is reasonable to insert at least a capacitor in the power-supply line near the microcontroller as shown in **Figure 7**.

![Figure 7: Arduino Flashing](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/capacitors_01.jpg) 

**Figure 7:** Capacitors used in the Arduino to stabilize the power line.

## Converting Arduino Nano to an ICSP Programmer

The Arduino can function as an ICSP (In-Circuit Serial Programmer) for Atmel processors. It is commonly utilized in conjunction with AVR Studio or Atmel Studio since the official programmers are quite expensive. 

This configuration facilitates flashing the Arduino bootloader onto the Atmega328P and subsequently loading the test firmware onto the Arduino. 

To convert the Arduino Nano into an ICSP, upload the "ArduinoISP" sketch as presented in **Figure 8**.

![Figure 8: ICSP Configuration](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/load_arduino_isp.PNG)

**Figure 8:** Loading ISP programmer on the Arduino Nano.

**Note:** You must check in your Arduino's datasheet which pins are the *MOSI* and *MISO* and *SCK* [6]. **Figure 9** shows the pins used by the Arduino Nano used in the PoC to flash the firmware to the breadboard.

After all circuits are assembled, it should look like **Figure 10**.

![Figure 9: ICSP Configuration](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/arduino_ISP.jpeg)

**Figure 9:** Connections for Arduino ISP wiring.

![Figure 10: Arduino Flashing](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/picture_with_isp.jpg)

**Figure 10:** Complete circuit for flashing the Arduino bootloader and sketch.

## Flashing the Bootloader onto the Breadboard with ICSP Programmer

Upon establishing the requisite connections as discussed previously, the bootloader is flashed onto the Atmega located on the breadboard. Navigate to **Tools -> Burn Bootloader** as depicted in Figure 11.

![Figure 11: Burning Bootloader](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/burn_arduino.png)

**Figure 11:** Burn bootloader menu.

Upon successful execution, a confirmation message is displayed. 

Occasionally, misleading errors such as the one illustrated below in **Figure 12** may arise, often attributable to connection issues.

![Figure 12: Error Message](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/yieks.PNG)

**Figure 12:** Common connection error.

If encountered, meticulously verify the connections.

## Flashing the Test Firmware onto the Target

The test program, denoted as **test.ino**, is straightforward and available in this repository. 

As the breadboard lacks direct computer connectivity, the firmware is uploaded via the ICSP programmer akin to the bootloader.

Clone the repository, open **"test.ino"**, configure the board settings as illustrated below in **Figure 13**, designating the breadboard as an Arduino Nano. 

![Figure 13: Board Configuration](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/arduino_ISP_conf.png)

**Figure 13:** Configuring the board.

Afterwards, select the programmer as **Arduino as ISP** and upload the sketch using the programmer as illustrated in **Figure 14**.

![Figure 14: Test Firmware Upload](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/upload_test.png)

**Figure 14:** Uploading using the ISP programmer.

With the target setup completed, the next sections will proceed to assembling the glitching circuit.

**Note: If the reader has an Arduino Uno, the bootloader and the firmware can be flashed using the Arduino Uno board, avoiding the need of first adapting the Arduino Nano to an ICSP programmer before adapting it to a glitch circuit.**

## Assembly of Glitching Circuit

The schematic for the glitching hardware is depicted in **Figure 15** and intends to destabilize the power line using a MOSFET transistor.

The same technique can be applied to the reset line and can also be exploited.

![Figure 15: Glitching Hardware](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/arduino_glitching.PNG)

**Figure 15:** Schematics for glitching.

### Circuit Integration and Glitching Operation

Subsequently, upload the **glitching.ino** to the Arduino Nano as customary. The complete circuit assembly is portrayed in **Figure 16**.

![Figure 16: Complete Circuit Assembly](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/complete_circuit.jpeg)

**Figure 16:** Complete glitch circuit.

## The MOSFET Purpose

Using a microcontroller pin directly to power another microcontroller or load is not recommended due to current limitations, voltage compatibility issues, lack of protection, and isolation [7]. 

Instead, using a transistor provides amplification, voltage level shifting, protection, and control, ensuring safe and reliable operation of both the microcontroller and the load [7,4].

MOSFETs operate primarily in a voltage-controlled mode. The conductivity of the channel is controlled by the voltage applied to the gate terminal. 

This voltage-based control allows for rapid changes in the channel conductivity, resulting in faster switching speeds [4].

In practical terms, MOSFETs are preferred for applications requiring high-speed switching, such as inverter circuits, motor control, and high-frequency switching power supplies [4].

**Figure 17** shows the MOSFET polarization circuit. 

Note that a resistor is not used between the microcontroller pin the MOSFET since unlike a BJT it is operated based on the voltage and not on the current [4].

![Figure 17: Test Firmware Upload](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/IRL540N_circuit.jpeg)

**Figure 17:** MOSFET assembly.

The hardware environment should look like **Figure 18**.

![Figure 18: Arduino Flashing](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/complete_envirorment.jpeg)

**Figure 18:** Complete glitch environment.

## Process Explanation

The intention is to skip the `if` block and make it possible to reach the `println(";)")`. Normally, this point cannot be reached under normal circumstances as the integer `a` will never be greater than 10. 

This is merely a Proof-of-concept, but consider scenarios where the "if" block represents a critical security function, such as a password validation or encryption key generation.

Following the code for the target is presented. This code also can be found in this repo as **test.ino**

```C
*/

// IMPORTANT THE FOLLOWING LIBRARIES MUST TO BE INSTALLED
// CHECK IN THE INTERNET HOW TO DO IT

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define LCD_ADDRESS 0x27
#define LINE_COLUMNS 16,2

// set the LCD through the I2C
// LCD is a slave with address 27 in hex
// it is a display with 2 lines and 16 columns

LiquidCrystal_I2C lcd(LCD_ADDRESS, LINE_COLUMNS );

void setup() {
  
  // initialize LCD hardware
  lcd.init();
  lcd.backlight();

}

// the loop function runs over and over again forever
void loop() {



  // wait  for a second
  // we wait all capacitors, etc.
  // also we wait LCD is done.
  delay(1000);

  // put cursor at begin
  lcd.setCursor(0,0);
  
  // we will use it to know when
  // the software was rebooted
  // because glitching

  lcd.print("start");
  lcd.setCursor(0,1);

  // the counter
  int a = 0;

while(1)
{

  lcd.print(a);
  delay(500);


  /*

    Instruction to be skipped. Bote that as a is an integer
    the following instruction is not atomic.

    So it won't be a 1:1 with assembly instruction, Please check the atmel 328
    datasheet for the instructions and use some disassemble to check if I am telling
    the true :)
  
  */

  a++; 


  // it will count till 10 and after go back to zero

  // We want to scape this "if" and makes a > 10
  if(a == 10)
  {

      lcd.setCursor(0,1);
      a = 0;
      lcd.clear();
  }

  // In theory impossible to reach out since the count is 
  // always reset when reach 10

  if(a > 10)
  {
      // this symbol appear when
      // glitch happened 
      lcd.print(";)");
  }
}

}
``` 

### Glitching Code


Following the code for the glitcher is presented. This code also can be found in this repo as **glitcher.ino**

```C
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

```

The code operates normally for 10 seconds initially, and then in the loop.

I manually adjusted the parameters, and after turning it on, it worked. 

It can be improved using a potentiometer in the microcontroller AD converter to manipulate those values. However, as it is only a PoC, I tried to keep it as simple as possible.

It's a random glitching process sufficient to demonstrate the manipulation of instruction sequences inside the microcontroller. 

It continuously sends oscillations to the breadboard power-line every 1 second. 

The randomness is introduced once the glitching circuit is never turned off, and if the user manually turns off and turns on the target, it will randomly pick up the signal delivered by the glitching circuit when the firmware starts to execute.

## Results

The circuit normally works as shown in **Video 1**.

[![Video 1: Circuit Working Normally](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/communication_freak_youtube_short.PNG)](https://youtube.com/shorts/bZ1MB8XfEco)

If the reader is curious, it is also possible to observe the Glitching signal through an oscilloscope as presented in **Video 2**. Most of the time, the hardware will start to behave unusually as shown in **Video 3**.

[![Video 2: Capturing a Glitching Attempt](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/glitching_attempt_freak_youtube_short.PNG)](https://youtu.be/I3Xn_78Hp-U)

[![Video 3: Capturing a Glitching Attempt](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/communication_freak_youtube_short.PNG)](https://youtu.be/UySfIcTq-Ns)

In the PoC tests, a successful glitching happened after 1 minute, displaying ";)" on the LCD. **Video 4** shows it happening. **Figure 19** captured the exact moment.

[![Video 4: Glitching Happening](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/glitching_happening_youtube_short.PNG)](https://youtube.com/shorts/Eb_dHtrLmSM)

![Figure 19: Glitching Happening](https://github.com/lord-feistel/glitching_lab/blob/main/images_videos/glitching_happening_pic.jpg)

## Conclusion

The ability to exploit microcontrollers through glitching techniques presents a critical challenge in modern cybersecurity research, with profound implications for the security of embedded systems. Glitching attacks can compromise the integrity and functionality of microcontrollers, posing significant risks to the myriad of embedded systems they power. These vulnerabilities allow attackers to bypass security measures, manipulate firmware, and extract sensitive information, leading to potential disruptions and security breaches.

The problematic nature of glitching lies in its ability to undermine the trustworthiness of embedded systems, which often operate in resource-constrained environments with limited security measures. The pervasive impact of glitching attacks amplifies the systemic risk to embedded systems' security and resilience, necessitating proactive measures to detect and mitigate vulnerabilities.

Addressing the challenges posed by glitching attacks requires a concerted effort from cybersecurity researchers, industry stakeholders, and regulatory bodies. Robust vulnerability assessment, coupled with the implementation of hardware and software defenses, is crucial to fortifying the security posture of embedded systems.

By fostering collaboration and investing in comprehensive security strategies, we can mitigate the risks associated with glitching attacks and ensure the continued trustworthiness of embedded systems. It is imperative to remain vigilant and proactive in safeguarding against emerging threats in the ever-evolving cybersecurity landscape.

## References

1. Koç, Ç. K., & Paar, C. (2005). *Side-Channel Analysis and Fault Injection Attacks on Cryptographic Hardware*. Springer.

2. Paar, C., & Pelzl, J. (2010). *Understanding Cryptography: A Textbook for Students and Practitioners*. Springer.

3. Mangard, S., Oswald, E., & Popp, T. (2011). *Side-Channel Attacks: Theory and Practice*. Springer.

4. Horowitz, P., & Hill, W. (2015). *The Art of Electronics (3rd ed.)*. Cambridge University Press. 

5. Liu, H. (2007). *MOSFET Modeling for Circuit Analysis and Design*. World Scientific.
