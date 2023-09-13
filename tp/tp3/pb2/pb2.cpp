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
  
  DDRA = 0xff;
  int a = 0;
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
