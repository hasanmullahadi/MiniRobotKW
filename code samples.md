#minirobot #arabic #Kuwait 


```c
#define LOCAL_SSID "Your_Router_Name"
#define LOCAL_PASS "Your_Router_Password"

```



will use for now ESP32
good place to look at:
https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/#:~:text=Installing%20ESP32%20Add%2Don%20in%20Arduino%20IDE&text=Open%20the%20Boards%20Manager.,installed%20after%20a%20few%20seconds.

![[PXL_20230116_162033566.jpg]]

![[PXL_20230116_162015247.jpg]]

what we need:
start with Arduino IDE:
esp32 DevkitV1

to start with ESP32 Arduino ID:
start with 

https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
to be added in 
![[Pasted image 20230117102145.png]]

![[Pasted image 20230117102251.png]]
![[Pasted image 20230117102324.png]]

add the URL in the list below:
then go to  Toosl -> Board: xxx -> Boards Manager:
![[Pasted image 20230117102643.png]]

search for ESP32 and install it:
![[Pasted image 20230117102835.png]]

**==then select Board "xxx" --> ESP32 Arduino --> DOIT ESP32 DEVKIT V1:==**
![[Pasted image 20230117123149.png]]
Next will implement a sericea of mini projects, that will be eventually integrated together.

# Get To Know Me
ESP32 has a built in Wifi module and Bluetooth module.
has the following pin configurations:

![[Pasted image 20230117193532.png]]

if only use for now one side of, for example:
![[Pasted image 20230117193619.png]]

we would have 17 --> GPIO, General Purpose Input Output,
and 1 --> 3.3V DC output from the device, from USB power in.

DC Current on I/O Pins  --> 40 mA
**DC 3.3V output --> 50 mA**
so make sure that you can not drive anything more than **50 mA**
it should come form outside power.
### **ESP32 Technical Specifications**
```notion-like-tables
table-id-ygVBOU
```










# P 1, Hello World, But Blinking
```c
/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
```
need to tested first.

```c
/*
 * MiniRobot
 * By: Hasan Ismail Ali
 * minirobotkw@gmail.com for any questions
 * 
 */

#define VER 1.01

//// for the ultrasonic sensor:
//#include <Arduino.h>
//#include <HC_SR04.h>
//#define TRIG 5
//#define ECHO 18
//HC_SR04<ECHO> sensor(TRIG);  

#include <HCSR04.h>
const byte triggerPin = 5;
const byte echoPin = 18;
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);


//this part for the LCD, driver SSD1306 128x64 I2C

#define RL1
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//end of display settings



 #define ONBOARD_LED  2

void setup() {
  // put your setup code here, to run once:
  pinMode(ONBOARD_LED,OUTPUT);
  LCDinit();
  displayInit();


    
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  digitalWrite(ONBOARD_LED,HIGH);
  delay(100);
  digitalWrite(ONBOARD_LED,LOW);

  displayDis(distanceSensor.measureDistanceCm());

    
}

void LCDinit()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
}


void displayInit()
{
  display.clearDisplay();
  display.setTextSize(3);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(F("Mini"));
  display.println(F("Robot"));
  display.setTextSize(2);
  display.print(F("v:"));
  display.println(VER);
  display.display();
  delay(2000);
}


void displayDis(float d)
{
  display.clearDisplay();
  display.setTextSize(3);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(F("Dist:"));
  //display.println(F("Robot"));
  display.setTextSize(2);
  display.print(d);
  display.println(F("cm"));

  display.display();
  delay(2000);
}


```


newer version and simpler:
```c
/*
 * MiniRobot
 * By: Hasan Ismail Ali
 * minirobotkw@gmail.com for any questions
 * 
 */

#define VER 1.01

#define TRIG 5
#define ECHO 18



//this part for the LCD, driver SSD1306 128x64 I2C

#define RL1
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//end of display settings



 #define ONBOARD_LED  2

void setup() {
  // put your setup code here, to run once:
  pinMode(ONBOARD_LED,OUTPUT);
  
  LCDinit();
  displayInit();
  initSR04();

    
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  digitalWrite(ONBOARD_LED,HIGH);
  delay(100);
  digitalWrite(ONBOARD_LED,LOW);

  displayDis( pulseSR04());

    
}

void LCDinit()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
}


void displayInit()
{
  display.clearDisplay();
  display.setTextSize(3);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(F("Mini"));
  display.println(F("Robot"));
  display.setTextSize(2);
  display.print(F("v:"));
  display.println(VER);
  display.display();
  delay(2000);
}


void displayDis(long d)
{
  display.clearDisplay();
  display.setTextSize(3);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(F("Dist:"));
  //display.println(F("Robot"));
  display.setTextSize(2);
  display.print(d);
  display.println(F("cm"));

  display.display();
  delay(100);
}


void initSR04()
{
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT); 
}

long pulseSR04()
{
  long duration = 0;
  long distance = 0;
  digitalWrite(TRIG, LOW); //set trigger signal low for 2us
  delayMicroseconds(2);
  
  /*send 10 microsecond pulse to trigger pin of HC-SR04 */
  digitalWrite(TRIG, HIGH);  // make trigger pin active high
  delayMicroseconds(10);            // wait for 10 microseconds
  digitalWrite(TRIG, LOW);   // make trigger pin active low
  /*Measure the Echo output signal duration or pulss width */
  duration = pulseIn(ECHO, HIGH); // save time duration value in "duration variable
  distance= duration*0.034/2.0; //Convert pulse duration into distance
  return distance;
}

```


