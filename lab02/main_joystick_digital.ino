#define UP_TRESHOLD 240           // zde vhodně nastavte hranici, která určí, že je joystick v pozici nahoře
#define DOWN_TRESHOLD -240         // zde vhodně nastavte hranici, která určí, že je joystick v pozici dole
#define RIGHT_TRESHOLD 240        // zde vhodně nastavte hranici, která určí, že je joystick v pozici vpravo
#define LEFT_TRESHOLD -240         // zde vhodně nastavte hranici, která určí, že je joystick v pozici vlevo

#define CENTER 0
#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4
#define PUSH 5

///////////////////////////////////////

#define BLUE_LED 9
#define GREEN_LED 10
#define RED_LED 11

#define POTENCIOMETR 3

#define PIEZZO 5

#define HORIZONTAL 0
#define VERTICAL 1

#define ON 1
#define OFF 0

#define OFFSET 20

int lastState = LOW;
int currentState = HIGH;

int button = HIGH;


int readJoystickKey(int xPos, int yPos){
    if (button == LOW) {
      return PUSH;
    }

    if (yPos > UP_TRESHOLD) {     // joystick je nahoře
      return UP;
    }

    if (yPos < DOWN_TRESHOLD) {   // joystick je dole
      return DOWN;
    }

    if (xPos > RIGHT_TRESHOLD) {  // joystick je vpravo
      return RIGHT;
    }

    if (xPos < LEFT_TRESHOLD) {   // joystick je vlevo
      return LEFT;
    }

    return CENTER;
}

void check_button(int pin, char string[]){
  currentState = digitalRead(pin);

  if(currentState == LOW){
    lastState = LOW;  
  }
  
  if(lastState == LOW && currentState == HIGH){
      lastState = currentState;
      Serial.println(string);
  }
}

void setup()
{
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  pinMode(2, INPUT_PULLUP); // BUTTON
  //pinMode(POTENCIOMETR, INPUT);
  
  Serial.begin(9600);
}

int frekvence_own = 0;

void loop()
{
  
  int x = analogRead(HORIZONTAL);
  int y = analogRead(VERTICAL);
  
  x = map(x, 0, 1023, -255, 255);
  y = map(y, 0, 1023, -255, 255);

  if (!digitalRead(2)) {

    frekvence_own = analogRead(POTENCIOMETR);
    frekvence_own = map(frekvence_own, 0, 1023, 0, 255);

    tone(PIEZZO, frekvence_own);

  } else{
    noTone(PIEZZO);
  }

  int pos_joystick = readJoystickKey(x, y);

  //frekvence_own = map(frekvence_own, 0, 1023, 0, 255);
  
  Serial.println("frekvence_own:");
  Serial.println(frekvence_own);
  
      switch (pos_joystick)
      {
        case LEFT:
          analogWrite(RED_LED, frekvence_own);
          break;
        case RIGHT:
          analogWrite(BLUE_LED, frekvence_own);
          break;
        case UP:
          analogWrite(BLUE_LED, frekvence_own);
          break;
        case DOWN:
          analogWrite(GREEN_LED, frekvence_own);
            break;
        case CENTER:
          analogWrite(RED_LED, 0);
          analogWrite(GREEN_LED, 0);
          analogWrite(BLUE_LED, 0);
          break; 
        //case PUSH:
      }
}
