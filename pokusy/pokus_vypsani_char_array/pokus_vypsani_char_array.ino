
int radek1 = 0;
int radek2 = 0;
unsigned long previousMillis = 0;

const long delay1S = 1000;
void setup() {
  
Serial.begin(9600);
}

void loop() {
   unsigned long currentMillis = millis(); 
 LCD(radek1 = 2, radek2 = 3, currentMillis);
 

}
void LCD(int num, int num2, unsigned long currentMillis){
  if (currentMillis - previousMillis >= delay1S) {
   previousMillis = currentMillis;
   char* hlasky[]={"This is string 1", "This is string 2", "This is string 3",
   "This is string 4", "This is string 5","This is string 6"};
   Serial.println(hlasky[num]);
   Serial.println(hlasky[num2]);
   Serial.println(previousMillis);
  Serial.println(currentMillis);
  }
  }
