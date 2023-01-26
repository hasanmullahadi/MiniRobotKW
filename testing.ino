//written by :Hasan Ismail Ali, eng.hasan.m@gmail.com
//All rights left,
//Oct, 4, 2022


#define VER 1.0

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

#define IR 8

// Motor Driver
#define L1A 12   // L1 for motor A INT1
#define L2A 11   // L2 for motor A INT2
#define L1B 10   // L1 for motor B INT3
#define L2B 9   // L2 for motor B INT4


// SR04 pin difinitions
#define TRIG 5
#define ECHO 6


//Following for the button control:
#define buttonEnter 3//16

int g_Counter = 0;
bool g_Stop = true;
String g_Direciton = "STOP";
void setup()
{
  initButtons();
 initMotors();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  displayInit();

  initSR04();
  initIR();

}

void loop()
{
  
  if(!g_Stop)
  {
    g_Counter +=1;
  }
 // displayTimer();
  displayDis( distanceSR04());
  displayIR( getIR() );
  forwareMotors();
  delay(500);
  reversMotors();
  delay(500);
}

//Display Modes
void displayInit()
{
  display.clearDisplay();
  display.setTextSize(4);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(F("MinRobotTest"));
  display.setTextSize(2);
  display.print(F("v:"));
  display.println(VER);
  display.display();
  delay(2000);
}
//bool g_DozanDoDo= true;
//bool g_DozanFaFa = false;
//bool g_Strings5 = false;
//bool g_Strins6 = true;
//bool g_DoReMi = true;
//bool g_CDE = false;
void displayTimer()
{
  display.clearDisplay();
  display.setTextSize(4);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner

   display.println(g_Counter);
 
  display.display();
 // delay(2000);
}






//#define buttonEnter 16
//#define buttonR 17
//#define buttonL 18
//#define buttonBack 19
void initButtons()
{
  pinMode(buttonEnter, INPUT);
  

  attachInterrupt(digitalPinToInterrupt(buttonEnter), BEnter, CHANGE  );
//  attachInterrupt(digitalPinToInterrupt(buttonEnter), BEnterStop, RISING  );


}


void BEnter()
{
  if (digitalRead(buttonEnter) == HIGH)
  {
    g_Stop = false;
    g_Counter = 0;
  }
  if (digitalRead(buttonEnter) == LOW)
    g_Stop = true;
  
}

void BEnterStop()
{
  g_Stop = true;
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
  display.display();
  delay(100);
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

// IR Code
void initIR()
{
    pinMode(IR, INPUT);
}

int getIR()
{
  return digitalRead(IR);
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
