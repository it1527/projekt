//Vysvětlení, proč jsem nepoužil millis():
/* 
 *  funkce millis musí běžet v loopu programu a jelikož ji potřebuji použít dřív, 
 *  tedy v setupu, jak je videt v kodu samotné čtečky, nehodí se tedy k použití v mém v tomto složitějším kódu.
 *  Je možné, že by se dalo toto obejít vnořenou funkcí, avšak me s naženi v tomhle ohledu nedopadlo úspěšně.
 *  Jelikož se nepřipojuji k Wi_fi mohu si dovoli použít delay(), na místo millis(). Snad Vám přiklad pochopí pochopit problématiku.
 */
int radek1 = 0; //definice radku 1 displeje
int radek2 = 0;//definice radku  2 displeje
unsigned long previousMillis = 0; //nastaveni promenne pro cely program

const long delay1S = 1000; //nastaveni hodnoty delaye
void setup() {
  //Zde v kodu čtečky potřebuju vyvolat funkci LCD, avšak funkce millis() funguje v loopu,
  //ke kterému se program zatím nedostal, tudiš tato funkce nefunguje a tim padem ani samotná LCD(), 
  //ktera hodnotu přijma jako parametr
  //unsigned long currentMillis = millis(); funkce millis se zde nepripocitava.. 
  LCD(radek1 = 2, radek2 = 3, currentMillis); //funkce vypisu na lcd dislay
  Serial.begin(9600);
}

void loop() {
   unsigned long currentMillis = millis(); // jiz funkcni millis v loopu
 LCD(radek1 = 2, radek2 = 3, currentMillis); // opět vyvolani vypisu lcd, tentokrát funguje s millis() namísto delay();
 

}
void LCD(int num, int num2, unsigned long currentMillis){
  if (currentMillis - previousMillis >= delay1S) { //podminka kdy ma byt kod vypsan, nahrazuje presne radek delay()
   previousMillis = currentMillis; //nastaveni millis pro pokracovani, pri opetovnem volani funkce
   char* hlasky[]={"This is string 1", "This is string 2", "This is string 3",
   "This is string 4", "This is string 5","This is string 6"}; //vypisy hlasek na obrazovku v poli
   Serial.println(hlasky[num]); //pomocne odladovaci vystupy na consoli
   Serial.println(hlasky[num2]);
   Serial.println(previousMillis);
  Serial.println(currentMillis);
  }
  }
