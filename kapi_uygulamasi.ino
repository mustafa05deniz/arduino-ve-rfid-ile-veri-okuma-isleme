#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
 
#define RST_PIN 9
#define SS_PIN 10

byte readCard[4];
int successRead;
int okunanVeri;

#define led1 7
#define led2 5
MFRC522 mfrc522(SS_PIN, RST_PIN); // kartın _ id kısmı buraya yazılacaktır . 
 
MFRC522::MIFARE_Key key;

 int liste[] = {9,7,7,1,3,9,1,6,4};
void setup()
{
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("RFID KART KAYIT UYGULAMASI");
  Serial.println("--------------------------");
  Serial.println("Lutfen Yeni bir  kart okutun");
  Serial.println();
 
 
 
}
 
void loop()
{

  do {
    //okuma başarılı olana kadar getID fonksiyonunu çağır
    successRead = getID(); 
  }
  while (!successRead);  
  
 
}
 
int getID() {
  //yeni bir kart okunmadıysa 0 döndür
  if ( ! mfrc522.PICC_IsNewCardPresent()) { 
    return 0;
    
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return 0;
    
  }
  
  for ( int i = 0; i < mfrc522.uid.size; i++ ) // mfrc522.uid.size kartın sahip olduğu numaranın uzunlugu 
  {
    //kartın UID'sini EEPROM'a kaydet    
    EEPROM.write(i, readCard[i] ); 
    
  }
  Serial.print("Kart UID'si: ");
  //kartın UID'sini byte byte oku ve seri monitöre yaz
  for (int i = 0; i < mfrc522.uid.size; i++) {  //
    readCard[i] = mfrc522.uid.uidByte[i];
    
    Serial.print(readCard[i]);
    

    
  }

  
  Serial.println("");
  //kart okumayı durdur ve 1 döndür (okuma başarılı)
  mfrc522.PICC_HaltA();
  
  digitalWrite(led1,HIGH);
  tone(6, 494, 500);
  delay(400);
  noTone(6);
  digitalWrite(led1,LOW);


  digitalWrite(led2,HIGH);
  tone(6, 494, 500);
  delay(400);
  noTone(6);
  digitalWrite(led2,LOW);
  
  
  return 1;
}
