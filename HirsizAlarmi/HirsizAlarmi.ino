
// ---- Dijital Pin Bölgeleri ----
#define LEDPIN 5
#define BUTONPIN 6 // AÇMA BUTONU - 3 SANİYE BASILI TUTUNCA AÇAR
#define KBUTONPIN 7 // KAPATMA BUTONU - DİREKT KAPATIR
#define BUZZERPIN 4
#define TRIGPIN 3
#define ECHOPIN 2

//--------------------------------


bool butonaktifmi = false;
unsigned long butonzamani = 0; // DATA ÇOK BÜYÜK OLACAĞI İÇİN UNSIGNED LONG İLE TUTULUYOR

int maxrange = 60;  //--> BU KISMI ÖLÇMESİ İSTEDİĞİ MAX UZAKLIK OLARAK DEĞİŞTİREBİLİRSİNİZ. STANDART OLARAK KAPI EŞİK ARALIĞI SEÇİLDİ (60 CM).
int minrange = 2;   // --> MİNİMUM 2 CM OLMAK ZORUNDA, İSTEDİĞİNİZ ŞEKİLDE DEĞİŞTİREBİLİRSİNİZ.

int sapma = 2;  //--> SAPMAYI 0 YAPMAYIN, BUTONA BASARKEN ELİNİZ KAYSA BİLE ÖTÜYOR (EN KÜÇÜK HAREKETTE) MİN 1 OLMAK ŞARTIYLA İSTEDİĞİNİZ DEĞERİ ATIYABİLİRSİNİZ.

int standartrange;
void setup() {

  pinMode(LEDPIN, OUTPUT);
  pinMode(BUTONPIN, INPUT_PULLUP);
  pinMode(KBUTONPIN, INPUT_PULLUP);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);

  Serial.begin(9600);
}

bool ilkolcumyapildimi = false;

int anlikolcum;


void loop() {
  Serial.println(digitalRead(BUTONPIN));

  if (digitalRead(BUTONPIN) == 0 && !butonaktifmi) {
    butonzamani=millis();
    butonaktifmi = true;
    
  }

  if(digitalRead(BUTONPIN) == 1){
    butonzamani = millis();
    butonaktifmi = false;
  }

  if (digitalRead(BUTONPIN) == 0 && butonaktifmi) {
    if (millis() - butonzamani >= 3000) {
      butonaktifmi = false;
      butonzamani = 0;
      noTone(BUZZERPIN);
      ilkolcumyapildimi = false;

      digitalWrite(LEDPIN, HIGH);
      standartrange = mesafe(maxrange, minrange);

      if (standartrange == 0) {

        for (int i = 0; i < 3; i++) {
          tone(BUZZERPIN, 440);
          delay(500);
          noTone(BUZZERPIN);
          delay(500);
          ilkolcumyapildimi = false;

          //EĞER HC-SR04 ÖLÇÜM YAPAMAZSA (0 DEĞERİ ALIRSA) 3 KERE ARALIKLI ÖTER
        }
        digitalWrite(LEDPIN, LOW);  //VE LED SÖNER
      } else {
        ilkolcumyapildimi = true;
        //YAPARSA LED AÇIK KALIR (KAPAMA KODU OLMADIĞI İÇİN)
      }
    }
  }

  if (ilkolcumyapildimi == true) {
    anlikolcum = mesafe(maxrange, minrange);
  }




  
  if (abs(anlikolcum - standartrange) > sapma) {

    tone(BUZZERPIN, 800);  //800 DEĞERİ FREKANSTIR. TOK SES İÇİN 300-500 ARASI, TİZ SES İÇİN 700-900 ARASI DEĞER GİREBİLİRSİNİZ.
  }

  if(digitalRead(KBUTONPIN) == 0){
    anlikolcum = 0;
    ilkolcumyapildimi = false;
    standartrange = 0;
    digitalWrite(LEDPIN, LOW);
    noTone(BUZZERPIN);
  }
}

int mesafe(int maxrng, int minrng) {
  long duration, distance;
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);

  duration = pulseIn(ECHOPIN, HIGH);
  distance = duration / 58.2;
  delay(50);

  if (distance >= maxrange || distance <= minrange){
    return 0;
  }
  else{
     return distance;
  }
 
}
