#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//0 ist volle Helligkeit

//const char* ssid = "Norbert";
//const char* password = "4455425005454114";

//const char* ssid = "UPC914DFB5";
//const char* password = "Wthxmstwp4tr";

//const char* ssid = "TP-LINK";
//const char* password = "EdB23x34y607";

const char* ssid = "Kellerkinder";
const char* password = "Hallo.ich.will.sterben";

//const char* ssid = "CoffeeBotWifi";
//const char* password = "robogistics";

//const char* ssid = "MadenHQ";
//const char* ssid = "FRITZ!BoxDesTODES";
//const char* password = "kostet1,37Euro";


//IPAddress ip(192,168,0,73); //Feste IP des neuen Servers, frei wählbar
//IPAddress gateway(172,31,1,1); //Gatway (IP Router eintragen)
//IPAddress subnet(255,255,255,0); //Subnet Maske eintragen

ESP8266WebServer server(80);

const int R = 13;
const int G = 12;
const int B = 14;

void setup(void){
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  analogWrite(R, 600);     // R 
  analogWrite(G, 600);     // G 
  analogWrite(B, 600);     // B 

  Serial.begin(9600);
  Serial.print("setup started");
  while(!Serial);
  WiFi.begin(ssid, password);
  //WiFi.config(ip);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  //  display.print(".");
  //  display.display();
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("led")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  testRGB();

  //allColors();
 
  Serial.print("setup finished");
}


