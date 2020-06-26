int R=13; //WeMosPin: D7 ESP: GPIO13
int G=12; //WeMosPin: D6 ESP: GPIO12
int B=14; //WeMosPin: D5 ESP: GPIO14

//digital 1=HIGH=0V 0=LOW=3,3V

int min=1023; // 0% Helligkeit
int max=0; //100%

void setup() {
  // put your setup code here, to run once:
  pinMode(R,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(G,OUTPUT);  
  //pinMode(LED_BUILDIN ,OUTPUT); //onBoard LED
  digitalWrite(R,1);
  digitalWrite(B,1);
  digitalWrite(G,1);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly
  
  
  Serial.println("blubblub");

 
  
  /*Serial.print("Huhu ich kotze Regeboegen! laeuft schon ");
  Serial.println(millis()/1000); //Zeit seit Neustart in ms
  
  if (Serial.available() > 0)
  {
    int befehle = Serial.read();
 
    if (befehle == 1) { 
      digitalWrite(13, 1); 
      Serial.println("rot an");
      }
    if (befehle == 0) { 
      digitalWrite(13, HIGH); 
      Serial.println("rot aus");
      }
    Serial.flush();
  }*/
    
}

void farbverlauf(){ //wie HSV von 0-360°
  analogWrite(R,max);
  for(int j=min;j>=max;j--){
    analogWrite(G,j);
    delay(1);  
  }
  for(int j=max;j<=min;j++){
    analogWrite(R,j);
    delay(1);  
  }
  for(int j=min;j>=max;j--){
    analogWrite(B,j);
    delay(1);  
  }
  for(int j=max;j<=min;j++){
    analogWrite(G,j);
    delay(1);  
  }
  for(int j=min;j>=max;j--){
    analogWrite(R,j);
    delay(1);  
  }
  for(int j=max;j<=min;j++){
    analogWrite(B,j);
    delay(1);  
  } 
}

void fade(int pin){
    for(int j=1023;j>=0;j--){
      analogWrite(pin,j);
      delay(1);  
    }
    for(int j=0;j<=1023;j++){
      analogWrite(pin,j);
      delay(1);  
    }
}
