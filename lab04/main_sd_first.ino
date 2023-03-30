#include <Esplora.h>
#include <SD.h>
#include <SPI.h>
#include <TFT.h>
#include <EEPROM.h>

#define SHIFT 20
#define SD_CS    8         // Chip select line for SD card in Esplora

void setup() {

  // initialize the GLCD and show a message
  // asking the user to open the serial line
  EsploraTFT.begin();

  // make the background black
  EsploraTFT.background(0,0,0);
  // set the text color to white
  EsploraTFT.stroke(255,255,255);

  EsploraTFT.println();
  //EsploraTFT.println(F("File system root: "));
  EsploraTFT.text("File system root: ", 0, 10);

  while ( !SD.begin(SD_CS) ){
     EsploraTFT.text("No SD card is avaliable! ", 0, 20);
     //while(1);
  } 
    EsploraTFT.background(0, 0, 0);
    EsploraTFT.text("File system root: ", 0, 10);
    EsploraTFT.text("SD card is avaliable! ", 0, 20);
    EsploraTFT.text("Context: ", 0, 30);

    readSDRoot("/");
}
int counterX = 40;
int counterY = 0;


File file;

void readSDRoot(String rootString){

   File root = SD.open(rootString);
  
  while( true ) {

    if (! (file = root.openNextFile()) ){
      break; 
    } else {
      //String filename = file.name();
      //filename.concat("/");
      if ( file.isDirectory() ){
        EsploraTFT.text(file.name(), counterY, counterX);
        counterX += 10;
        counterY += SHIFT;
        
        readSDRoot(file.name());  
        
      } else{
        EsploraTFT.text(file.name(), counterY, counterX);
        counterX += 10;
      }
    }
    
  }
  counterY = 0;
  //EsploraTFT.text(file.name(), 0, 50);
}

void loop() {
  // put your main code here, to run repeatedly:
}
