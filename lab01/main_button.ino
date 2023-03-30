#define RED_PIN 4
#define GREEN_PIN 3
#define BLUE_PIN 2

#define PUSH_DELAY 100

int lastState = LOW;
int currentState = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

char red[] = "red";
char green[] = "green";
char blue[] = "blue";

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


void loop() {

  if (!digitalRead(RED_PIN)) {

    digitalWrite(11, 1);
    unsigned long time_now = millis();

    while(millis() < time_now + PUSH_DELAY){
      check_button(RED_PIN, red);
    }
    
  } else {

    digitalWrite(11, 0);
  }

  if (!digitalRead(GREEN_PIN)) {

    digitalWrite(10, 1);
    unsigned long time_now = millis();

    while(millis() < time_now + PUSH_DELAY){
      check_button(GREEN_PIN, green);
    }
    
  } else {

    digitalWrite(10, 0);
  }

  if (!digitalRead(BLUE_PIN)) {

    digitalWrite(9, 1);
    unsigned long time_now = millis();

    while(millis() < time_now + PUSH_DELAY){
      check_button(BLUE_PIN, blue);
    }
    
  } else {

    digitalWrite(9, 0);
  }
}
