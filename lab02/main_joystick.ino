#define BLUE_LED 9
#define GREEN_LED 10
#define RED_LED 11

#define HORIZONTAL 0
#define VERTICAL 1

#define ON 1
#define OFF 0

#define OFFSET 20

void setup() 
{
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  int x = analogRead(HORIZONTAL);
  int y = analogRead(VERTICAL);
  
  x = map(x, 0, 1023, -255, 255);
  y = map(y, 0, 1023, -255, 255);

  if (abs(x) < OFFSET && abs(y) < OFFSET)
  {
    analogWrite(RED_LED, 0);
    analogWrite(GREEN_LED, 0);
    analogWrite(BLUE_LED, 0); 
  } else
  {
    if(x > 0){
      analogWrite(RED_LED, x);
    } else {
      analogWrite(GREEN_LED, -x);
    } 
    if(y > 0){
      analogWrite(RED_LED, y);
    } else {
      analogWrite(BLUE_LED, -y);
    } 
  }

  

  Serial.println("x:");
  Serial.println(x);

  Serial.println("y:");
  Serial.println(y);
  
  
}