now to add the motor controller:
![[Pasted image 20230117143237.png]]
![[Pasted image 20230118182004.png]]
![[Pasted image 20230118182550.png]]

Rx2 -> GPIO 16.
also 
![[Pasted image 20230118191121.png]]
also since GPIO is also contected to LED, keep a track of that
1-run it as server 
2- has it track distance and line or just move it around.

get the line detoctor done
![[Pasted image 20230120053640.png]]

![[Pasted image 20230120053705.png]]

TX2 -> GPIO17

Next we do the IP interface.

HelloServer.ino
```c
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid     = "HUAWEI_H122_BE0F";
const char* password = "LDG2AMADAQ5";

WebServer server(80);

const int led = 13;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp32!");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}
```

also create a holder for the IR :
![[Pasted image 20230120142624.png]]
fist test:
![[Pasted image 20230120142654.png]]
did a bit modifications on it:
![[Pasted image 20230120170434.png]]

things needs to be don : [[code samples Pending items]]



working on timers interrupts [[ESP32 Timer & Multiple Timer & Changing Timer]] 

final code sample for V1.02: 
# MiniRobot1_2.ino
```c
/*
 * MiniRobot
 * Developed by: Hasan I A A Mohammad
 * email @ minirobotkw@gmail.com
 * 
 * 
 */
#define VER 1.02


#include "file.h"

//define the server :
#include <WiFi.h>       // standard library
#include <WebServer.h>  // standard library
#include "html.h"

// here you post web pages to your homes intranet which will make page debugging easier
// as you just need to refresh the browser as opposed to reconnection to the web server
#define USE_INTRANET

// replace this with your homes intranet connect parameters
#define LOCAL_SSID "HUAWEI_H122_BE0F"
#define LOCAL_PASS "LDG2AMADAQ5"

// once  you are read to go live these settings are what you client will connect to
#define AP_SSID "MiniRobotV1_02"
#define AP_PASS "023456789"


// the XML array size needs to be bigger that your maximum expected size. 2048 is way too big for this example
char XML[2048];

// just some buffer holder for char operations
char buf[32];

// variable for the IP reported when you connect to your homes intranet (during debug mode)
IPAddress Actual_IP;

// definitions of your desired intranet created by the ESP32
IPAddress PageIP(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip;

// gotta create a server
WebServer server(80);


//End of Server configurations


// MiniRobot Configs:
// IR detorctor
#define IR 17

// Motor Driver
#define L1A 15   // L1 for motor A INT1
#define L2A 2    // L2 for motor A INT2
#define L1B 4   // L1 for motor B INT3
#define L2B 16   // L2 for motor B INT4



// SR04 pin difinitions
#define TRIG 5
#define ECHO 18


// Display settings:

//this part for the LCD, driver SSD1306 128x64 I2C

#define RL1
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//end of display settings

bool g_Forward = false;
bool g_Back = false;
bool g_Left = false;
bool g_Right = false;
bool g_Stop = true;
String g_Direciton = "STOP";

bool g_Free = true;
bool g_Obst = false;
bool g_lineFollow = false;
String g_Mode = "FREE";

uint32_t g_time = 0;

uint32_t g_sensorUpdate = 0;

// setup the Timer interupts 
////////////////////////////////////////////////////
////0 (Used by WiFi), 1 is available to configure.
/////////////////////////////////////////////////////

// or simply use tiker

#define ESP32MHz 80 //for ESP32 running at 80MHz
#define ESP32TIMER 2 //for wich ESP32 internal hardware timer will be used, there are 
#define ESP32TIMERCOUNT true // true => Count Up, false => cound Down
#define ESP32TAUTOENAB false // set auto enable on or off
#define ESP32INTMODE true // true=Edge triggered or false=Level triggered
hw_timer_t *g_Timer0_Cfg = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// this funciton will always revet back to stop condition
void IRAM_ATTR Timer0_ISR()
{
   //portENTER_CRITICAL_ISR(&timerMux);
    // function will be called when timer is completed.
    //timerStop(g_Timer0_Cfg);// stop it first, so to reset it, so serve new event call 
    ProcessButton_3(); // stop of motor, and set the massage to "STOP"
   //portEXIT_CRITICAL_ISR(&timerMux); 
}

void initTimer()
{
  g_Timer0_Cfg = timerBegin(ESP32TIMER, ESP32MHz, ESP32TIMERCOUNT);
  timerAttachInterrupt(g_Timer0_Cfg, &Timer0_ISR, ESP32INTMODE);
  //timerAlarmWrite(g_Timer0_Cfg, 1000, ESP32TAUTOENAB);
  //timerAlarmEnable(g_Timer0_Cfg);
  
}

void startTimer(uint32_t t)
{
  timerAlarmDisable(g_Timer0_Cfg);// stop it first, so to reset it, so serve new event call 
  timerAlarmWrite(g_Timer0_Cfg, t*1000, ESP32TAUTOENAB);
  timerAlarmEnable(g_Timer0_Cfg);
  //timerStart(g_Timer0_Cfg);
}
void stopTimer()
{
  timerStop(g_Timer0_Cfg);
}
//End of timer setup
///Ticker code
#include <Ticker.h>
#define TMULT 100
Ticker MotterStoper;
void INTStopMoter(void)
{
  ProcessButton_3();
}

Ticker RobotTurner;
bool g_LR = true;
bool g_timerCalled = false;
void INTgoForward(void)
{
   g_LR = !g_LR;
   g_timerCalled = false;
   
}


void setup() {
  initMotors();
  //initTimer();
  Serial.begin(115200);
  LCDinit();
  displayInit();
  initSR04();
  initIR();

    // Initialize SPIFFS
  #ifdef ESP32
    if(!SPIFFS.begin(true)){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
  #else
    if(!SPIFFS.begin()){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
  #endif

 // just an update to progress
  Serial.println("starting server");

  // if you have this #define USE_INTRANET,  you will connect to your home intranet, again makes debugging easier
#ifdef USE_INTRANET
  WiFi.begin(LOCAL_SSID, LOCAL_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
  Actual_IP = WiFi.localIP();
#endif

  // if you don't have #define USE_INTRANET, here's where you will creat and access point
  // an intranet with no internet connection. But Clients can connect to your intranet and see
  // the web page you are about to serve up
#ifndef USE_INTRANET
  WiFi.softAP(AP_SSID, AP_PASS);
  delay(100);
  WiFi.softAPConfig(PageIP, gateway, subnet);
  delay(100);
  Actual_IP = WiFi.softAPIP();
  Serial.print("IP address: "); Serial.println(Actual_IP);
#endif

  printWifiStatus();


  // these calls will handle data coming back from your web page
  // this one is a page request, upon ESP getting / string the web page will be sent
  server.on("/", SendWebsite);

  // upon esp getting /XML string, ESP will build and send the XML, this is how we refresh
  // just parts of the web page
  server.on("/xml", SendXML);

  // upon ESP getting /UPDATE_SLIDER string, ESP will execute the UpdateSlider function
  // same notion for the following .on calls
  // add as many as you need to process incoming strings from your web page
  // as you can imagine you will need to code some javascript in your web page to send such strings
  // this process will be documented in the SuperMon.h web page code
  server.on("/UPDATE_SLIDER", UpdateSlider);
  server.on("/BUTTON_0", ProcessButton_0);
  server.on("/BUTTON_1", ProcessButton_1);
  server.on("/BUTTON_2", ProcessButton_2);
  server.on("/BUTTON_3", ProcessButton_3);
  server.on("/BUTTON_4", ProcessButton_4);
  server.on("/BUTTON_5", ProcessButton_5);
  server.on("/BUTTON_6", ProcessButton_6);
  server.on("/BUTTON_7", ProcessButton_7);
  
  // finally begin the server
  server.begin();

  
  
}

void loop() {


  // update LCD every 50ms, .25 sec
  if ((millis() - g_sensorUpdate) >= 50) {
      g_sensorUpdate = millis();
      displayDis( distanceSR04());
      displayIR( getIR() );
      displayIP(WiFi.localIP().toString());
      if(g_Mode == "OBSTACLE"){
        ObstacleDetectionMode();
      }
      else if (g_Mode == "FOLLOW"){
        FollowLineMode();  
      }

      
        
  }
  //delay(500);
   server.handleClient();
}


// code to send the main web page
// PAGE_MAIN is a large char defined in SuperMon.h
void SendWebsite() {

  Serial.println("sending web page");
  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(200, "text/html", PAGE_MAIN);

}

// code to send the main web page
// I avoid string data types at all cost hence all the char mainipulation code
void SendXML() {

  // Serial.println("sending xml");

  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");


  // send Distance on V0 XML tages

  sprintf(buf, "<V0>%d</V0>\n", distanceSR04());
  strcat(XML, buf);

  // send IR V1
  sprintf(buf, "<V1>%d</V1>\n", getIR());
  strcat(XML, buf);

 // send Mode  V2
  sprintf(buf, "<V2>%s</V2>\n", g_Mode);
  strcat(XML, buf);

 // send Direction  V3
  sprintf(buf, "<V3>%s</V3>\n", g_Direciton);
  strcat(XML, buf);
  
   strcat(XML, "</Data>\n");
  // wanna see what the XML code looks like?
  // actually print it to the serial monitor and use some text editor to get the size
  // then pad and adjust char XML[2048]; above
  Serial.println(XML);

  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(200, "text/xml", XML);


}

void UpdateSlider()
{
   String t_state = server.arg("VALUE");

  // conver the string sent from the web page to an int
  g_time = t_state.toInt();
  Serial.print("UpdateSlider"); Serial.println(g_time);
   strcpy(buf, "");
  sprintf(buf, "%d", g_time);
  sprintf(buf, buf);

  // now send it back
  server.send(200, "text/plain", buf); //Send web page
}

void ProcessButton_0()
{
  // set mode to FOLLOW
  g_Mode = "FOLLOW";
  
}

void ProcessButton_1()
{
  // set mode to Obstacle
    g_Mode = "OBSTACLE";
}

void ProcessButton_2()
{
  // set mode to Free Form
    g_Mode = "FREE";
}

void ProcessButton_3()
{
  // set operation to Stop
 // g_Direciton = "STOP";
   stopMotors();
   
}

void ProcessButton_4()
{
  // set operation to Forward
  //g_Direciton = "FORWARD";
  forwareMotors();
  // need to add timer here to stop  it back
  //startTimer(g_time); // to convert ms to s
  MotterStoper.once_ms(g_time*TMULT,INTStopMoter);
}

void ProcessButton_5()
{
  // set operation to Reverse
 // g_Direciton = "REVERSE";
  reversMotors();
  MotterStoper.once_ms(g_time*TMULT,INTStopMoter);
    // need to add timer here to stop  it back
    
}

void ProcessButton_6()
{
  // set operation to Left
  //g_Direciton = "LEFT";
  leftMotors();
    MotterStoper.once_ms(g_time*TMULT,INTStopMoter);
  // need to add timer here to stop  it back
}

void ProcessButton_7()
{
  // set operation to Right
 // g_Direciton = "RIGHT";
  rightMotors();
    MotterStoper.once_ms(g_time*TMULT,INTStopMoter);
    // need to add timer here to stop  it back
}





void setGlobalsDirection(String var)
{
  if(var == "Stop")
  {
    stopMotors();
  }
  else if(var == "Forward")
  {
    forwareMotors();
  }
   else if(var == "Back")
  {
    reversMotors();
  }
  else if(var == "Left")
  {
    leftMotors();
  }
  else if(var == "Right")
  {
    rightMotors();
  }
  
  
}


void setGlobalsMode(String var)
{
  if(var == "Free")
  {
    g_Free = true;
    g_Obst = false;
    g_lineFollow = false;
  }
  else if (var == "Obstacle")
  {
     g_Free = false;
    g_Obst = true;
    g_lineFollow = false;
  }
  else if (var == "Follow")
  {
    g_Free = false;
    g_Obst = false;
    g_lineFollow = true;
  }
  
}
// LCD code
void LCDinit()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
}


void displayInit()
{
  display.clearDisplay();
  display.setTextSize(3);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(F("Mini"));
  display.println(F("Robot"));
  display.setTextSize(2);
  display.print(F("v:"));
  display.println(VER);
  display.display();
  delay(2000);
}


void displayDis(long d)
{
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.print(F("Dist:"));
  display.print(d);
  display.println(F("cm"));
 // display.display();

}


void displayIR(int d)
{
 // display.setTextSize(2);             // Normal 1:1 pixel scale
 // display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.print(F("IR: "));
  display.println(d);
  //display.display();
  //delay(100);
}

void displayIP(String ip)
{
 // display.setTextSize(2);             // Normal 1:1 pixel scale
//  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.print(ip);
  display.display();
  //delay(100);
}


// motor code
void initMotors()
{
  pinMode(L1A, OUTPUT);
  pinMode(L2A, OUTPUT);
  pinMode(L1B, OUTPUT);
  pinMode(L2B, OUTPUT);

  digitalWrite(L1A, LOW);
  digitalWrite(L2A, LOW);
  digitalWrite(L1B, LOW);
  digitalWrite(L2B, LOW);
}

void forwareMotors()
{
  g_Direciton = "FORWARD";
  digitalWrite(L1A, LOW); // this one is fliped
  digitalWrite(L2A, HIGH);
  digitalWrite(L1B, HIGH);
  digitalWrite(L2B, LOW);
}
void stopMotors()
{
  g_Direciton = "STOP";
  digitalWrite(L1A, LOW);
  digitalWrite(L2A, LOW);
  digitalWrite(L1B, LOW);
  digitalWrite(L2B, LOW);
}
void reversMotors()
{
  g_Direciton = "REVERSE";
  digitalWrite(L1A, HIGH); // this one is fliped
  digitalWrite(L2A, LOW);
  digitalWrite(L1B, LOW);
  digitalWrite(L2B, HIGH);
}
void leftMotors()
{
    g_Direciton = "LEFT";
    digitalWrite(L1A, LOW); // this one is fliped
  digitalWrite(L2A, HIGH);
  digitalWrite(L1B, LOW);
  digitalWrite(L2B, HIGH);

}
void rightMotors()
{
  g_Direciton = "RIGHT";
  digitalWrite(L1A, HIGH); // this one is fliped
  digitalWrite(L2A, LOW);
  digitalWrite(L1B, HIGH);
  digitalWrite(L2B, LOW);
}


// IR Code
void initIR()
{
    pinMode(IR, INPUT);
}

// will read 1 if Dark, 0 if bright
int getIR()
{
  return digitalRead(IR);
}

void initSR04()
{
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT); 
}

long distanceSR04()
{
  long duration = 0;
  long distance = 0;
  digitalWrite(TRIG, LOW); //set trigger signal low for 2us
  delayMicroseconds(2);
  
  /*send 10 microsecond pulse to trigger pin of HC-SR04 */
  digitalWrite(TRIG, HIGH);  // make trigger pin active high
  delayMicroseconds(10);            // wait for 10 microseconds
  digitalWrite(TRIG, LOW);   // make trigger pin active low
  /*Measure the Echo output signal duration or pulss width */
  duration = pulseIn(ECHO, HIGH); // save time duration value in "duration variable
  distance= duration*0.034/2.0; //Convert pulse duration into distance
  return distance;
}

// I think I got this code from the wifi example
void printWifiStatus() {

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("Open http://");
  Serial.println(ip);
}


void ObstacleDetectionMode()
{
  if (distanceSR04()<=20)
  {
    // just turn right for now
     rightMotors();
  }
  else
  {
    
    forwareMotors();
  }
}

void FollowLineMode()
{
  // 1 that is go staright

  if (getIR()==1)  // when line is detected, will getIR will be 1
  {
   
    RobotTurner.detach();
    g_timerCalled= false;
    forwareMotors();
  }
  else // else, we need to turn a bit left and abit right till we find it.
  {
    if (!g_timerCalled){ // don't call this till timer has finished
      g_timerCalled = true;
      RobotTurner.once_ms(g_time*TMULT,INTgoForward);
    }
      
    if (g_LR)
    {
      rightMotors();
    }
    else
    {
      leftMotors();
    }
  }
  
 
 
}
```

