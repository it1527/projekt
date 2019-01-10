//Důvod, proč používám delay a ne millis, je popsán v souboru i s příkladem: Millis_trouble
//ktery naleznete na mém Githubu:  https://github.com/it1527/projekt/tree/master/Millis_trouble
#include <Adafruit_Fingerprint.h>// knihovna čtečky
// lcd knihovny
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <SoftwareSerial.h> //knihovna serialu
SoftwareSerial mySerial(2, 3); //definovani pinu serialu
LiquidCrystal_I2C lcd(0x3F,16,2);  // nastaveni adresy I2C modulu a 16 pismen a 2 radky
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);  //prirazeni serialu čtečce

int radek1 = 0; // nastaveni promene pro radek displeje
int radek2 = 0;
int LEDzelena = 4;
int LEDcervena = 5;
//unsigned long previousMillis = 0;  
//const long delay1S = 1000;

void setup()  
{
  Serial.begin(9600);
  //LCD
  lcd.init();                // initialize lcd 
  lcd.backlight();          // podsviceni lcd
  pinMode(LEDzelena, OUTPUT); 
  pinMode(LEDcervena, OUTPUT);
  while (!Serial);      //Z duvodu některých platforem  
  delay(100);
  Serial.println("Inicializace senzoru, prosím o strpení.."); //Vypis hlasky na consoli
  LCD(radek1 = 1, radek2 = 1); //Vypis na lcd monitor pomoci funkce, cisla znaci poradi hlasek v poli.
  
  // nasteaveni rychlosti ctecky
  finger.begin(57600);
  
  if (finger.verifyPassword()) { //overeni zda je senzor pripojen a pripraven k pouziti
    Serial.println("Senzor nalezen!");
    LCD(radek1 = 2, radek2 = 2);
  } else { //větev ne
    Serial.println("Senzor nenalezen..");
    LCD(radek1 = 2, radek2 = 3);
    while (1) { delay(1); }
  }

  finger.getTemplateCount(); //vraci pocet ulozenych sablon otisku
  Serial.print("Senzor obsahuje "); Serial.print(finger.templateCount); Serial.println(" šablon");
  LCD(radek1 = 3, radek2 = 0);
  lcd.print(finger.templateCount);
  lcd.print("  sablon");
  Serial.println("Přiložte prst");
  LCD(radek1 = 6, radek2 = 0);
}
void loop()                   
{
  getFingerprintIDez(); 
  //digitalWrite(LEDcervena, HIGH);
  digitalWrite(LEDzelena, LOW);
  delay(50);           
}

void LCD(int i, int j){
  //if (currentMillis - previousMillis >= delay1S) {
  // previousMillis = currentMillis;
  
  // pole v niz jsou ulozeny hlasky, ktere jsou vypisovany podle pridelenych id
  //                       0          1              2            3                     4                  5              6               7                 8            9                   10              11
   char* hlasky_radek_1[]={"", "Inicializace..", "Senzor ","Senzor obsahuje", "","Nezadal si cislo", "Prilozte prst", "Otisk ulozen", "Chyba senzoru!","Chyba otisku!", "Neznama chyba!","Otisk preveden",
   "Spatna kvalita", "Chyba funkce!", "Odstrante prst", "Otisky se" , "Otisk nebyl", " Chyba ulozeni", "Prst nebyl", "Otisky se"};
   //      12             13                  14              15           16                 17          18              19
   //                      0          1                2          3                 4            5         6        7           8           9           10             11         12
   char* hlasky_radek_2[]={"", "Prosim strpeni", "nalezen :)","nenalezen :(", "obsahuje: ","otisku", "znovu", "shoduji", "neshoduji","do pameti!", "ulozen pod:","do pameti", "prilozen!"};
   lcd.init();
   lcd.setCursor(0,0); //nastaveni cursoru na radek 1 a pozici 1
   lcd.print(hlasky_radek_1[i]); //vypsani hlasky na radek 1 disleje
   lcd.setCursor(0,1); //nastaveni cursoru na radek 2 a pozici 1
   lcd.print(hlasky_radek_2[j]); //vypsani hlasky na radek 2 disleje
   delay(500); //spomaleni hlasek na dispeji
   //Serial.println(hlasky_radek_1[i]); pomocne vypisy
   //Serial.println(hlasky_radek_2[j]);
   //Serial.println(previousMillis);
   //Serial.println(currentMillis);
   //}
  }