void handleRoot() {
  
  String red = server.arg(0);          // read RGB arguments
  String green = server.arg(1);
  String blue = server.arg(2);
  String partymode = server.arg(3);
  
  analogWrite(R, (red.toInt()));
  analogWrite(G, (green.toInt()));
  analogWrite(B, (blue.toInt()));

  Serial.print("r=");   // for TESTING
  Serial.print(red.toInt()); 
  Serial.print(" g=");
  Serial.print(green.toInt()); 
  Serial.print(" b=");
  Serial.print(blue.toInt()); 
  Serial.print(" partymode=");
  Serial.println(partymode); 

  if(partymode=="1"){
    allColors();
    partymode="0";
  }

  String webpage;     
      webpage += "<!DOCTYPE HTML>\r\n";
      webpage += "<html>\r\n";
      webpage += "<header><title>LED-Cube</title></header>";
      
      webpage += "<head>";    
      webpage += "<meta name='mobile-web-app-capable' content='yes' />";
      webpage += "<meta name='viewport' content='width=device-width' />";
      webpage += "</head>";

      webpage += "<body style='margin: 0px; padding: 0px;'>";
      webpage += "<button type='button' id='onoff'>on/off</button>";
      webpage += "<button type='button' id='partymode'>partymode</button>";
      webpage += "<canvas id='colorspace'></canvas></body>";
     
      webpage += "<script type='text/javascript'>";
      webpage += "(function () {";
      webpage += " var canvas = document.getElementById('colorspace');";
      webpage += " var button1 = document.getElementById('onoff');";
      webpage += " var button3 = document.getElementById('partymode');";
      webpage += " var ctx = canvas.getContext('2d');";
      webpage += " function drawCanvas() {";
      webpage += " var colours = ctx.createLinearGradient(0, 0, window.innerWidth, 0);";
      webpage += " for(var i=0; i <= 360; i+=10) {";
      webpage += " colours.addColorStop(i/360, 'hsl(' + i + ', 100%, 50%)');";
      webpage += " }";
      
      webpage += " ctx.fillStyle = colours;";
      webpage += " ctx.fillRect(0, 0, window.innerWidth, window.innerHeight);";
      webpage += " var luminance = ctx.createLinearGradient(0, 0, 0, ctx.canvas.height);";
      webpage += " luminance.addColorStop(0, '#ffffff');";
      webpage += " luminance.addColorStop(0.05, '#ffffff');";
      webpage += " luminance.addColorStop(0.5, 'rgba(0,0,0,0)');";
      webpage += " luminance.addColorStop(0.95, '#000000');";
      webpage += " luminance.addColorStop(1, '#000000');";
      webpage += " ctx.fillStyle = luminance;";
      webpage += " ctx.fillRect(0, 0, ctx.canvas.width, ctx.canvas.height);";
      webpage += " }";
      webpage += " var eventLocked = false;";
      webpage += " var onStatus = true;";
      webpage += " var partymode = 0;";


      webpage += " function handleEventButton1() {";
      webpage += " if(eventLocked) {";
      webpage += " return;";
      webpage += " }";
      webpage += " if(onStatus) {";
      webpage += " var params = [";
      webpage += " 'r=1023',"; //1023 ist komplett aus
      webpage += " 'g=1023',";
      webpage += " 'b=1023',";
      webpage += " 'partymode=0'";
      webpage += " ].join('&');";
      webpage += " onStatus = false;";
      webpage += " }else if(onStatus==false){";
      webpage += " var params = [";
      webpage += " 'r=0',"; //0 ist volle Helligkeit
      webpage += " 'g=0',";
      webpage += " 'b=0',";
      webpage += " 'partymode=0'";
      webpage += " ].join('&');";
      webpage += " onStatus = true;";
      webpage += " }";
      webpage += " var req = new XMLHttpRequest();";
      webpage += " req.open('POST', '?' + params, true);";
      webpage += " req.send();";
      webpage += " eventLocked = true;";
      webpage += " req.onreadystatechange = function() {";
      webpage += " if(req.readyState == 4) {";
      webpage += " eventLocked = false;";
      webpage += " }";
      webpage += " }";
      webpage += " }";

      webpage += " function handleEventButton3() {";
      webpage += " if(eventLocked) {";
      webpage += " return;";
      webpage += " }";
      webpage += " if(partymode==0) {";
      webpage += " var params = [";
      webpage += " 'r=0',"; 
      webpage += " 'g=0',";
      webpage += " 'b=0',";
      webpage += " 'partymode=1'"; //Mode wechseln
      webpage += " ].join('&');";
      webpage += " partymode=1;";
      webpage += " }else if(partymode==1){";
      webpage += " var params = [";
      webpage += " 'r=0',"; 
      webpage += " 'g=0',";
      webpage += " 'b=0',";
      webpage += " 'partymode=0'"; //Mode wechseln
      webpage += " ].join('&');";
      webpage += " partymode=0;";
      webpage += " }";
      webpage += " var req = new XMLHttpRequest();";
      webpage += " req.open('POST', '?' + params, true);";
      webpage += " req.send();";
      webpage += " eventLocked = true;";
      webpage += " req.onreadystatechange = function() {";
      webpage += " if(req.readyState == 4) {";
      webpage += " eventLocked = false;";
      webpage += " }";
      webpage += " }";
      webpage += " }";
      
      webpage += " function handleEvent(clientX, clientY) {";
      webpage += " if(eventLocked) {";
      webpage += " return;";
      webpage += " }";
      
      webpage += " function colourCorrect(v) {";
      webpage += " return Math.round(1023-(v*v)/64);"; //((v*v)/64) für LEDs mit 1023 als MAX/HIGH
      webpage += " }";

      webpage += " var data = ctx.getImageData(clientX, clientY, 1, 1).data;";
      webpage += " var params = [";
      webpage += " 'r=' + colourCorrect(data[0]),";
      webpage += " 'g=' + colourCorrect(data[1]),";
      webpage += " 'b=' + colourCorrect(data[2]),";
      webpage += " 'mode=0'";
      webpage += " ].join('&');";
      webpage += " var req = new XMLHttpRequest();";
      webpage += " req.open('POST', '?' + params, true);";
      webpage += " req.send();";
      webpage += " eventLocked = true;";
      webpage += " req.onreadystatechange = function() {";
      webpage += " if(req.readyState == 4) {";
      webpage += " eventLocked = false;";
      webpage += " }";
      webpage += " }";
      webpage += " }";
      
      webpage += " canvas.addEventListener('click', function(event) {";
      webpage += " handleEvent(event.clientX, event.clientY, true);";
      webpage += " }, false);";
      
      webpage += " button1.addEventListener('click', function(event) {";
      webpage += " handleEventButton1();";
      webpage += " }, false);";

      webpage += " button3.addEventListener('click', function(event) {";
      webpage += " handleEventButton3();";
      webpage += " }, false);";
      
      webpage += " canvas.addEventListener('touchmove', function(event){";
      webpage += " handleEvent(event.touches[0].clientX, event.touches[0].clientY);";
      webpage += "}, false);";
      webpage += " function resizeCanvas() {";
      webpage += " canvas.width = window.innerWidth;";
      webpage += " canvas.height = window.innerHeight;";
      webpage += " drawCanvas();";
      webpage += " }";
      
      webpage += " window.addEventListener('resize', resizeCanvas, false);";
      webpage += " resizeCanvas();";
      webpage += " drawCanvas();";
      webpage += " document.ontouchmove = function(e) {e.preventDefault()};";
      webpage += " })();";   
      webpage += "</script><html>\r\n";

      server.send(200, "text/html", webpage);     
}


