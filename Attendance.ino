 #include <SPI.h>  
 #include <MFRC522.h>  
 #include <Wire.h>   
 #include<LiquidCrystal_I2C.h>
 LiquidCrystal_I2C lcd(0x3F,16,2);
 
#define RST_PIN         9         
#define SS_PIN          10         

MFRC522 mfrc522(SS_PIN, RST_PIN);
   
 #define LED_G 7 
 #define LED_R 2 
 #define BUZZER 3  
   
 void setup()   
 {  
  Serial.begin(9600);    
  SPI.begin();    
  mfrc522.PCD_Init();       
  lcd.backlight();   
  pinMode(LED_G, OUTPUT);  
  pinMode(LED_R, OUTPUT);  
  pinMode(BUZZER, OUTPUT);  
  noTone(BUZZER); 

   lcd.init();
   lcd.backlight();
   lcd.setCursor(0,0);
   lcd.print("show your card");
   
 }  
 void loop()   
 {  
  
  if ( ! mfrc522.PICC_IsNewCardPresent())   
  {    
  lcd.setCursor(3,0);  
  lcd.print("SHOW YOUR");  
  lcd.setCursor(4,1);  
  lcd.print("ID CARD");   
  return;  
  }  
  else{  
    lcd.clear();  
  }  
    
  if ( ! mfrc522.PICC_ReadCardSerial())   
  {  
   return;  
  }  
 
  Serial.print("UID tag :");  
  String content= "";  
  byte letter;  
  for (byte i = 0; i < mfrc522.uid.size; i++)   
  {  
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");  
    Serial.print(mfrc522.uid.uidByte[i], HEX);  
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));  
    content.concat(String(mfrc522.uid.uidByte[i], HEX));  
  }  
  Serial.println();  
  content.toUpperCase();   
  if (content.substring(1) == "11 5F ED 23")  
  {  
   lcd.print("STUDENT 01");  
   lcd.setCursor(0,1);  
   lcd.print("PRESENT");    
   digitalWrite(LED_G, HIGH);  
   tone(BUZZER, 500);  
   delay(300);  
   noTone(BUZZER);  
   delay(3000);  
   digitalWrite(LED_G, LOW);  
   lcd.clear();  
  }  
  else if (content.substring(1) == "") 
  {  
   lcd.print("STUDENT 02");  
   lcd.setCursor(0,1);  
   lcd.print("PRESENT");  
   digitalWrite(LED_G, HIGH);  
   tone(BUZZER, 500);  
   delay(300);  
   noTone(BUZZER);    
   delay(3000);  
   digitalWrite(LED_G, LOW);  
   lcd.clear();  
  }  
  else if (content.substring(1) == "91 69 3E 43")   
  {  
   lcd.print("STUDENT 03");  
   lcd.setCursor(0,1);  
   lcd.print("PRESENT");  
   digitalWrite(LED_G, HIGH);  
   tone(BUZZER, 500);  
   delay(300);  
   noTone(BUZZER);  
   delay(3000);  
   digitalWrite(LED_G, LOW);  
   lcd.clear();  
  }  
  else  {  
   lcd.print("UNAUTHORIZE");  
   lcd.setCursor(0,1);  
   lcd.print("ACCESS");    
   digitalWrite(LED_R, HIGH);  
   tone(BUZZER, 300);  
   delay(2000);  
   digitalWrite(LED_R, LOW);  
   noTone(BUZZER);  
   lcd.clear();  
  }  
 }  
