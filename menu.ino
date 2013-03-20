void menufunc() {
  switch (curset) {
  case 1:    
    //Time between photos
    lcd.setCursor(0, 0);
    lcd.print("Delta t         ");
    if (modsel == true){ 
      if (movement == 1)
        ++timeincn;
      if (movement == -1)
        --timeincn;
      if (timeincn<0)
        timeincn=18-1;
      if (timeincn>18-1)
        timeincn=0;
      lcd.setCursor(0,1);
      lcd.print(char(126));
    }
    displaytime(timeinc[timeincn]);
    //interval=timeinc[timeincn];
    break;
  case 2:    
    //Number of photos
    lcd.setCursor(0, 0);
    lcd.print("# Photos        "); 
    if (modsel == true){
      if (movement == 1)
        ++photon;
      if (movement == -1)
        --photon;
      if (photon<0) 
        photon = 14;
      if (photon>14)
        photon = 0;
      if ((photon < 14)&&(photon>=0)){
        displaynumber(photoninc[photon]);

      }
      else
        displaymsg(1);
      nophoto=photoninc[photon];  
      lcd.setCursor(0,1);
      lcd.print(char(126));
    }
    displaynumber(photoninc[photon]);
    break;
  case 3:    
    //Autofocus on/off
    lcd.setCursor(0, 0);
    lcd.print("Autofocus       "); 
    if (modsel == true){
      if (movement != 0)
        autofoc = !autofoc;
      lcd.setCursor(0,1);
      lcd.print(char(126));
    }
    if (autofoc == false)
      displaymsg(3);
    else
      displaymsg(2);
    break;
  case 4:    
    //Delay before first shot default 0
    lcd.setCursor(0, 0);
    lcd.print("1st Shot Delay  "); 
    if (modsel == true){ 
      if (movement == 1)
        ++delaytimen;
      if (movement == -1)
        --delaytimen;
      if (delaytimen<0)
        delaytimen=17-1;
      if (delaytimen>17-1)
        delaytimen=0;
      lcd.setCursor(0,1);
      lcd.print(char(126));
    }
    if (delaytimen==0)
      displaymsg(3);
    else
      displaytime(delaytime[delaytimen]);
    delaytimer=delaytime[delaytimen];
    break;
  case 5:
    lcd.setCursor(0, 0);
    lcd.print("Bulb Mode      "); 
    //Bulb mode
    if (modsel == true){ 
      if (movement == 1)
        ++bulb;
      if (movement == -1)
        --bulb;
      if (bulb<0)
        bulb=17-1;
      if (bulb>17-1)
        bulb=0;
      lcd.setCursor(0,1);
      lcd.print(char(126));
    }
    if (bulb==0)
      displaymsg(3);
    else
      displaytime(bulbtimes[bulb]);
    break;
  case 6:    
    //Run
    if ((run==false)&&(modsel==false)){
      lcd.setCursor(0, 0);
      lcd.print("Run            ");
    };
    if (modsel == true){ 
      if (movement != 0)
        run = !run;  
      lcd.setCursor(0,1);
      lcd.print(char(126));
    }
    if (run == false){
      startTime=0;
      displaymsg(3);
    }
    else if ((run == true)&&(modsel==true))
      displaymsg(2);
    if ((run == true)&&(modsel==false)&&(startTime==0))  {
      startTime = currentMillis;
      prevDel=startTime;
    };
    break;
  case 7:    
    //
    break;
  case 8:    
    //
    break;
  };
};

