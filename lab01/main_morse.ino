#define DOT 200
#define DASH 800
#define NO_LIGHT 200

#define ABC_SHIFT 97
#define ABC_LENGTH 26

char* letters[]={
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",  // A-G
  "...." , "..", ".---", "-.-", ".-..", "--", "-.", // H-N
  "---", ".--.", "--.-", ".-.", "...", "-", "..-",  // O-U
  "...-", ".--", "-..-", "-.--", "--.."             // V-Z
};
char inputKey = 0;

void flash(int value) {
  digitalWrite(9, value);
  digitalWrite(10, value);
  digitalWrite(11, value);
}

void charToSignal(char* message, int size) {

  for (int i = 0; i < size; i++) {
    flash(1);
    if (message[i] == '.') {
      delay(DOT);
    } else if (message[i] == '-') {
      delay(DASH);
    }
    flash(0);
    delay(NO_LIGHT);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  Serial.println("Start.");
}

void loop() {

  // reply only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    inputKey = Serial.read();

    // say what you got:
    if((inputKey >= 97) && (inputKey < 97 + ABC_LENGTH)){
      Serial.println(inputKey);
      charToSignal(letters[inputKey - ABC_SHIFT], strlen(letters[inputKey - ABC_SHIFT]));
    } else{
      //Serial.print("Unknown symbol!");
      //delay(500);
    }
    
  }
}
