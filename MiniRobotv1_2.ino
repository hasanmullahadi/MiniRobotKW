/*
 * MiniRobot
 * Developed by: Hasan I A A Mohammad
 * email @ eng.hasan.m@gmail.com
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
#define LOCAL_SSID "YOURROUTERNAME"
#define LOCAL_PASS "YOURROUTERPASSWORD"

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
