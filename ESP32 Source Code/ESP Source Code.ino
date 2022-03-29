 #include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>


const char* ssid = "*WIFI*";
const char* password = "*PASSWORD*";

const int output = 2;
const int output2 = 33;
const int button1 = 5;
const int button2 = 27;
const int button3 = 4;
const int button4 = 12;
const int button5 = 13;
const int button6 = 14;

String sliderValue = "0";
String sliderValue1 = "0";

const int freq = 5000;
const int ledChannel = 0;
const int ledChannel1 = 1;

const int resolution = 8;

const char* PARAM_INPUT = "value";

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP Web Server</title>
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 2.3rem;}
    p {font-size: 1.9rem;}
    arbtn{
      height:20px;
      width:50px;
    }
    body {max-width: 400px; margin:0px auto; padding-bottom: 25px;}
    .slider { -webkit-appearance: none; margin: 14px; width: 360px; height: 25px; background: #FFD65C;
      outline: none; -webkit-transition: .2s; transition: opacity .2s;}
    .slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: #003249; cursor: pointer;}
    .slider::-moz-range-thumb { width: 35px; height: 35px; background: #003249; cursor: pointer; } 
  </style>
</head>
<body >
  <h6>ESP Web Server</h6>
  <p><span id="textSliderValue">%SLIDERVALUE%</span></p>
  <p><input type="range" onchange="updateSliderPWM(this)" id="pwmSlider" min="0" max="255" value="%SLIDERVALUE%" step="1" class="slider"></p>
  <p><span id="textSliderValue1">%SLIDERVALUE1%</span></p>
  <p><input type="range" onchange="updateSlider1PWM(this)" id="pwmSlider1" min="0" max="255" value="%SLIDERVALUE1%" step="1" class="slider"></p>
  <h6>Button 1</h6>
  <button class="button arbtn" id="" onclick="but1('on');"">ON</button>
  <button class="button arbtn" id="" onclick="but1('off');"">OFF</button>
  <h6>Button 2</h6>
  <button class="button arbtn" id="" onclick="but2('on');"">ON</button>
  <button class="button arbtn" id="" onclick="but2('off');"">OFF</button>
  <h6>Button 3</h6>
  <button class="button arbtn" id="" onclick="but3('on');"">ON</button>
  <button class="button arbtn" id="" onclick="but3('off');"">OFF</button>
  <h6>Button 4</h6>
  <button class="button arbtn" id="" onclick="but4('on');"">ON</button>
  <button class="button arbtn" id="" onclick="but4('off');"">OFF</button>
  <h6>Button 5</h6>
  <button class="button arbtn" id="" onclick="but5('on');"">ON</button>
  <button class="button arbtn" id="" onclick="but5('off');"">OFF</button>
  <h6>Button 6</h6>
  <button class="button arbtn" id="" onclick="but6('on');"">ON</button>
  <button class="button arbtn" id="" onclick="but6('off');"">OFF</button>
<script>
function but1(x) {
  console.log(x);
 var xhr = new XMLHttpRequest();
 xhr.open("GET", "/" + x, true);
 xhr.send();
}
function but2(x) {
 console.log(x);
 var xhr = new XMLHttpRequest();
 xhr.open("GET", "/" + x + "2", true);
 xhr.send();
}
function but3(x) {
 console.log(x);
 var xhr = new XMLHttpRequest();
 xhr.open("GET", "/" + x + "3", true);
 xhr.send();
}
function but4(x) {
  console.log(x);
 var xhr = new XMLHttpRequest();
 xhr.open("GET", "/" + x + "4", true);
 xhr.send();
}
function but5(x) {
  console.log(x);
 var xhr = new XMLHttpRequest();
 xhr.open("GET", "/" + x + "5", true);
 xhr.send();
}
function but6(x) {
   console.log(x);
 var xhr = new XMLHttpRequest();
 xhr.open("GET", "/" + x + "6", true);
 xhr.send();
}
function updateSliderPWM(element) {
  var sliderValue = document.getElementById("pwmSlider").value;
  document.getElementById("textSliderValue").innerHTML = sliderValue;
  console.log(sliderValue);
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/slider?value="+sliderValue, true);
  xhr.send();
}
function updateSlider1PWM(element) {
  var sliderValue1 = document.getElementById("pwmSlider1").value;
  document.getElementById("textSliderValue1").innerHTML = sliderValue1;
  console.log(sliderValue1);
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/slider1?value="+sliderValue1, true);
  xhr.send();
}
</script>
</body>
</html>
)rawliteral";

