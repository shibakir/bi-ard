#define RED_PIN  11
#define GREEN_PIN 12
#define BLUE_PIN   13

const int up_button       = 2;
const int down_button     = 4;
const int left_button     = 5;
const int right_button    = 3;
const int joystick_button = 8;

volatile int pinoutLED = 11;
bool state = true;

void setup () {
  // put your setup code here, to run once:
  pinMode ( BLUE_PIN , OUTPUT );    // set BLUE_PIN as OUTPUT
  pinMode ( GREEN_PIN , OUTPUT );   // set GREEN_PIN as OUTPUT
  pinMode ( RED_PIN , OUTPUT );     // set RED_PIN as OUTPUT

  pinMode ( up_button , INPUT_PULLUP );
  attachInterrupt(digitalPinToInterrupt( up_button ) , changeState , RISING );
}

void changeState () {
    int pinoutLEDLast = pinoutLED;
    if ( pinoutLED == 11) {
      pinoutLED = 12;
    } else if ( pinoutLED == 12 ) {
      pinoutLED = 13;
    } else {
      pinoutLED = 11;
    }
    if ( state ) {
      digitalWrite(pinoutLEDLast, 0);
      digitalWrite(pinoutLED, 1);
    } 
    //digitalWrite(pinoutLED, 1);
} 

void turnOffAll() {
   digitalWrite(RED_PIN, 0);
   digitalWrite(GREEN_PIN, 0);
   digitalWrite(BLUE_PIN, 0); 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pinoutLED, state);
   
  delay(1000);  
  state = !state; 
  turnOffAll();
  delay(200);    
  
}
