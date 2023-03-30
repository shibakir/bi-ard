#define RED_PIN  11
#define GREEN_PIN 12
#define BLUE_PIN   13

#define HORIZONTAL 0
#define VERTICAL 1

void setup() {
  Serial.begin(9600);
  
  pinMode ( BLUE_PIN , OUTPUT );    // set BLUE_PIN as OUTPUT
  pinMode ( GREEN_PIN , OUTPUT );   // set GREEN_PIN as OUTPUT
  pinMode ( RED_PIN , OUTPUT );     // set RED_PIN as OUTPUT

  digitalWrite(RED_PIN, 1);
}

void turnOffAll() {
   digitalWrite(RED_PIN, 0);
   digitalWrite(GREEN_PIN, 0);
   digitalWrite(BLUE_PIN, 0); 
}

int pinoutLED = 11;

void loop() {

  while (Serial.available() == 0) {
  }

  int barva = Serial.parseInt();

  int x = analogRead(HORIZONTAL);
  int y = analogRead(VERTICAL);

  Serial.print( x );

  turnOffAll();
  delay(1000);

  switch (barva) {
    case 1:
      pinoutLED = 11;
      break;

    case 2:
      pinoutLED = 12;
      break;

    case 3:
      pinoutLED = 13;
      break;

    default:
      Serial.println("Unknown LED");
  }

  digitalWrite(pinoutLED, 1);
  delay(1000);
}
