#define RED_LED 9
#define GREEN_LED 10
#define BLUE_LED 11
#define YELLOW_LED 12

#define SWITCH_1 2
#define SWITCH_2 3
#define SWITCH_3 4
#define SWITCH_4 5

#define ON 1
#define OFF 0

void setup()
{
  pinMode(SWITCH_1, INPUT_PULLUP);
  pinMode(SWITCH_2, INPUT_PULLUP);
  pinMode(SWITCH_3, INPUT_PULLUP);
  pinMode(SWITCH_4, INPUT_PULLUP);
  
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  Serial.begin(9600);
}

void pushLED(int led, int val){
  digitalWrite(led, val);
}

int counter = 0;
int catched = 0;

void loop()
{
  int num = (random(60000) % 4);             // je třeba, aby barvy blikaly náhodně

  switch(num)
  {
    case 0:
      pushLED(RED_LED, ON);
      push_button(SWITCH_1, "red");       // pokud se rozsvítí červená LED, musíte zmáčknout SWITCH 1
      pushLED(RED_LED, OFF);
      break;

    case 1:
      //zde rozsviťte zelenou RGB LED
      pushLED(GREEN_LED, ON);
      push_button(SWITCH_2, "green");     // pokud se rozsvítí zelená LED, musíte zmáčknout SWITCH 2
      pushLED(GREEN_LED, OFF);
      break;

     case 2:
      //zde rozsviťte modrou RGB LED
      pushLED(BLUE_LED, ON);
      push_button(SWITCH_3, "blue");       // pokud se rozsvítí modrá LED, musíte zmáčknout SWITCH 3
      pushLED(BLUE_LED, OFF);
      break;

     case 3:
      //zde rozsviťte žlutou RGB LED
      pushLED(YELLOW_LED, ON);
      push_button(SWITCH_4, "yellow");     // pokud se rozsvítí žlutá LED, musíte zmáčknout SWITCH 4
      pushLED(YELLOW_LED, OFF);
      break;
  }

   if(counter >= 30)
   {

    Serial.print("Your score is "); 
    Serial.print(catched);

    if( counter > 15 ) // byla správně zmáčknuta více než polovina tlačítek
    {
      Serial.println("* Winner! *");
    }
    else
    {
      Serial.println("* Loser! *");
    }
    counter = 0;
    catched = 0;
  }
 }

void push_button( int btn, char color[] )
{
    for(int i=0; i < 4000; i++)                    // velikost i určuje dobu rozsvícení LED
    {
      if( !digitalRead(btn) )
      {
        if(digitalRead(SWITCH_1)+digitalRead(SWITCH_2)+digitalRead(SWITCH_3)+digitalRead(SWITCH_4) == 3)
        {
          Serial.println(color);
          catched++;
          break;
        }
      }
    }
}