uint8_t getFingerprintID() { //funkce pro rozpoznani otisku
  uint8_t p = finger.getImage(); //s tehle funkce se da ziskat sablona otisku funkce
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Otisk uložen");
      LCD(radek1 = 7, radek2 = 0);
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("Nebyl přiložen prst");
      LCD(radek1 = 18, radek2 = 12);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Chyba komunikace se senzorem");
      LCD(radek1 = 8, radek2 = 0);
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Chyba při snímání otisku!");
       LCD(radek1 = 9, radek2 = 0);
      return p;
    default:
      Serial.println("Neznámá chyba!");
      LCD(radek1 = 10, radek2 = 0);
      return p;
  }

  
  

  p = finger.image2Tz(); //prevedeni otisku
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Otisk převeden");
      LCD(radek1 = 11, radek2 = 0);
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Špatná kvalita otisku");
      LCD(radek1 = 12, radek2 = 5);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Chyba komunikace se senzorem");
      LCD(radek1 = 8, radek2 = 0);
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Chyba funkce otisku prstu!");
      LCD(radek1 = 13, radek2 = 0);
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Chyba funkce otisku prstu!");
      LCD(radek1 = 13, radek2 = 0);
      return p;
    default:
      Serial.println("Neznámá chyba!");
      LCD(radek1 = 10, radek2 = 0);
      return p;
  }
  
  
  p = finger.fingerFastSearch(); //rozlyšuje zda se otisky shodji či na ne
  if (p == FINGERPRINT_OK) {
    Serial.println("Otisky se shoduji");
    LCD(radek1 = 19, radek2 = 7);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Chyba komunikace se senzorem");
    LCD(radek1 = 8, radek2 = 0);
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Otisky se neshoduji");
    LCD(radek1 = 19, radek2 = 8);
    return p;
  } else {
    Serial.println("Neznámá chyba!");
    LCD(radek1 = 10, radek2 = 0);
    return p;
  }   
  
  // shoda otisku
  Serial.print("ID otisku: "); 
  Serial.print(finger.fingerID); //vraci ID otisku
  Serial.print(" s přesností: "); 
  Serial.println(finger.confidence); //vraci presnost shody
  lcd.init();
  lcd.setCursor(0,0); 
  lcd.print("ID otisku: ");
  lcd.print(finger.fingerID);
  lcd.setCursor(0,1); 
  lcd.print("Presnost: ");
  lcd.print(finger.confidence); 
  return finger.fingerID; //vraci id otisku
}

// funkce vracejici id, vraci -1 kdyz se nepovede zjistit id
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  //shoda otisku
//  digitalWrite(LEDcervena, LOW);
  digitalWrite(LEDzelena, HIGH);
  //delay(1000);
  //digitalWrite(LEDzelena, LOW);
  //delay(1000);
 // digitalWrite(LEDcervena, HIGH);
  Serial.print("ID otisku: ");
  Serial.print(finger.fingerID); 
  Serial.print(" s přesností: ");
  Serial.println(finger.confidence);
  lcd.init();
  lcd.setCursor(0,0); 
  lcd.print("ID otisku: ");
  lcd.print(finger.fingerID);
  lcd.setCursor(0,1); 
  lcd.print("Presnost: ");
  lcd.print(finger.confidence); 
  
  return finger.fingerID; //vraci id otisku
}