/*
void handleRoot() {
  
  String red = server.arg(0);          // read RGB arguments
  String green = server.arg(1);
  String blue = server.arg(2);
  
  analogWrite(R, (red.toInt()));
  analogWrite(G, (green.toInt()));
  analogWrite(B, (blue.toInt()));

   Serial.println(red.toInt());   // for TESTING
   Serial.println(green.toInt()); // for TESTING
   Serial.println(blue.toInt());  // for TESTING

 
 // display.clearDisplay();
 // display.setTextColor(WHITE);
    
  /*display.setTextSize(2); 
  display.setTextColor(WHITE); 
  display.setCursor(0,0);      
  display.print("R = ");  display.println(red.toInt());
  display.setCursor(0,18);
  display.print("G = ");  display.println(green.toInt());
  display.setCursor(0,36);
  display.print("B = ");  display.println(blue.toInt()); 
  display.display();

  
  String webpage;     
      webpage += "<!DOCTYPE HTML>\r\n";
      webpage += "<html>\r\n";
      webpage += "<header><title>LED CUBE</title></header>";
      
      webpage += "<head>";    
      webpage += "<meta name='mobile-web-app-capable' content='yes' />";
      webpage += "<meta name='viewport' content='width=device-width' />";
      webpage += "</head>";

      webpage += "<body style='margin: 0px; padding: 0px;'>";
      webpage += "<canvas id='colorspace'></canvas></body>";
     
      webpage += "<script type='text/javascript'>";
      webpage += "(function () {";
      webpage += " var canvas = document.getElementById('colorspace');";
      webpage += " var ctx = canvas.getContext('2d');";
      webpage += " function drawCanvas() {";
      webpage += " var colours = ctx.createLinearGradient(0, 0, window.innerWidth, 0);";
      webpage += " for(var i=0; i <= 360; i+=10) {";
      webpage += " colours.addColorStop(i/360, 'hsl(' + i + ', 100%, 50%)');";
      webpage += " }";
      
      webpage += " ctx.fillStyle = colours;";
      webpage += " ctx.fillRect(0, 0, window.innerWidth, window.innerHeight);";
      webpage += " var luminance = ctx.createLinearGradient(0, 0, 0, ctx.canvas.height);";
      webpage += " luminance.addColorStop(0, '#ffffff');";
      webpage += " luminance.addColorStop(0.05, '#ffffff');";
      webpage += " luminance.addColorStop(0.5, 'rgba(0,0,0,0)');";
      webpage += " luminance.addColorStop(0.95, '#000000');";
      webpage += " luminance.addColorStop(1, '#000000');";
      webpage += " ctx.fillStyle = luminance;";
      webpage += " ctx.fillRect(0, 0, ctx.canvas.width, ctx.canvas.height);";
      webpage += " }";
      webpage += " var eventLocked = false;";
      
      webpage += " function handleEvent(clientX, clientY) {";
      webpage += " if(eventLocked) {";
      webpage += " return;";
      webpage += " }";
      
      webpage += " function colourCorrect(v) {";
      webpage += " return Math.round(1023-(v*v)/64);";
      webpage += " }";
      webpage += " var data = ctx.getImageData(clientX, clientY, 1, 1).data;";
      webpage += " var params = [";
      webpage += " 'r=' + colourCorrect(data[0]),";
      webpage += " 'g=' + colourCorrect(data[1]),";
      webpage += " 'b=' + colourCorrect(data[2])";
      webpage += " ].join('&');";
      webpage += " var req = new XMLHttpRequest();";
      webpage += " req.open('POST', '?' + params, true);";
      webpage += " req.send();";
      webpage += " eventLocked = true;";
      webpage += " req.onreadystatechange = function() {";
      webpage += " if(req.readyState == 4) {";
      webpage += " eventLocked = false;";
      webpage += " }";
      webpage += " }";
      webpage += " }";
      webpage += " canvas.addEventListener('click', function(event) {";
      webpage += " handleEvent(event.clientX, event.clientY, true);";
      webpage += " }, false);";
      webpage += " canvas.addEventListener('touchmove', function(event){";
      webpage += " handleEvent(event.touches[0].clientX, event.touches[0].clientY);";
      webpage += "}, false);";
      webpage += " function resizeCanvas() {";
      webpage += " canvas.width = window.innerWidth;";
      webpage += " canvas.height = window.innerHeight;";
      webpage += " drawCanvas();";
      webpage += " }";
      
      webpage += " window.addEventListener('resize', resizeCanvas, false);";
      webpage += " resizeCanvas();";
      webpage += " drawCanvas();";
      webpage += " document.ontouchmove = function(e) {e.preventDefault()};";
      webpage += " })();";   
      webpage += "</script><html>\r\n";

      server.send(200, "text/html", webpage);    
}
*/


