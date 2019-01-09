//Důvod, proč používám delay a ne millis, je popsán v souboru i s příkladem: Millis_trouble
//ktery naleznete na mém Githubu: 
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
//unsigned long previousMillis = 0;  
//const long delay1S = 1000;


uint8_t id; // nastaveni promenne pod kterou bude ulozen otisk

void setup(){
  Serial.begin(9600); // nastaveni seriove rychlost, musí být na 9600
  //LCD
  lcd.init();                // initialize lcd 
  lcd.backlight();          // podsviceni lcd
  
  while (!Serial);   //Z duvodu některých platforem 
  delay(100);
  Serial.println("Inicializace senzoru, prosím o strpení..");  //Vypis hlasky na consoli
  LCD(radek1 = 1, radek2 = 1); //Vypis na lcd monitor pomoci funkce, cisla znaci poradi hlasek v poli.
  
  
  finger.begin(57600); // nasteaveni rychlosti ctecky
  
  if (finger.verifyPassword()) {  //overeni zda je senzor pripojen a pripraven k pouziti
    Serial.println("Senzor nalezen!"); //větev ano
    LCD(radek1 = 2, radek2 = 2);
  } else { //větev ne
    Serial.println("Senzor nenalezen..");
    LCD(radek1 = 2, radek2 = 3);
    while (1) { delay(1); }
  }
}

uint8_t readnumber(void) { //funkce pro cteni serialu
  uint8_t num = 0; 
  while (num == 0) {
    while (! Serial.available()); //overeni zda je funkci serial, nasledne v kodu nize vypisuje chyby
    num = Serial.parseInt(); 
  }
  return num;
}

void loop(){

  //unsigned long currentMillis = millis(); promena a funkce pro pouziti millis misto delay
  
  Serial.println("Připraven k sejmutí otisku");
    LCD(radek1 = 3, radek2 = 0);
    
  Serial.println("Zadejte cislo od ID od 1 do 127 pod kterým chcete otisk uložit");
    LCD(radek1 = 4, radek2 = 4);
  id = readnumber();
  if (id == 0 || id > 127) { //overeni zadani s conzole
    Serial.println("Nebyla zadana hodnota od 0 do 127");
    LCD(radek1 = 5, radek2 = 4);
     return;
  }
  //vypisy
  Serial.print("Vybráno číslo: ");
  Serial.println(id);
  delay(500);
  lcd.init();
  lcd.setCursor(0,0); 
  lcd.print("Vybrano");
  lcd.setCursor(0,1); 
  lcd.print("cislo: ");
  lcd.print(id);

    
  //Spouštení funkce pro otisknnuti a ulozeni funkce  
  while (!  getFingerprintEnroll() );
}
//funckce pro vypis na lcd
void LCD(int i, int j){
  //if (currentMillis - previousMillis >= delay1S) {
  // previousMillis = currentMillis;
  
  // pole v niz jsou ulozeny hlasky, ktere jsou vypisovany podle pridelenych id
  //                       0          1              2            3                     4                  5              6               7                 8            9                   10              11
   char* hlasky_radek_1[]={"", "Inicializace..", "Senzor ","Senzor pripraven", "Zadejte cislo","Nezadal si cislo", "Prilozte prst", "Otisk ulozen", "Chyba senzoru!","Chyba otisku!", "Neznama chyba!","Otisk preveden",
   "Spatna kvalita", "Chyba funkce!", "Odstrante prst", "Otisky se" , "Otisk nebyl", " Chyba ulozeni"};
   //      12             13                  14              15           16                 17          
   //                      0          1                2          3                 4            5         6        7           8           9           10             11
   char* hlasky_radek_2[]={"", "Prosim strpeni", "nalezen :)","nenalezen :(", "od 1 do 127:","otisku", "znovu", "shoduji", "neshoduji","do pameti!", "ulozen pod:","do pameti"};
   lcd.init();
   lcd.setCursor(0,0); //nastaveni cursoru na radek 1 a pozici 1
   lcd.print(hlasky_radek_1[i]); //vypsani hlasky na radek 1 disleje
   lcd.setCursor(0,1); //nastaveni cursoru na radek 2 a pozici 1
   lcd.print(hlasky_radek_2[j]); //vypsani hlasky na radek 2 disleje
   delay(500);
   //Serial.println(hlasky_radek_1[i]); pomocne vypisy
   //Serial.println(hlasky_radek_2[j]);
   //Serial.println(previousMillis);
   //Serial.println(currentMillis);
   //}
  }
