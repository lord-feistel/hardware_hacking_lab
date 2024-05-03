/*
  Simple glitching example for arduino

  At this first experiment we will only send some spiks in to the MOSFET after 10 seconds
  and check the behavious of microcontroller.

  mail : lord.feistel@gmail.com
  author : Antonio Silva 
  

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
