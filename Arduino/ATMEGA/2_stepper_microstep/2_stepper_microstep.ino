// CODE FOR 2 STEPPER TO RUN IN MICROSTEP MODES
// change MS1/2/3 & MS1_/2_/3_ to control steps as per datasheet

// pan motor on port D
// tilt motor on port A

// tilt motor sweeps 180 degrees
// pan motor moves 1 step up when tilt completes 180 degree

#include<SRA16.h>

#define MS1 REGISTER_BIT(PORTD,2)
#define MS2 REGISTER_BIT(PORTD,3)
#define MS3 REGISTER_BIT(PORTD,4)
#define ENABLE REGISTER_BIT(PORTD,5)
#define DIR REGISTER_BIT(PORTD,6)
#define STEP REGISTER_BIT(PORTD,7)

#define MS1_ REGISTER_BIT(PORTA,2)
#define MS2_ REGISTER_BIT(PORTA,3)
#define MS3_ REGISTER_BIT(PORTA,4)
#define ENABLE_ REGISTER_BIT(PORTA,5)
#define DIR_ REGISTER_BIT(PORTA,6)
#define STEP_ REGISTER_BIT(PORTA,7)

void setup() {
  // put your setup code here, to run once:
  DDRD = 0b11011100; // pan
  DDRA = 0b11011100; // tilt

  MS1 = 0;
  MS2 = 0;
  MS3 = 0;

  MS1_ = 0;
  MS2_ = 0;
  MS3_ = 0;

  DIR_ = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  DIR = 1;
  for (int y = 0; y < 100; y++)
  {
    STEP = 1;
    _delay_ms(50);
    STEP = 0;
    _delay_ms(50);
  }

  STEP_ = 1;
  _delay_ms(50);
  STEP_ = 0;
  _delay_ms(50);
    
  DIR = 0;
  for (int y = 0; y < 100; y++)
  {
    STEP = 1;
    _delay_ms(50);
    STEP = 0;
    _delay_ms(50);
  }

  STEP_ = 1;
  _delay_ms(50);
  STEP_ = 0;
  _delay_ms(50);
  
}

