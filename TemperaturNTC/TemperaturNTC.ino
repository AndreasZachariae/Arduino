#include <SimpleDHT.h>
#include <Wire.h>
#include <DS3231.h>

#define dataIn 3
#define speicherTakt 4
#define schiebeTakt 5
#define pin1000er 8
#define pin100er 9
#define pin10er 10
#define pin1er 11
#define tempSensor A0
#define vorwiderstand 10000
#define DHT11Pin 12
#define tasterPin 2 //Interrupt Pin 0
#define TEMP 0
#define FEUCHT 1
#define DRUCK 2
#define ZEIT 3
#define DATUM 4
#define luftdruck 1013.25
#define partialDampfDruck 23.4

SimpleDHT11 dht11;
DS3231 clock;
RTCDateTime dt;

int pinStelle[]={8,9,10,11};

byte zahlen[10]={B00111111,B00000110,B01011011,B01001111,B01100110,
                B01101101,B01111101,B00000111,B01111111,B01101111};

int zustand=TEMP;
bool tasterZustand=false;
unsigned long zeit=1000;
unsigned long zeitNeu;
int wert;

void setup() {
  pinMode(dataIn,OUTPUT);
  pinMode(speicherTakt,OUTPUT);
  pinMode(schiebeTakt,OUTPUT);
  for(int i=0;i<4;i++){
    pinMode(pinStelle[i],OUTPUT);
    digitalWrite(pinStelle[i],HIGH);
  }
  pinMode(tempSensor,INPUT);
  pinMode(tasterPin,INPUT);

  Serial.begin(9600);

  attachInterrupt(0,ISRTaster,FALLING);

  clock.begin();
  clock.setDateTime(__DATE__, __TIME__);
}

void ISRTaster(){
  tasterZustand=true;
}

void TasterGedrueckt(){
  if(zustand==TEMP){
    zustand=FEUCHT;
    Serial.println("FEUCHTIGKEIT");
  }
  else if(zustand==FEUCHT){
    zustand=ZEIT;
    Serial.println("DRUCK");
  }
  else if(zustand==DRUCK){
    zustand=ZEIT;
    Serial.println("UHRZEIT");
  }
  else if(zustand==ZEIT){
    zustand=DATUM;
    Serial.println("DATUM du huremsihn!!!!");
  }
  else if(zustand==DATUM){
    zustand=TEMP;
    Serial.println("TEMPERATUR");
  }
  delay(500);
  tasterZustand=false;
}

void Anzeigen(int zahl){

  int zahl0=zahl;
  int stelle[]={10,10,10,10};
  
  if(zahl0>999)stelle[0]=zahl/1000;
  zahl=zahl%1000;
  if(zahl0>99)stelle[1]=zahl/100;
  zahl=zahl%100;
  if(zahl0>9)stelle[2]=zahl/10;
  stelle[3]=zahl%10;

  for(int i=0;i<4;i++){
    
    if(stelle[i]<10){
      
      digitalWrite(speicherTakt,LOW);
      if(i==1){
        shiftOut(dataIn,schiebeTakt,MSBFIRST,zahlen[stelle[i]] | B10000000); //Punkt bei der zweiten Stelle
      }else{
        shiftOut(dataIn,schiebeTakt,MSBFIRST,zahlen[stelle[i]]);
      }
      digitalWrite(speicherTakt,HIGH);  //steigende Flanke 
      digitalWrite(pinStelle[i],LOW); //nur eine Stelle wird angesprochen
      delay(1);
      digitalWrite(pinStelle[i],HIGH);
    }
  }
}

//-----------------------------------------------------------------------------------------
  
void loop() {

  if(zustand==TEMP){
    zeitNeu=millis();
    if(zeitNeu-zeit>100){
      Serial.println(NTCWiderstand());
      Serial.println(Temperatur());
      wert=Temperatur()*100;
      zeit=millis();
    }
    
  }else if(zustand==FEUCHT){

    zeitNeu=millis();
    if(zeitNeu-zeit>1000){
      byte tempDHT11 = 0;
      byte feucht = 0;
      byte data[40] = {0};
      if (dht11.read(DHT11Pin, &tempDHT11, &feucht, data)) {
        Serial.print("Read DHT11 failed");
        return;
      }
      Serial.print((int)tempDHT11); Serial.print("*C, ");
      Serial.print((int)feucht); Serial.println("%");
      wert=feucht;
      zeit=millis();
    }
    
  }else if(zustand==DRUCK){
    zeitNeu=millis();
    if(zeitNeu-zeit>1000){
      float tempC= Temperatur();
      float saettigungsP= 6.11153*exp((17.5043*tempC)/(241.2+tempC)); //Sättigungsdampfdruck von Wasserdampf in Luft in hPa
      float relFeuchte=luftdruck/saettigungsP; //partialDampfdruck statt Luftdruck
      Serial.println(relFeuchte);
      wert=relFeuchte;
      zeit=millis();
    }
    
  }else if(zustand==ZEIT){                            //Helligkeit //Abstand weitere Möglichkeiten
    zeitNeu=millis();
    if(zeitNeu-zeit>1000){
      dt = clock.getDateTime();
      String uhrzeit=clock.dateFormat("Hi", dt);
      wert= uhrzeit.toInt();
      Serial.println(wert);
      zeit=millis();
    }
    
  }else if(zustand==DATUM){
    zeitNeu=millis();
    if(zeitNeu-zeit>1000){
      dt = clock.getDateTime();
      String datum=clock.dateFormat("dm", dt);
      wert= datum.toInt();
      Serial.println(wert);
      zeit=millis();
    }
  }
  
 
  Anzeigen(wert);
  Serial.println(digitalRead(tasterPin));
  if(tasterZustand==true){
    TasterGedrueckt();
  }
  
}


//---------------------------------------------------------------------------------------------

float NTCWiderstand(){
  float spannung= analogRead(tempSensor)*(5.0/1024.0);
  float verhaeltnis= spannung/5.0;
  float widerstand= (verhaeltnis*vorwiderstand)/(1-verhaeltnis);
  return widerstand;
}

float Temperatur(){
  int tempSensor = analogRead(tempSensor);
  double ln = log(10000.0 * ((1024.0 / tempSensor - 1)));
  float tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * ln * ln )) * ln );
  float tempC = tempK-273.15;
  return tempC;
}
