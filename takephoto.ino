void  takephoto(long pinterval){
  if (bulb==0){ //non bulb mode
    if((currentMillis - lastphotoMillis > pinterval-1000)&&(autofoc==true)) { 
      digitalWrite(focusPin, HIGH);
    };
    if(currentMillis - lastphotoMillis > pinterval-100) {
      lastphotoMillis = currentMillis;   
      digitalWrite(shutterPin, HIGH);
      delay(100);
      digitalWrite(focusPin,LOW);
      digitalWrite(shutterPin, LOW);
      ++takenPhoto;
    };
    displaytime(pinterval+(lastphotoMillis-currentMillis));
    lcd.setCursor(14,1);
    if (autofoc==true)
      lcd.print("AF");
    else
      lcd.print("MF");
  } 
  else { //bulb mode
    if(currentMillis - lastphotoMillis > pinterval) {
      lastphotoMillis = currentMillis;
      digitalWrite(shutterPin, LOW);   
      digitalWrite(shutterPin, HIGH);
      lcd.setCursor(15,1);
      lcd.print("!");
    };
    if (currentMillis - lastphotoMillis > bulbtimes[bulb]) {
      digitalWrite(shutterPin, LOW);
      lcd.setCursor(15,1);
      lcd.print("o");
      ++takenPhoto;
    };
  };
}





