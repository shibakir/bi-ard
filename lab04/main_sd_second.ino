#include <Esplora.h>
#include <SD.h>
#include <SPI.h>
#include <TFT.h>
#include <EEPROM.h>

#define SHIFT 20
#define SD_CS    8         // Chip select line for SD card in Esplora
PImage logo;

void setup() {

  EEPROM.update(0,0);     // Ukládám hodnotu 0 na adresu 0 v paměti EEPROM.
  EEPROM.update(1,0);     // Ukládám hodnotu 0 na adresu 1 v paměti EEPROM.
  
  // initialize the GLCD and show a message
  // asking the user to open the serial line
  EsploraTFT.begin();

  // make the background black
  EsploraTFT.background(0,0,0);
  // set the text color to white
  EsploraTFT.stroke(255,255,255);

  EsploraTFT.println();
  //EsploraTFT.println(F("File system root: "));
  //EsploraTFT.text("File system root: ", 0, 10);

  while ( !SD.begin(SD_CS) ){
     EsploraTFT.text("No SD card is avaliable! ", 0, 20);
     //while(1);
  } 
    EsploraTFT.background(0, 0, 0);
    //EsploraTFT.text("File system root: ", 0, 10);
    EsploraTFT.text("SD card is avaliable! ", 0, 20);
    

    //readSDRoot("/");

    //File root = SD.open("/");

    //if ( ! root.exists("bi-ard.bmp") ) {
      if ( ! SD.exists("bi-ard.bmp") ){

        EsploraTFT.text("bi-ard.bmp missing!", 0, 30);
        delay(2000);
        //exit(0);
        return;
    } else {
      
         EsploraTFT.text("bi-ard.bmp exists!", 0, 30); 
         delay(2000);
  
         EsploraTFT.background(0, 0, 0);

        // load the image into the named instance of PImage
        logo = EsploraTFT.loadImage("bi-ard.bmp");

        if (logo.isValid()) {
          Esplora.writeGreen(255);
        }else{
          // if it is not valid, turn the LED red
          Esplora.writeRed(255);
        }
      
        EsploraTFT.image(logo, 0, 0);
    }
    
}

int width = EsploraTFT.width();
int height = EsploraTFT.height();

void loop() {
  // put your main code here, to run repeatedly:

  int valueX = Esplora.readJoystickX();
  int valueY = Esplora.readJoystickY();
 
}
