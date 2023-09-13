/*
Authors: Ikram Arroud (2210444), Leo Martineau (2114043)
INF1900
Section 02
TP-2, Pb-1
*/

//Program Description: 
// This program displays a color and when the button is pressed, it fade away in 3 second then light up in the other color to do the same thing.
// The color fade away in 3 second at 1 kHz.
// DDRD is set as inputs for the button, whereas DDRA1 and DDRA2 are outputs for the LED, as we plugged the ports A0 and A1 to the double-LED pin:
// The color green is displayed when PORTA0 is set to 1 and PORTA1 is set to 0.
// Finally,to turn off the led, we set both PORTA0 and PORTA1 to 0.
// We initialize the b and a at 1000 to have a ratio a/b starting at 1 and decreasing to 0 in 3 seconds.


#define F_CPU 8000000UL
#define BUTTON_DEBOUNCE_DELAY 10
#define INTERRUPT_BUTTON_PIN 0x04

#include <util/delay.h>
#include <avr/io.h> 

enum Color {RED, GREEN};

void setGreen()
{
  PORTA &= ~(1<<PORTA0);
  PORTA |= (1<<PORTA1);
}

void setRed()
{
  PORTA |= (1<<PORTA0);
  PORTA &= ~(1<<PORTA1);
}

void setColor(Color CurrentColor)
{
  if (CurrentColor == RED) {setRed();}
  else {setGreen();}
}

void setDark()
{
  PORTA &= ~(1<<PORTA0);
  PORTA &= ~(1<<PORTA1);
}


int main()
{
  
  DDRA |= (1<<PORTA0)|(1<<PORTA1);
  DDRD &= ~(1<<DDD2); // Dont know if useful
  int a = 1000;
  int b = 1000;
  Color CurrentColor = RED;

  setColor(CurrentColor);
  while (true)
  {
    if (PIND & INTERRUPT_BUTTON_PIN)
    {
      _delay_ms(BUTTON_DEBOUNCE_DELAY);
      if (PIND & INTERRUPT_BUTTON_PIN)
      { 
        for (int i = 0; i < 3000; i++)
        {
          a = b - i/3;
          setColor(CurrentColor);
          for (int j = 0; j <= a; j++)
          {
            _delay_us(1);
          }
          setDark();
          for (int j = 0; j <= b - a; j++)
          {
            _delay_us(1);
          }
        }
        if (CurrentColor == RED) {CurrentColor = GREEN;}
        else {CurrentColor = RED;}
        setColor(CurrentColor);
      }
    }
  }
  return 0; 
}
