#include <Time.h>
#include <LiquidCrystal.h>

const int modSwitchPin = 7;
const int focusPin = 13;
const int shutterPin = 9;
const int backlightPin = 10;

int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
long interval = 100;           // interval at which to blink (milliseconds)

LiquidCrystal lcd(12, 11, 6, 5, 4, 8);


int encoderPin1 = 3;
int encoderPin2 = 2;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;
int movement = 0;

boolean modsel = false; //mode selection
boolean autofoc = false; //auto focus on or off
boolean run = false;

int rotam = 0;
int timeincn = 3;
int photon = 14;
int bulb = 0;
int nophoto = 9999;
int delaytimen = 0;
int curset = 1;
int nomenu = 6;
int brightness = 64;
int aniInt = 500;
int dispDimInt = 500;
int aniPos = 1;
int curBright = 0;
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

long takenPhoto = 0;
long delaytimer = 0;
long startTime =0;
long lastphotoMillis = 0;
long prevDel = 0;
long aniPrevMil = 0;
long dispDim = 0;
long currentMillis = 0;
long lastInt = 0;
long lastPush = 0;
long debDelay = 25;

String toShow2 = "" ;
String toShow1 = "" ;

const long timeinc[18] = {
  250,500,1e3,2e3,5e3,1e4,15e3,2e4,3e4,45e3,6e4,9e4,12e4,3e5,6e5,12e5,18e5,36e5
};
const int photoninc[15] = {
  1,2,5,10,15,20,25,50,100,200,500,1000,2000,5000,9999
};
const long bulbtimes[17] = {
  0,1e3,2e3,5e3,1e4,15e3,2e4,3e4,45e3,6e4,9e4,12e4,3e5,6e5,12e5,18e5,36e5
};
const long delaytime[17] = {
  0,1e3,2e3,5e3,1e4,15e3,2e4,3e4,45e3,6e4,9e4,12e4,3e5,6e5,12e5,18e5,36e5
};

byte backslash[8] = {
  0,16,8,4,2,1,0,0
};

void setup()
{
  //Rotary Encoder pins
  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);


  lcd.createChar(1, backslash);
  lcd.begin(16, 2);

  lcd.print("Booting:");
  lcd.setCursor(0,1);
  for (int tempbright=1 ; tempbright <= brightness; tempbright++){
    analogWrite(backlightPin, tempbright);
    delay(10);
    if (tempbright%4==0)
      lcd.print(".");
  };
  curBright = brightness;
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Startup");
  lcd.setCursor(0,1);
  lcd.print(" complete");
  analogWrite(backlightPin, brightness);
  delay(500);
  lcd.clear();

  //Mode Switch Input
  pinMode(modSwitchPin,INPUT);
  //focus
  pinMode(focusPin,OUTPUT);
  //shutter
  pinMode(shutterPin,OUTPUT);
}

void loop()
{
  currentMillis = millis();
  //Rotary Encoder Stuff
  if (abs(encoderValue-lastencoderValue)>3){
    if (encoderValue>lastencoderValue)
      movement=1;
    if (encoderValue<lastencoderValue)
      movement=-1;
    lastencoderValue=encoderValue; 
    lastInt=currentMillis;
  } 
  else
    movement=0;

  //Mode select button
  int reading = digitalRead(modSwitchPin);
  if (reading != lastButtonState) {
    lastPush = millis();
  } 

  if ((millis() - lastPush) > debDelay) {
    buttonState = reading;
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;


  if (buttonState == HIGH){
    modsel = !modsel;
  }
  if ((modsel==false)&&(run==false)){
    curset+=movement;
    lcd.setCursor(0,1);
    lcd.print(" ");
  };
  if (curset>nomenu)
    curset=1; 
  if (curset<0)
    curset=nomenu;
  //run menu
  menufunc();
  if ((run==true)&&(modsel==false)) {
    if (delaytimer<=0){
      if (photon==14) {
        //Infinity Case
        takephoto(timeinc[timeincn]);
        toShow1 = ">>"+String(takenPhoto)+"|"+String(char(243));
        lcd.setCursor(0,0);
        lcd.print(toShow1);
        progressani(1);
      } 
      else if ((takenPhoto<nophoto)){
        //Decrease photos

        takephoto(timeinc[timeincn]);
        toShow1 = ">>"+String(nophoto-takenPhoto)+"    ";
        lcd.setCursor(0,0);
        lcd.print(toShow1);
        progressani(1);
      };
    } 
    else if (delaytimer>0){
      //delay count down
      delaytimer -= currentMillis-prevDel;
      prevDel=currentMillis;
      displaytime(delaytimer);
      lcd.setCursor(0,0);
      lcd.print("Delay countdown");
      lcd.setCursor(0,1);
      //lcd.print(String(delaytimer));
      interval=delaytimer/100;
      progressani(-1);
    };
  }

  if(currentMillis - lastInt > 10000) {
    // save the last time you blinked the LED 
    displayDim(false);
  } 
  else
    displayDim(true);
}




















































