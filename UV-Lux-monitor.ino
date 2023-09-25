/* Code voor een DIGITALE lux/UV monitor
met een LTR 390 sensor van Adafruit weergegeven
op een i2c 26x2 lcd MONOCHROME display 
via Adafruit_RGBLCDShield.h library */ 


#include <Wire.h>
#include <LTR390.h>
#include <Adafruit_RGBLCDShield.h>
#include <OneWire.h>
#define I2C_ADDRESS 0x53

LTR390 ltr390(I2C_ADDRESS);
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// Instelling van de achtergrondkleur = White voor momochroom display
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7 // Enkel WHITE wordt hier gebruikt voor een monocroom LCD

void setup() {
   lcd.setBacklight(WHITE); //Zet monochroom op witte letters
   lcd.begin(16, 2); // Initialiseer het 16 digit LCD en 2 rijen.

  Serial.begin(115200); // Initialiseer de sefriële monitor op 115200 Baud

// Controle van de werking van de ltr390...
  Wire.begin();
  if(!ltr390.init()){
    Serial.println("LTR390 not connected!"); // Controle werking van de ltr390
  }
  ltr390.setMode(LTR390_MODE_ALS);
  ltr390.setGain(LTR390_GAIN_3);
  lcd.setCursor(0,0);
  Serial.print("Gain : ");
  switch (ltr390.getGain()) {
    case LTR390_GAIN_1: Serial.print(1); break;
    case LTR390_GAIN_3: Serial.print(3); break;
    case LTR390_GAIN_6: Serial.print(6); break;
    case LTR390_GAIN_9: Serial.print(9); break;
    case LTR390_GAIN_18: Serial.print(18); break;
  }
  
  ltr390.setResolution(LTR390_RESOLUTION_18BIT);
  lcd.setCursor(0,1);
  Serial.print("Resolution : ");
  switch (ltr390.getResolution()) {
    case LTR390_RESOLUTION_13BIT: Serial.print(13); break;
    case LTR390_RESOLUTION_16BIT: Serial.print(16); break;
    case LTR390_RESOLUTION_17BIT: Serial.print(17); break;
    case LTR390_RESOLUTION_18BIT: Serial.print(18); break;
    case LTR390_RESOLUTION_19BIT: Serial.print(19); break;
    case LTR390_RESOLUTION_20BIT: Serial.print(20); break;
  }
delay(5000);
 }
/* Weergave van:
Lichtsterkte (LUX) op de eerste lijn (Geheel getal)
UV-index op de tweede lijn met 2 cijfers achter de komma
*/
void loop() {
  if (ltr390.newDataAvailable()) {
(ltr390.getMode() == LTR390_MODE_ALS);
     if (ltr390.getMode() == LTR390_MODE_ALS) {
     lcd.setCursor(5,0);
     lcd.print("     ");
     lcd.setCursor(0,0);
     lcd.print("Lux: "); 
     lcd.print(ltr390.getLux(),0);
     ltr390.setGain(LTR390_GAIN_18); 
      //Recommended for Lux - x18
      ltr390.setResolution(LTR390_RESOLUTION_20BIT); 
      //Recommended for Lux - 20-bit
      ltr390.setMode(LTR390_MODE_UVS);
     
      } else if (ltr390.getMode() == LTR390_MODE_UVS) {
      lcd.setCursor(0,1);
      lcd.print("UV Index: "); 
      lcd.print(ltr390.getUVI(),2);
      ltr390.setGain(LTR390_GAIN_3);     
      //Aanbevolen voor UVI: x3
      ltr390.setResolution(LTR390_RESOLUTION_18BIT);  
      //Aanbevolen voor UVI: 18-bit
      ltr390.setMode(LTR390_MODE_ALS);
      }
    }

// **** DE DRUKKNOPPEN VAN HET LCD INITIALISEREN EN INLEZEN **** //
// **** OPMERKING: DE RESET IS VIA DE HARWARE GECONNECTEERD **** //
// **** LCD-Shield: pen 1 naar RESET van de Arduino One *****//
uint8_t i=0;
uint8_t buttons = lcd.readButtons();

// *** PROGRAMMATIE KNOP OMHOOG *** //
  if (buttons & BUTTON_UP) {
    ltr390.setMode(LTR390_MODE_ALS);
    (ltr390.getMode() == LTR390_MODE_ALS);
    lcd.setCursor(5,0);
    ltr390.setGain(LTR390_GAIN_18); 
    ltr390.setResolution(LTR390_RESOLUTION_20BIT); 
  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print ("UV-INDEX =  ");
    lcd.print(ltr390.getUVI());
    ltr390.setMode(LTR390_MODE_ALS);

    if (ltr390.getUVI() < 1.00) {
    lcd.setCursor(0,1);
    lcd.print ("Code Groen");
  }  
    if ((ltr390.getUVI() >= 1) && (ltr390.getUVI() < 2.00 )){
    lcd.setCursor(0,1);
    lcd.print ("Code Geel");
    }  
    if ((ltr390.getUVI() >= 2.00) && (ltr390.getUVI() < 3.00 )){
    lcd.setCursor(0,1);
    lcd.print ("Code Oranje");
    }  
    if ((ltr390.getUVI() >= 3.00) && (ltr390.getUVI() < 4.00 )){
    lcd.setCursor(0,1);
    lcd.print ("Rood");
    }
    if ((ltr390.getUVI() >= 4.00) && (ltr390.getUVI() < 5.00 )){
    lcd.setCursor(0,1);
    lcd.print ("Code Blauw ");
    }  
    if ((ltr390.getUVI() >= 5.00) && (ltr390.getUVI() < 6.00 )){
    lcd.setCursor(0,1);
    lcd.print ("Code Paars");
    }
    if ((ltr390.getUVI() >= 6.00) && (ltr390.getUVI() < 7.00 )){
    lcd.setCursor(0,1);
    lcd.print ("Code Paars");
    }
    if (ltr390.getUVI() >= 7.00) {
    lcd.setCursor(0,1);
    lcd.print ("EXTREEM VEEL UV");
    }
   delay (5000);
   lcd.clear();
  }
// *** PROGRAMMATIE KNOP RIGHT *** //
  if (buttons & BUTTON_RIGHT) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print ("UV-INDEX =  ");
  lcd.print(ltr390.getUVI());
      
  if (ltr390.getUVI() < 1.00) {
  lcd.setCursor(0,1);
  lcd.print ("VEILIG");
  }  
  if ((ltr390.getUVI() >= 1.00) && (ltr390.getUVI() < 2.00 )){
  lcd.setCursor(0,1);
  lcd.print ("INSMEREN");
  }  
  if ((ltr390.getUVI() >= 2.00) && (ltr390.getUVI() < 3.00 )){
  lcd.setCursor(0,1);
  lcd.print ("Reg. INSMEREN");
  }  
  if ((ltr390.getUVI() >= 3.00) && (ltr390.getUVI() < 4.00 )){
  lcd.setCursor(0,1);
  lcd.print ("Reg. INSMEREN + ");
  }  
  if ((ltr390.getUVI() >= 4.00) && (ltr390.getUVI() < 5.00 )){
  lcd.setCursor(0,1);
  lcd.print ("Reg. INSMEREN ++");
  }
  if ((ltr390.getUVI() >= 5.00) && (ltr390.getUVI() < 6.00 )){
  lcd.setCursor(0,1);
  lcd.print ("Reg. INSMEREN +++");
  }
  if (ltr390.getUVI() >= 6.00) {
  lcd.setCursor(0,1);
  lcd.print ("BINNEN BLIJVEN");
  }
  delay (5000);
  lcd.clear();
  }

