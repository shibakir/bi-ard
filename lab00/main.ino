#define RED 13              // číslo pinu, na kterém je červená LED
#define GREEN 12            // číslo pinu, na kterém je zelená LED
#define BLUE 11             // číslo pinu, na kterém je modrá LED

#define DOT 200             // doba bliknutí tečky
#define DASH 800            // doba bliknutí čárky
#define NO_LIGHT 200        // doba vypnutí LED mezi jednotlivými bliknutími

int color = RED;
int count = 1;

int lastState = LOW;
int currentState = HIGH;

void flash(int outPin, int doba){
  // parametr duration určuje dobu, kdy je LED zapnutá

    unsigned long time_now = millis();
    
    digitalWrite(color, 1);
    
    while(millis() < time_now + doba){
      check_button();
    }
    digitalWrite(color, 0);
    time_now = millis();
    while(millis() < time_now + NO_LIGHT){
      check_button();      
    }
} 

void morse(int outPin){

    flash(outPin, DOT);
    flash(outPin, DASH);

    flash(outPin, DOT);
    flash(outPin, DASH);
    flash(outPin, DOT);

    flash(outPin, DASH);
    flash(outPin, DOT);
    flash(outPin, DOT);
}

void check_button(){

  currentState = digitalRead(2);

  if(currentState == LOW){
    lastState = LOW;  
  }
  
  if(lastState == LOW && currentState == HIGH){
      count++;
      lastState = currentState;
  }

   count = count % 4;
  
  switch(count){
    case 1:
      color = RED;
      digitalWrite(GREEN, 0);
      digitalWrite(BLUE, 0);
      break;
    case 2:
      color = GREEN;
      digitalWrite(RED, 0);
      digitalWrite(BLUE, 0);
        break;
    case 3:
      color = BLUE;
      digitalWrite(GREEN, 0);
      digitalWrite(RED, 0);
        break;
    default:
      color = RED;
      digitalWrite(GREEN, 0);
      digitalWrite(BLUE, 0);
      break;
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(2, INPUT_PULLUP);

}


void loop() {
  // put your main code here, to run repeatedly:

  morse(color);
  
}