//funkce pro snimani otisku
uint8_t getFingerprintEnroll() {
  int p = -1;
  Serial.print("Priložte prst, otisk bude uložen pod číslem: "); 
  Serial.println(id);
  LCD(radek1 = 6, radek2 = 0);
  
  while (p != FINGERPRINT_OK) { //podminka, pokud neni splnena switch vrati hodnotu default, kterou je neznama chyba.
    p = finger.getImage(); //funkce pro ziskani otisku
    switch (p) { //ve switchi jsou hodnoty ktera vraci funkce fingerprintEnroll(), podle nich se vyvola hlaska ve switchi
    case FINGERPRINT_OK: 
    Serial.println("Otisk uložen");
    LCD(radek1 = 7, radek2 = 0);
      break;
    case FINGERPRINT_NOFINGER:
      //Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Chyba komunikace se senzorem");  
      LCD(radek1 = 8, radek2 = 0);
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Chyba při snímání otisku!");
      LCD(radek1 = 9, radek2 = 0);
      break;
    default:
      Serial.println("Neznámá chyba!");
      LCD(radek1 = 10, radek2 = 0);
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1); //prevadeni otisku
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
  
  Serial.println("Odstraňte prst");
    LCD(radek1 = 14, radek2 = 0);
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Přiložte prst znovu");
  LCD(radek1 = 6, radek2 = 6);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Otisk uložen");
      LCD(radek1 = 7, radek2 = 0);
      break;
    case FINGERPRINT_NOFINGER:
      //Serial.print("..");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Chyba komunikace se senzorem");
      LCD(radek1 = 8, radek2 = 0);
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Chyba při snímání otisku!");
      LCD(radek1 = 9, radek2 = 0);
      break;
    default:
      Serial.println("Neznámá chyba!");
      LCD(radek1 = 10, radek2 = 0);
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2); //druhe prevedeni otisku
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
  
  // OK converted!
  Serial.print("Vytvářím model otisku pro:");  
  Serial.println(id);
  delay(500);
  lcd.init();
  lcd.setCursor(0,0); 
  lcd.print("Vytvarim model");
  lcd.setCursor(0,1);  
  lcd.print("pro cislo: ");
  lcd.print(id);
  
  p = finger.createModel(); //vytvareni modelu otisku z dvou ppředchozích snimani otisku
  if (p == FINGERPRINT_OK) {
    Serial.println("Otisky se shodují");
    LCD(radek1 = 15, radek2 = 7);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Chyba komunikace se senzorem");
    LCD(radek1 = 8, radek2 = 0);
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Otisky se neshodují");
    LCD(radek1 = 15, radek2 = 8);
    return p;
  } else {
    Serial.println("Neznámá chyba!");
    LCD(radek1 = 10, radek2 = 0);
    return p;
  }   
  
  Serial.print("ID otisku: ");
  Serial.println(id);
  p = finger.storeModel(id); //ulozeni jiz zkontrolovaneho otisku pod zadaným id
  if (p == FINGERPRINT_OK) {
    Serial.println("Otisk uložen do paměti!");
     LCD(radek1 = 7, radek2 = 9);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Chyba komunikace se senzorem");
    LCD(radek1 = 8, radek2 = 0);
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Otisk nemohl být uložen pod ID:");
    Serial.println(id);
    LCD(radek1 = 16, radek2 = 10);
    lcd.print(id);
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Chyba uložení do paměti");
    LCD(radek1 = 17, radek2 = 11);
    return p;
  } else {
    Serial.println("Neznámá chyba!");
    LCD(radek1 = 10, radek2 = 0);
    return p;
  }   
}