void testRGB() { // fade in and out of Red, Green, Blue
    analogWrite(R, 1023);     // R off
    analogWrite(G, 1023);     // G off
    analogWrite(B, 1023);     // B off 
    fade(R); // R
    fade(G); // G
    fade(B); // B
}

void fade(int pin) {
    for (int u = 0; u < 1024; u++) {
      analogWrite(pin,  1023 - u);
      delay(1);
    }
    for (int u = 0; u < 1024; u++) {
      analogWrite(pin, u);
      delay(1);
    }
}

void allColors() {
    int col[3] = { 0,0,0 };
for (int a = 0; a <= 100; a++) { //Anzahl der Farbdurchläufe
  

    for (int i = 0; i < 360; i++) {
       getRGB(i, 255, 255, col);             // HSV in RGB umrechen
       analogWrite(R, 1023 - col[0]*4);    // und ausgeben
       analogWrite(G, 1023 - col[1]*4);
       analogWrite(B, 1023 - col[2]*4);
       delay(10);
    }
}
  
 
}

void handleNotFound(){
  //digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  //digitalWrite(led, 0);
}



void loop(void){
  server.handleClient();
}


void getRGB(int hue, int sat, int val, int colors[3]) 
  {  // Diese Funktion rechnet einen HSV-Wert in die ensprechenden
     // RGB-Werte um. Diese werden im Array ‚colors' zurückgegeben
     // colors[0] = ROg, colors[1]} = Gruen, colors[2] = Blau
     // hue: 0 - 359, saturation: 0 - 255, val (lightness): 0 - 255
  int red, green, blue, base;

  if (sat == 0) 
    { // Sättigung = 0 --> Grauwert
    colors[0] = val;
    colors[1] = val;
    colors[2] = val;
    } 
  else  
    {
    base = ((255 - sat) * val) >> 8;
    if (hue < 60)
      {
      red = val;
      green = (((val - base)*hue)/60) + base;
      blue = base;
      }
    else if (hue < 120)
      {
      red = (((val - base)*(60-(hue%60)))/60) + base;
      green = val;
      blue = base;
      }
    else if (hue < 180)
      {
      red = base;
      green = val;
      blue = (((val - base)*(hue%60))/60) + base;
      }
    else if (hue < 240)
      {
      red = base;
      green = (((val - base)*(60 - (hue%60)))/60) + base;
      blue = val;
      }
    else if (hue < 300)
      {
      red = (((val - base)*(hue%60))/60) + base;
      green = base;
      blue = val;
      }
    else if (hue < 360)
      {
      red = val;
      green = base;
      blue = (((val - base)*(60 - (hue%60)))/60) + base;
      }
    colors[0] = red;
    colors[1] = green;
    colors[2] = blue;
    }
  }
