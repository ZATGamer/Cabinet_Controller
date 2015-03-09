void lcdprintDZTime(int HH, int MM, int SS, int b){
  cursorStart();
  
  // If setting the Hour Blink, Else Display SOLID.
  if(b == 1){
    if(SS % 2 == 0){
      if(HH < 10){
        lcd.print(" ");
        lcd.print(HH);
      }
      else{
        lcd.print(HH);
      }
    }
    else if(digitalRead(UP_BUTTON) == LOW || digitalRead(DOWN_BUTTON) == LOW){
      if(HH < 10){
        lcd.print(" ");
        lcd.print(HH);
      }
      else{
        lcd.print(HH);
      }
    }
    else{
      lcd.print("  ");
    }
  }
  else{
    if(HH < 10){
      lcd.print(" ");
      lcd.print(HH);
    }
    else{
       lcd.print(HH);
    }
  }
  // Blink the ":" when just displaying the time
  // While setting time, display Solid.
  if(b == 0){
    if(SS % 2 == 0){
      lcd.print(":");
    }
    else lcd.print(" ");
  }
  else lcd.print(":");
  
  // If Setting Minute Blink, else display Solid.  
  if(b == 2){
    if(SS % 2 == 0){
      if(MM < 10){
        lcd.print("0");
        lcd.print(MM);
      }
      else{
        lcd.print(MM);
      }
    }
    else if(digitalRead(UP_BUTTON) == LOW || digitalRead(DOWN_BUTTON) == LOW){
      if(MM < 10){
        lcd.print("0");
        lcd.print(MM);
      }
      else{
        lcd.print(MM);
      }
    }
    else{
      lcd.print("  ");
    }
  }
  else{
    if(MM < 10){
      lcd.print("0");
      lcd.print(MM);
      }
      else{
        lcd.print(MM);
      }
  }
}


void custom_DZ_display(int dow, int setting){
  cursorStart();
  lcd.print(dow);
  lcd.print("-");
  DateTime current = RTC.now();
  
  if(current.second() % 2 == 0) lcd.print(setting);
  else if(digitalRead(UP_BUTTON) == LOW || digitalRead(DOWN_BUTTON) == LOW) lcd.print(setting);
  else lcd.print("  ");
  
  
  
  
}
