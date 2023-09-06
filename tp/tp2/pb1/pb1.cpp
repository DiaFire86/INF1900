#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 

/*Les compteurs sont une forme de machines à états. 
On veut ici simplement que la DEL soit éteinte au départ. 
On doit appuyer et relâcher 3 fois le bouton-poussoir avant que la DEL tourne au vert pendant exactement 2 secondes. 
Par la suite, on revient au départ pour pouvoir recommencer.
*/

enum class state{state_0, state_1, state_2};
bool isPressed = false;

void changeState(state *current_state)
{
  switch (*current_state)
  {
  case state::state_0:
    *current_state = state::state_1;
    break;
  
  case state::state_1:
    *current_state = state::state_2;
    break;

  case state::state_2:
    PORTA = 2;
    _delay_ms(2000);
    PORTA = 0;
    *current_state = state::state_0;
    break;
  
  default:
    break;
  }
}

int main()
{
  DDRA = 0xFF;
  state current_state = state::state_0;

  while (true)
  {
    if (PIND & 0x04)
    {
      _delay_ms(10);
      if (PIND & 0x04) {isPressed = true;}
    }
    if (isPressed)
    {
      if (!(PIND & 0x04))
      {
        _delay_ms(10);
        if (!(PIND & 0x00)) {isPressed = false; changeState(&current_state);}
      }
    }
  }
  return 0; 
}