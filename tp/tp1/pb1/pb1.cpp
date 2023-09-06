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

  while (true) 
  {

    PORTA = rouge;
    _delay_ms(1000);

    PORTA = vert;
    _delay_ms(1000);

    for (int i = 0; i < 50; i++) {
      PORTA = rouge;
      _delay_ms(10);
      PORTA = vert;
      _delay_ms(10);
    }
  }


  return 0; 
}