// *** PROGRAMMATIE KNOP SELECT *** //
   if (buttons & BUTTON_SELECT) {
   ltr390.setMode(LTR390_MODE_ALS);
   (ltr390.getMode() == LTR390_MODE_ALS);
   lcd.setCursor(5,0);
   lcd.clear();
   lcd.setCursor(0,0);
   ltr390.setGain(LTR390_GAIN_18); 
   //Recommended for Lux - x18
   ltr390.setResolution(LTR390_RESOLUTION_20BIT); 
   //Recommended for Lux - 20-bit
      
   lcd.print ("UV-INDEX =  ");
   lcd.print(ltr390.getUVI());
   ltr390.setMode(LTR390_MODE_ALS);

   if (ltr390.getUVI() < 1.00) {
   lcd.setCursor(0,1);
   lcd.print ("VEILIG");
   }  
   if ((ltr390.getUVI() >= 1.00) && (ltr390.getUVI() < 2.00 )){
   lcd.setCursor(0,1);
   lcd.print ("INSMEREN");
   }  
   if ((ltr390.getUVI() >= 2.00) && (ltr390.getUVI() < 3.00 )){
   lcd.setCursor(0,1);
   lcd.print ("Reg. INSMEREN");
   }  
   if ((ltr390.getUVI() >= 3.00) && (ltr390.getUVI() < 4.00 )){
   lcd.setCursor(0,1);
   lcd.print ("Reg. INSMEREN + ");
   }  
   if ((ltr390.getUVI() >= 4.00) && (ltr390.getUVI() < 5.00 )){
   lcd.setCursor(0,1);
   lcd.print ("Reg. INSMEREN ++");
   }
   if ((ltr390.getUVI() >= 5.00) && (ltr390.getUVI() < 6.00 )){
   lcd.setCursor(0,1);
   lcd.print ("Reg. INSMEREN +++");
   }
   if (ltr390.getUVI() >= 6.00) {
   lcd.setCursor(0,1);
   lcd.print ("BINNEN BLIJVEN");
   }
      
   delay (5000);
   lcd.clear();
  }
   
 // *** PROGRAMMATIE KNOP LEFT *** //
  if (buttons & BUTTON_LEFT) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print ("Software V1.2"); 
  lcd.setCursor(0,1);
  lcd.print ("Sept. 2023");
  delay (3000);
  }

  // *** PROGRAMMATIE KNOP DOWN *** //
  if (buttons & BUTTON_DOWN) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print ("Vrije"); 
  lcd.setCursor(0,1);
  lcd.print ("Ruimte");
  delay (3000);
  }
}

