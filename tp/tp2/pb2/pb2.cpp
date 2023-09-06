#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 


/*
Quand la carte mère démarre, la DEL libre doit s'allumer en rouge. 
Si le bouton-poussoir libre pour usage général est pesé, la DEL affiche la couleur ambre. 
Quand le bouton-poussoir est relâché, la DEL devient verte. 
Si le bouton est de nouveau pesé, la DEL prend la couleur rouge encore. 
Quand il est relâché, la DEL s'éteint. 
Si le bouton est de nouveau pesé, la DEL affiche la couleur verte. 
Quand il est relâché, la DEL tourne au rouge ce qui fait que la carte mère est de retour à son état initial et tout peut recommencer.
*/

enum class state{state_0, state_1, state_2, state_3, state_4, state_5};
bool isPressed = false;
uint8_t off = 0;
uint8_t red = 1;
uint8_t green = 2;

void ChangeState(state *current_state, bool isPressed)
{
  switch (isPressed)
  {
    case true :
      switch (*current_state)
      {
      case state::state_0:
        *current_state = state::state_1;
        while (isPressed)
        {
          PORTA = red;
          _delay_ms(10);
          PORTA = green;
          _delay_ms(10);
          if (!(PIND & 0x04))
          {
            _delay_ms(10);
            if (!(PIND & 0x04)) 
            {
              break;
            }
          }
        }
        break;

      case state::state_2:
        *current_state = state::state_3;
        PORTA = red;
        break;

      case state::state_4:
        *current_state = state::state_5;
        PORTA = green;
        break;

      default:
        break;
      }
      break;
    
    case false :
      switch (*current_state)
      {
      case state::state_1:
        *current_state = state::state_2;
        PORTA = green;
        break;

      case state::state_3:
        *current_state = state::state_4;
        PORTA = off;
        break;

      case state::state_5:
        *current_state = state::state_0;
        PORTA = red;
        break;
      
      default:
        break;
      }
      break;
    
    default:
    break;
  }
}

int main()
{
  DDRA = 0xFF;
  state current_state = state::state_0;
  PORTA = red;

  while (true)
  {
    if (PIND & 0x04)
    {
      _delay_ms(10);
      if (PIND & 0x04) {isPressed = true; ChangeState(&current_state, isPressed);}
    }
    if (isPressed)
    {
        if (!(PIND & 0x04)) {isPressed = false; ChangeState(&current_state, isPressed);}
    }
  }

  return 0; 
}