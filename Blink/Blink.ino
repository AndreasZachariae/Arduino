#define led 13
#define datenEingang 4
#define schiebeTakt 3
#define speicherTakt 2

int zahlenAufDisplay[10][8] ={
  { LOW, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH },
  { LOW, LOW, LOW, LOW, LOW, HIGH, HIGH, LOW },
  { LOW, HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH },
  { LOW, HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH },
  { LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW },
  { LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH },
  { LOW, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, HIGH },
  { LOW, LOW, LOW, LOW, LOW, HIGH, HIGH, HIGH },
  { LOW, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH },
  { LOW, HIGH, HIGH, LOW, HIGH, HIGH, HIGH, HIGH }
};

int zaehler=0;
int letzterZustand=0;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(datenEingang, OUTPUT);
  pinMode(schiebeTakt, OUTPUT);
  pinMode(speicherTakt, OUTPUT);
  pinMode(8,INPUT);
  Serial.begin(9600);
}

void loop() {
  
  int input=digitalRead(8);
  if(letzterZustand!=input){
    Serial.println(zaehler);
    if(input==1){
      zaehler++;
      zaehler=zaehler%10;
      letzterZustand=1;
    }
    else{
      letzterZustand=0;
    }
  }
  anzeigen(zaehler,zahlenAufDisplay);
  delay(10);

  
  /*if (Serial.available()>0){
    char befehl = Serial.read();
    if (befehl=='1'){
      digitalWrite(led,HIGH);
      Serial.println("LED ON");
    }else if (befehl=='2'){
      digitalWrite(led,LOW);
      Serial.println("LED OFF");
    }else {
      Serial.print("Unbekannter Befehl: ");
      Serial.println(befehl);
    } 
  }*/
} 

void anzeigen(int zaehler,int zahlen[10][8]){
  for(int i=0; i<8; i++){
    digitalWrite(datenEingang,zahlen[zaehler][i]);
    digitalWrite(schiebeTakt,LOW);
    digitalWrite(schiebeTakt,HIGH); //ansteigende Flanke
  }
  digitalWrite(speicherTakt,LOW);
  digitalWrite(speicherTakt,HIGH);
  
}
