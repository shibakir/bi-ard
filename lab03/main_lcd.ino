#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DOWN  5  // SW1
#define UP    4  // SW4
#define ENTER 6 // SW2
#define BACK  7 // SW3



LiquidCrystal_I2C lcd(0x27, 16, 2); // inicialization of LCD display

enum states {
  HOME_FIRST_STATE, HOME_SECOND_STATE, HOME_THIRD_STATE, T_STATE, LIGHT_STATE, A_STATE
};
enum states STATE, NEXT_STATE;


char startMenuFirstFirst[] = "> 1.Temperature";
char startMenuFirstSecond[] = "2.Light";

char startMenuSecondFirst[] = "1.Temperature";
char startMenuSecondSecond[] = "> 2.Light";

char startMenuThirdFirst[] = "> 3.Acce";
char empty_line[] = "       ";

byte buttonFlag = 0;

bool buttonEvent(int button)
{
  switch(button)
  {
    case UP:
     if (digitalRead(UP) == LOW)
     {
       buttonFlag |= 1;
     } else if (buttonFlag & 1)
     {
       buttonFlag ^= 1;
       return true;
     }
     break;

    case DOWN:
     if (digitalRead(DOWN) == LOW)
     {
       buttonFlag |= 2;
     } else if (buttonFlag & 2)
     {
       buttonFlag ^= 2;
       return true;
     }
     break;

    case BACK:
     if (digitalRead(BACK) == LOW)
     {
       buttonFlag |= 4;
     } else if (buttonFlag & 4)
     {
       buttonFlag ^= 4;
       return true;
     }
     break;

    case ENTER:
     if (digitalRead(ENTER) == LOW)
     {
       buttonFlag |= 8;
     } else if (buttonFlag & 8)
     {
       buttonFlag ^= 8;
       return true;
     }
  }
   return false;
}

void change_position(char a[], char b[]){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(a);
    lcd.setCursor(0,1);
    lcd.print(b);
}

void draw_temp(double temp){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp is:");
    lcd.setCursor(0,1);
    lcd.print(temp);
    delay(50);
}

void draw_light(int light){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Light is:");
    lcd.setCursor(0,1);
    lcd.print(light);
    delay(50);
}

void display_menu(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(startMenuFirstFirst);
    lcd.setCursor(0,1);
    lcd.print(startMenuFirstSecond);
}

void draw_acce(int potenc){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Acce is:");
    lcd.setCursor(0,1);
    lcd.print(potenc);
    delay(50);
}


void setup() {
 // Proveďte inicializaci displeje
  pinMode(4, INPUT_PULLUP); // BUTTON
  pinMode(5, INPUT_PULLUP); // BUTTON
  pinMode(6, INPUT_PULLUP); // BUTTON
  pinMode(7, INPUT_PULLUP); // BUTTON
 
  lcd.init();
  lcd.init();
  lcd.backlight();
  display_menu();                             
  STATE = HOME_FIRST_STATE;
  NEXT_STATE = HOME_FIRST_STATE;
}

void loop(){

  double temperature_num = analogRead(0);
  int light_num = analogRead(1);

  temperature_num = map(temperature_num, 0, 1023, 0, 500) - 273.15;
  light_num = map(light_num, 0, 1023, 0, 100);

  int potenc_num = analogRead(2);
  potenc_num = map(potenc_num, 0, 1023, 0, 100);
  

    switch (STATE){
    case HOME_FIRST_STATE:
      if (buttonEvent(DOWN)) {
        NEXT_STATE = HOME_SECOND_STATE; 
        change_position(startMenuSecondFirst, startMenuSecondSecond);
        }
      if (buttonEvent(ENTER)) {
        NEXT_STATE = T_STATE; 
        draw_temp(temperature_num);
        }
      break;
    case HOME_SECOND_STATE:
      if (buttonEvent(UP)) {
        NEXT_STATE = HOME_FIRST_STATE; 
        change_position(startMenuFirstFirst, startMenuFirstSecond);
      }
      if (buttonEvent(DOWN)) {
        NEXT_STATE = HOME_THIRD_STATE; 
        change_position(startMenuThirdFirst, empty_line);
      }
      if (buttonEvent(ENTER)) {
        NEXT_STATE = LIGHT_STATE;
        draw_light(light_num);
      }
      break;
    case HOME_THIRD_STATE:
      if (buttonEvent(UP)) {
        NEXT_STATE = HOME_SECOND_STATE; 
        change_position(startMenuSecondFirst, startMenuSecondSecond);
      } 
      if (buttonEvent(ENTER)) {
        NEXT_STATE = A_STATE; 
        draw_acce(potenc_num);
      }
      break;
    case T_STATE:
      draw_temp(temperature_num);
      if (buttonEvent(BACK)) {
        NEXT_STATE = HOME_FIRST_STATE; 
        change_position(startMenuFirstFirst, startMenuFirstSecond);
      }
      break;
    case LIGHT_STATE:
      draw_light(light_num);
      if (buttonEvent(BACK)) {
        NEXT_STATE = HOME_SECOND_STATE; 
        change_position(startMenuSecondFirst, startMenuSecondSecond);
      }
      break;
    case A_STATE:
      draw_acce(potenc_num);
      if (buttonEvent(BACK)) {
        NEXT_STATE = HOME_THIRD_STATE; 
        change_position(startMenuThirdFirst, empty_line);
      }
      break;
  };

  STATE = NEXT_STATE;
}
