void  displaynumber(int num)
{
  if (num==9999)
    toShow2 = String(char(243))+"              ";
  else {
    toShow2 = String(num)+"         ";
  };
  lcd.setCursor(1, 1);
  lcd.print(toShow2);
};

void  displaytime(long num)
{
  int mil = 0;
  mil=num%1000;
  num=num/1000;
  if (hour(num)<10)
    toShow2 = "0";
  if (hour(num)==0)
    toShow2 += "0";
  if (hour(num)>=1)
    toShow2 += String(hour(num));
  toShow2 += ":";

  if (minute(num)<10)
    toShow2 += "0";
  if (minute(num)==0)
    toShow2 += "0";
  if (minute(num)>=1)
    toShow2 += String(minute(num));
  toShow2 += ":";

  if (second(num)<10)
    toShow2 += "0";
  if (second(num)==0)
    toShow2 += "0";
  if (second(num)>=1)
    toShow2 += String(second(num));
  toShow2 += ",";

  if (mil<10)
    toShow2 += "0";
  if (mil==0)
    toShow2 += "0";
  if (mil>=1)
    toShow2 += String(mil/10);

  toShow2 += "  ";
  lcd.setCursor(1, 1);
  lcd.print(toShow2);
};

void  displaymsg(int num)
{
  switch (num) {
  case 1:
    toShow2 = String(char(243))+"              ";
    lcd.setCursor(1, 1);
    lcd.print(toShow2);
    break;
  case 2:
    toShow2= "On             ";
    lcd.setCursor(1, 1);
    lcd.print(toShow2);
    break;
  case 3: //off
    toShow2= "Off             ";
    lcd.setCursor(1, 1);
    lcd.print(toShow2);
    break;
  };
};

void  progressani(int dir)
{
  String aniChar = "";
  if(currentMillis - aniPrevMil > aniInt) {
    // save the last time you blinked the LED 
    aniPrevMil = currentMillis;   
    if (dir>0)
      aniPos++;
    else
      aniPos--;
    if (aniPos==5)
      aniPos=1;
    if (aniPos==0)
      aniPos=4;
    // if the LED is off turn it on and vice-versa:
    switch (aniPos){
    case 1:
      aniChar = "|";
      lcd.setCursor(15,0);
      lcd.print(aniChar);
      break;
    case 2:
      aniChar = "/";
      lcd.setCursor(15,0);
      lcd.print(aniChar);
      break;
    case 3:
      aniChar = "-";
      lcd.setCursor(15,0);
      lcd.print(aniChar);
      break;
    case 4:
      lcd.setCursor(15,0);
      lcd.write(1);
      break;
    };

  }
};


void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}

void displayDim(boolean state){
  if ((state==true)&&(curBright!=brightness)){
    curBright=brightness;
    analogWrite(backlightPin, curBright);
  } 
  else
    if(currentMillis - dispDim > dispDimInt) {
      // save the last time you blinked the LED 
      previousMillis = currentMillis; 
      if (curBright>0) 
        --curBright;
      analogWrite(backlightPin, curBright);
    };  
};