# html.h
```c
/*
 * This code has been based on work of https://github.com/KrisKasprzak/ESP32_WebPage
 * you can also go to his YouTube channel and see the way he did this : 
 * https://www.youtube.com/watch?v=pL3dhGtmcMY&t=1029s
 * 
 */

#ifndef __html_h__
#define __html_h__

const char PAGE_MAIN[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html lang="en" class="js-focus-visible">

<title>Web Page Update Demo</title>

  <style>
    table {
      position: relative;
      width:100%;
      border-spacing: 0px;
    }
    tr {
      border: 1px solid white;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
    }
    th {
      height: 20px;
      padding: 3px 15px;
      background-color: #343a40;
      color: #FFFFFF !important;
      }
    td {
      height: 20px;
       padding: 3px 15px;
    }
    .tabledata {
      font-size: 24px;
      position: relative;
      padding-left: 5px;
      padding-top: 5px;
      height:   25px;
      border-radius: 5px;
      color: #FFFFFF;
      line-height: 20px;
      transition: all 200ms ease-in-out;
      background-color: #00AA00;
    }
    .fanrpmslider {
      width: 30%;
      height: 55px;
      outline: none;
      height: 25px;
    }
    .bodytext {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 24px;
      text-align: left;
      font-weight: light;
      border-radius: 5px;
      display:inline;
    }
    .navbar {
      width: 100%;
      height: 50px;
      margin: 0;
      padding: 10px 0px;
      background-color: #FFF;
      color: #000000;
      border-bottom: 5px solid #293578;
    }
    .fixed-top {
      position: fixed;
      top: 0;
      right: 0;
      left: 0;
      z-index: 1030;
    }
    .navtitle {
      float: left;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 50px;
      font-weight: bold;
      line-height: 50px;
      padding-left: 20px;
    }
   .navheading {
     position: fixed;
     left: 60%;
     height: 50px;
     font-family: "Verdana", "Arial", sans-serif;
     font-size: 20px;
     font-weight: bold;
     line-height: 20px;
     padding-right: 20px;
   }
   .navdata {
      justify-content: flex-end;
      position: fixed;
      left: 70%;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      font-weight: bold;
      line-height: 20px;
      padding-right: 20px;
   }
    .category {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: bold;
      font-size: 32px;
      line-height: 50px;
      padding: 20px 10px 0px 10px;
      color: #000000;
    }
    .heading {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: normal;
      font-size: 28px;
      text-align: left;
    }
  
    .btn {
      background-color: #444444;
      border: none;
      color: white;
      padding: 10px 20px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 16px;
      margin: 4px 2px;
      cursor: pointer;
    }
    .foot {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      position: relative;
      height:   30px;
      text-align: center;   
      color: #AAAAAA;
      line-height: 20px;
    }
    .container {
      max-width: 1800px;
      margin: 0 auto;
    }
    table tr:first-child th:first-child {
      border-top-left-radius: 5px;
    }
    table tr:first-child th:last-child {
      border-top-right-radius: 5px;
    }
    table tr:last-child td:first-child {
      border-bottom-left-radius: 5px;
    }
    table tr:last-child td:last-child {
      border-bottom-right-radius: 5px;
    }
    
  </style>
<head>
  <title>MiniRobot V1.02</title>
</head>
  <body style="background-color: #efefef" onload="process()">
  
    <header>
      <div class="navbar fixed-top">
          <div class="container">
            <div class="navtitle">Mini Robot</div>
            <div class="navdata" id = "date">mm/dd/yyyy</div>
            <div class="navheading">DATE</div><br>
            <div class="navdata" id = "time">00:00:00</div>
            <div class="navheading">TIME</div>
            
          </div>
      </div>
    </header>
  
    <main class="container" style="margin-top:70px">
      <div class="category">Sensor Readings</div>
      <div style="border-radius: 10px !important;">
      <table style="width:50%">
      <colgroup>
        <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
        <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
       
      </colgroup>
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
     
      <tr>
        <th colspan="1"><div class="heading">Sensor</div></th>
        <th colspan="1"><div class="heading">Value</div></th>
        
      </tr>
      <tr>
        <td><div class="bodytext">Distance</div></td>
        <td><div class="tabledata" id = "v0"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">IR</div></td>
        <td><div class="tabledata" id = "v1"></div></td>
      </tr>
       <tr>
        <td><div class="bodytext">Mode</div></td>
        <td><div class="tabledata" id = "v2"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">Direction</div></td>
        <td><div class="tabledata" id = "v3"></div></td>
      </tr>
    </table>
    </div>
    <br>
    <div class="category">Mode Selection</div>
    <br>
    <table style="width:50%">
    <colgroup>
      <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
      <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
     
    </colgroup>
    <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
    <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
    <tr>
      <td><div class="bodytext">Follow Line</div></td>
      <td><button type="button" class = "btn" id = "btn0" onclick="ButtonPress0()">Toggle</button></div></td>
    </tr>
    
    <tr>
     <td><div class="bodytext">Obstacle</div></td>
    <td><button type="button" class = "btn" id = "btn1" onclick="ButtonPress1()">Toggle</button></div> </td>
    </tr>
    <tr>
      <td><div class="bodytext">Free Form</div></td>
       <td><button type="button" class = "btn" id = "btn2" onclick="ButtonPress2()">Toggle</button></div> </td>
    </tr>
     </table>
    <br>
    <br>
        <div class="category">Free Mode Controls</div>
    <br>
    <table style="width:50%">
    <colgroup>
      <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
      <col span="1" style="background-color:rgb(200,200,200); width: 20%; color:#000000 ;">        
      <col span="1" style="background-color:rgb(180,180,180); width: 20%; color:#000000 ;">
     
    </colgroup>
    <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
    <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
    <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
   <tr>
    <td></td>
    <td> 
    <button type="button" class = "btn" id = "btn4" onclick="ButtonPress4()">Toggle</button>
    </div></td>
    <td></td>
    </tr>

    <tr>
    <td>
      
    <button type="button" class = "btn" id = "btn6" onclick="ButtonPress6()">Toggle</button>
    </div>
    </td>
    <td>
       
    <button type="button" class = "btn" id = "btn3" onclick="ButtonPress3()">Toggle</button>
    </div>
    </td>

    <td>
           
    <button type="button" class = "btn" id = "btn7" onclick="ButtonPress7()">Toggle</button>
    </div>
    </td>
    </tr>

   <tr>
   <td>
   </td>
    <td>
     
    <button type="button" class = "btn" id = "btn5" onclick="ButtonPress5()">Toggle</button>
    </div>
   </td>
    <td>
   </td>
   </tr>
  
   

   

   </table>
    <br>
    <br>
    <div class="bodytext">Timer Control (x100ms: <span id="timeVal"></span>)</div>
    <br>
    <input type="range" class="fanrpmslider" min="0" max="100" value = "0" width = "0%" oninput="UpdateSlider(this.value)"/>
    <br>
    <br>
  </main>

  <footer div class="foot" id = "temp" >ESP32 Web Page for Mini Robot Ver 1.02 </div></footer>
  
  </body>


  <script type = "text/javascript">
  
    // global variable visible to all java functions
    var xmlHttp=createXmlHttpObject();

    // function to create XML object
    function createXmlHttpObject(){
      if(window.XMLHttpRequest){
        xmlHttp=new XMLHttpRequest();
      }
      else{
        xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
      }
      return xmlHttp;
    }

    // function to handle button press from HTML code above
    // and send a processing string back to server
    // this processing string is use in the .on method
    function ButtonPress0() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      // if you want to handle an immediate reply (like status from the ESP
      // handling of the button press use this code
      // since this button status from the ESP is in the main XML code
      // we don't need this
      // remember that if you want immediate processing feedbac you must send it
      // in the ESP handling function and here
      /*
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          message = this.responseText;
          // update some HTML data
        }
      }
      */
       
      xhttp.open("PUT", "BUTTON_0", false);
      xhttp.send();
    }


    // function to handle button press from HTML code above
    // and send a processing string back to server
    // this processing string is use in the .on method
    function ButtonPress1() {
      var xhttp = new XMLHttpRequest(); 
      /*
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("button1").innerHTML = this.responseText;
        }
      }
      */
      xhttp.open("PUT", "BUTTON_1", false);
      xhttp.send(); 
    }
    
    function ButtonPress2() {
      var xhttp = new XMLHttpRequest(); 
      xhttp.open("PUT", "BUTTON_2", false);
      xhttp.send(); 
    }
    function ButtonPress3() {
      var xhttp = new XMLHttpRequest(); 
      xhttp.open("PUT", "BUTTON_3", false);
      xhttp.send(); 
    }
    function ButtonPress4() {
      var xhttp = new XMLHttpRequest(); 
      xhttp.open("PUT", "BUTTON_4", false);
      xhttp.send(); 
    }    
    function ButtonPress5() {
      var xhttp = new XMLHttpRequest(); 
      xhttp.open("PUT", "BUTTON_5", false);
      xhttp.send(); 
    }    
    function ButtonPress6() {
      var xhttp = new XMLHttpRequest(); 
      xhttp.open("PUT", "BUTTON_6", false);
      xhttp.send(); 
    }  
    function ButtonPress7() {
      var xhttp = new XMLHttpRequest(); 
      xhttp.open("PUT", "BUTTON_7", false);
      xhttp.send(); 
    }          
    function UpdateSlider(value) {
      var xhttp = new XMLHttpRequest();
      // this time i want immediate feedback to the fan speed
      // yea yea yea i realize i'm computing fan speed but the point
      // is how to give immediate feedback
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          // update the web based on reply from  ESP
          document.getElementById("timeVal").innerHTML=this.responseText;
        }
      }
      // this syntax is really weird the ? is a delimiter
      // first arg UPDATE_SLIDER is use in the .on method
      // server.on("/UPDATE_SLIDER", UpdateSlider);
      // then the second arg VALUE is use in the processing function
      // String t_state = server.arg("VALUE");
      // then + the controls value property
      xhttp.open("PUT", "UPDATE_SLIDER?VALUE="+value, true);
      xhttp.send();
    }

    // function to handle the response from the ESP
    function response(){
      var message;
      var barwidth;
      var currentsensor;
      var xmlResponse;
      var xmldoc;
      var dt = new Date();
      var color = "#e8e8e8";
     
      // get the xml stream
      xmlResponse=xmlHttp.responseXML;
  
      // get host date and time
      document.getElementById("time").innerHTML = dt.toLocaleTimeString();
      document.getElementById("date").innerHTML = dt.toLocaleDateString();
  
      // v0
      xmldoc = xmlResponse.getElementsByTagName("V0"); 
      message = xmldoc[0].firstChild.nodeValue;
      
      if (message < 5){
      color = "#aa0000";
      }
      else {
        color = "#0000aa";
      }
      
      barwidth = message / 40.95;
      document.getElementById("v0").innerHTML=message;
      document.getElementById("v0").style.width=(barwidth+"%");
      // if you want to use global color set above in <style> section
      // other wise uncomment and let the value dictate the color
      document.getElementById("v0").style.backgroundColor=color;
     
      // v1
      xmldoc = xmlResponse.getElementsByTagName("V1");
      message = xmldoc[0].firstChild.nodeValue;
      if (message > 2048){
      color = "#aa0000";
      }
      else {
        color = "#0000aa";
      }
      document.getElementById("v1").innerHTML=message;
      width = message / 40.95;
      document.getElementById("v1").style.width=(width+"%");
      document.getElementById("v1").style.backgroundColor=color;

  
      xmldoc = xmlResponse.getElementsByTagName("V2");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("v2").innerHTML=message;
      if (message == "FREE"){
        document.getElementById("btn0").innerHTML="ON";
        document.getElementById("btn1").innerHTML="ON";
        document.getElementById("btn2").innerHTML="OFF";
      }
      else if (message == "FOLLOW") {
        document.getElementById("btn0").innerHTML="OFF";
        document.getElementById("btn1").innerHTML="ON";
        document.getElementById("btn2").innerHTML="ON";
      }
      else if (message == "OBSTACLE") {
        document.getElementById("btn0").innerHTML="ON";
        document.getElementById("btn1").innerHTML="OFF";
        document.getElementById("btn2").innerHTML="ON";
      }



      // Operation Mode   

      // Current Robot Direction    
      xmldoc = xmlResponse.getElementsByTagName("V3");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("v3").style.backgroundColor="rgb(200,200,200)";
      // update the text in the table
      if (message == "STOP"){
        document.getElementById("v3").innerHTML="STOP";
        document.getElementById("btn3").innerHTML="[STOP]";
        document.getElementById("btn3").style.color="#008000"; 
        document.getElementById("btn4").innerHTML="FORWARD"; 
        document.getElementById("btn4").style.color="#edeff2"; 
        document.getElementById("btn5").innerHTML="REVERSE";
        document.getElementById("btn5").style.color="#edeff2";
        document.getElementById("btn6").innerHTML="LEFT";
        document.getElementById("btn6").style.color="#edeff2"; 
        document.getElementById("btn7").innerHTML="RIGHT";
        document.getElementById("btn7").style.color="#edeff2"
        document.getElementById("v3").style.color="#0000AA"; 
      }
      else if (message == "FORWARD") {
        document.getElementById("v3").innerHTML="FORWARD";
        document.getElementById("btn3").innerHTML="STOP";
        document.getElementById("btn3").style.color="#edeff2"; 
        document.getElementById("btn4").innerHTML="[FORWARD]"; 
        document.getElementById("btn4").style.color="#ed091c";
        document.getElementById("btn5").innerHTML="REVERSE";
        document.getElementById("btn5").style.color="#edeff2";
        document.getElementById("btn6").innerHTML="LEFT";
        document.getElementById("btn6").style.color="#edeff2"; 
        document.getElementById("btn7").innerHTML="RIGHT";
        document.getElementById("btn7").style.color="#edeff2"
        document.getElementById("v3").style.color="#0000AA"; 
      }
       else if (message == "REVERSE") {
         document.getElementById("v3").innerHTML="REVERSE";
        document.getElementById("btn3").innerHTML="STOP";
        document.getElementById("btn3").style.color="#edeff2"; 
        document.getElementById("btn4").innerHTML="FORWARD"; //#ed091c
        document.getElementById("btn4").style.color="#edeff2";
        document.getElementById("btn5").innerHTML="[REVERSE]";
        document.getElementById("btn5").style.color="#ed091c";
        document.getElementById("btn6").innerHTML="LEFT";
        document.getElementById("btn6").style.color="#edeff2"; 
        document.getElementById("btn7").innerHTML="RIGHT";
        document.getElementById("btn7").style.color="#edeff2"

        document.getElementById("v3").style.color="#0000AA"; 
      }

       else if (message == "LEFT") {
        document.getElementById("v3").innerHTML="LEFT";
        document.getElementById("btn3").innerHTML="STOP";
        document.getElementById("btn3").style.color="#edeff2"; 
        document.getElementById("btn4").innerHTML="FORWARD"; //#ed091c
        document.getElementById("btn4").style.color="#edeff2";
        document.getElementById("btn5").innerHTML="REVERSE";
        document.getElementById("btn5").style.color="#edeff2";
        document.getElementById("btn6").innerHTML="[LEFT]";
        document.getElementById("btn6").style.color="#ed091c"; 
        document.getElementById("btn7").innerHTML="RIGHT";
        document.getElementById("btn7").style.color="#edeff2"
        document.getElementById("v3").style.color="#0000AA"; 
      }

       else if (message == "RIGHT") {
        document.getElementById("v3").innerHTML="RIGHT";
        document.getElementById("btn3").innerHTML="STOP";
        document.getElementById("btn3").style.color="#edeff2"; 
        document.getElementById("btn4").innerHTML="FORWARD"; //#ed091c
        document.getElementById("btn4").style.color="#edeff2";
        document.getElementById("btn5").innerHTML="REVERSE";
        document.getElementById("btn5").style.color="#edeff2";
        document.getElementById("btn6").innerHTML="LEFT";
        document.getElementById("btn6").style.color="#edeff2"; 
        document.getElementById("btn7").innerHTML="[RIGHT]";
        document.getElementById("btn7").style.color="#ed091c"
        document.getElementById("v3").style.color="#0000AA"; 
      }


      


      
     }
  
    // general processing code for the web page to ask for an XML steam
    // this is actually why you need to keep sending data to the page to 
    // force this call with stuff like this
    // server.on("/xml", SendXML);
    // otherwise the page will not request XML from the ESP, and updates will not happen
    function process(){
     
     if(xmlHttp.readyState==0 || xmlHttp.readyState==4) {
        xmlHttp.open("PUT","xml",true);
        xmlHttp.onreadystatechange=response;
        xmlHttp.send(null);
      }       
        // you may have to play with this value, big pages need more porcessing time, and hence
        // a longer timeout
        setTimeout("process()",100);
    }
  
  
  </script>

</html>
)rawliteral";

#endif
```


# file.h
```c
#ifndef __file_h__
#define __file_h__
#include <SPIFFS.h>






String readFile(fs::FS &fs, const char * path);
void writeFile(fs::FS &fs, const char * path, const char * message);







#endif
```


# file.cpp
```c++


#include "file.h"




String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
    Serial.println("- empty file or failed to open file");
    return String();
  }
  Serial.println("- read from file:");
  String fileContent;
  while(file.available()){
    fileContent+=String((char)file.read());
  }
  file.close();
  Serial.println(fileContent);
  return fileContent;
}

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
  file.close();
}
```
