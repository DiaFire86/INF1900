/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 * 
 * Version 1.2 par Jérôme Collin, août 2023
 * 
 */

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 

int main()
{
  
  DDRA = 0xff;
  uint8_t vert = 1;
  uint8_t rouge = 2; 
  int color = 0;

  while (true)
  {
    if (PIND & 0x04)
    {
      _delay_ms(10);
      if (PIND & 0x04)
      { 
        if (color == 0){color = 1; PORTA = vert; _delay_ms(200);}
        else if (color == 1){color = 2; PORTA = rouge; _delay_ms(200);}
        else if (color == 2){_delay_ms(200); while (color == 2){PORTA = vert; _delay_ms(10); PORTA = rouge; _delay_ms(10); if(PIND & 0x04){_delay_ms(10); if (PIND & 0x04){color = 0;}}};}
      }
    }
  }


  return 0; 
}

