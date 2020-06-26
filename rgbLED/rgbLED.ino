#define rot 13
#define gruen 12
#define blau 14

int max=0;
int min=1023;


void setup() {
  pinMode(rot,OUTPUT);
  pinMode(gruen,OUTPUT);
  pinMode(blau,OUTPUT);
  digitalWrite(rot,1);
  digitalWrite(gruen,1);
  digitalWrite(blau,1);

  Serial.begin(9600);

}

void loop() {
  //farbverlauf();
  fadeEin(rot);
  analogWrite(rot,max);
  analogWrite(gruen,max);
  analogWrite(blau,max);
}

void fadeEin(int pin){
  for(int i=min;i<=max;i++){
    analogWrite(pin,i);
    delay(10);
  }
}
void fadeAus(int pin){
  for(int i=max;i>=min;i--){
    analogWrite(pin,i);
    delay(10);
  }
}

void farbverlauf(){
  analogWrite(rot,max);
  fadeEin(gruen);
  fadeAus(rot);
  fadeEin(blau);
  fadeAus(gruen);
  fadeEin(rot);
  fadeAus(blau);
}
