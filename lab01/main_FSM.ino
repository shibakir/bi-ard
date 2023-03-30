#define RED_PIN 9              
#define GREEN_PIN 10            
#define BLUE_PIN 11             

#define OWN_DELAY 100

bool checkState = false;

void flash(int pin){
  digitalWrite(pin, 1);
  delay(OWN_DELAY);
  digitalWrite(pin, 0);
}


enum states {
  STATE_START, STATE_SW1, STATE_SW2, STATE_SW1SW2
};

enum states STATE, NEXT_STATE;

void setup() {
  Serial.begin(9600);
  
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  //pinMode(3, INPUT_PULLUP);
  
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  STATE = STATE_START;
}


void loop() {
    int sw1_pressed = !digitalRead(2);
    int sw2_pressed = !digitalRead(3);
    
    switch (STATE)
    {
      case STATE_START:
          
          if (sw1_pressed == true) {
            NEXT_STATE = STATE_SW1;
          } else if (sw2_pressed == true) {
            NEXT_STATE = STATE_SW2;
          }

          checkState = false;
          break;

      case STATE_SW1:
         if(sw2_pressed == true){
          NEXT_STATE = STATE_SW1SW2;
         } else if (sw1_pressed == false) {
          NEXT_STATE = STATE_START;
          
          if (checkState == false){
            Serial.println("AKCE A");
            flash(RED_PIN);

            checkState = true;
            }
         }
         break;

      case STATE_SW2:
        if(sw1_pressed == true){
          NEXT_STATE = STATE_SW1SW2;
         }
         else if (sw2_pressed == false) {
          NEXT_STATE = STATE_START;
          
           if (!checkState){
            Serial.println("AKCE B");
            flash(GREEN_PIN);

            checkState = true;
            }
         }
         break;

      case STATE_SW1SW2:
         if (sw2_pressed == false && sw1_pressed == false) {
          NEXT_STATE = STATE_START;
          
           if (!checkState){
              Serial.println("AKCE C");
              flash(BLUE_PIN);

              checkState = true;
            }
         }
         break;

    }

    STATE = NEXT_STATE;
 }