String processor(const String& var){

  if (var == "SLIDERVALUE"){
    return sliderValue;
  }
  return String();
}

String processor1(const String& var){

  if (var == "SLIDERVALUE1"){
    return sliderValue1;
  }
  return String();
}

void setup(){

  Serial.begin(115200);
  

  ledcSetup(ledChannel, freq, resolution);

  ledcSetup(ledChannel1, freq, resolution);
  

  ledcAttachPin(output, ledChannel);


  ledcAttachPin(output2, ledChannel1);

  pinMode(button1, OUTPUT);
  server.on("/on", HTTP_GET, [] (AsyncWebServerRequest *request) {
    digitalWrite(button1, HIGH);
    request->send(200, "text/plain", "ok");
  });
 
  server.on("/off", HTTP_GET, [] (AsyncWebServerRequest *request) {
    digitalWrite(button1, LOW);
    request->send(200, "text/plain", "ok");
  });
  pinMode(button2, OUTPUT);
  server.on("/on2", HTTP_GET, [] (AsyncWebServerRequest *request) {
    digitalWrite(button2, HIGH);
    request->send(200, "text/plain", "ok");
  });

  server.on("/off2", HTTP_GET, [] (AsyncWebServerRequest *request) {
    digitalWrite(button2, LOW);
    request->send(200, "text/plain", "ok");
  });
  pinMode(button3, OUTPUT);
  server.on("/on3", HTTP_GET, [] (AsyncWebServerRequest *request) {
    digitalWrite(button3, HIGH);
    request->send(200, "text/plain", "ok");
  });
 
  server.on("/off3", HTTP_GET, [] (AsyncWebServerRequest *request) {
    digitalWrite(button3, LOW);
    request->send(200, "text/plain", "ok");
  });
  pinMode(button4, OUTPUT);
  server.on("/on4", HTTP_GET, [] (AsyncWebServerRequest *request) {
    digitalWrite(button4, HIGH);
    request->send(200, "text/plain", "ok");
  });
 
  server.on("/off4", HTTP_GET, [] (AsyncWebServerRequest *request) {
    digitalWrite(button4, LOW);
    request->send(200, "text/plain", "ok");
  });
  pinMode(button5, OUTPUT);
  server.on("/on5", HTTP_GET, [] (AsyncWebServerRequest *request) {
    digitalWrite(button5, HIGH);
    request->send(200, "text/plain", "ok");
  });
 
  server.on("/off5", HTTP_GET, [] (AsyncWebServerRequest *request) {
    digitalWrite(button5, LOW);
    request->send(200, "text/plain", "ok");
  });
  pinMode(button6, OUTPUT);
  server.on("/on6", HTTP_GET, [] (AsyncWebServerRequest *request) {
    digitalWrite(button6, HIGH);
    request->send(200, "text/plain", "ok");
  });
 
  server.on("/off6", HTTP_GET, [] (AsyncWebServerRequest *request) {
    digitalWrite(button6, LOW);
    request->send(200, "text/plain", "ok");
  });
  
  ledcWrite(ledChannel, sliderValue.toInt());
  ledcWrite(ledChannel1, sliderValue1.toInt());


  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }


  Serial.println(WiFi.localIP());


  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor1);
  });


  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;

    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage;
      ledcWrite(ledChannel, sliderValue.toInt());
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });

    server.on("/slider1", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;

    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue1 = inputMessage;
      ledcWrite(ledChannel1, sliderValue1.toInt());
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });
  

  server.begin();
}
  
void loop() {
  
}
