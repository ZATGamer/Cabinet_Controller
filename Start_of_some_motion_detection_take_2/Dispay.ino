/*
This is all code to control the display.
*/

const int LCDdelay = 10;

void lcdprintTime_OLD(int HH, int MM, int SS){
  cursorStart();
  if(HH < 10){
    lcd.print(" ");
    lcd.print(HH);
  }
  else{
    lcd.print(HH);
  }
  if(SS % 2 == 0) lcd.print(":");
  else lcd.print(" ");
  if(MM < 10){
    lcd.print("0");
    lcd.print(MM);
  }
  else{
    lcd.print(MM);
  }
  /*lcd.print(":");
  if(SS < 10){
    lcd.print("0");
    lcd.print(SS);
  }
  else{
    lcd.print(SS);
  }*/
}


// CHANGED THIS
void lcdprintTime(int HH, int MM, int SS, int b = 0){
  cursorStart();
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
  
  lcd.print(":");
    
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


void lcdSetDate(int MONTH, int DAY, int SS, int b){
  cursorStart();
  if(b == 1){
    if(SS % 2 == 0){
      if(MONTH < 10){
        lcd.print(" ");
        lcd.print(MONTH);
      }
      else{
        lcd.print(MONTH);
      }
    }
    else if(digitalRead(UP_BUTTON) == LOW || digitalRead(DOWN_BUTTON) == LOW){
      if(MONTH < 10){
        lcd.print(" ");
        lcd.print(MONTH);
      }
      else{
        lcd.print(MONTH);
      }
    }
    else{
      lcd.print("  ");
    }
  }
  else{
    if(MONTH < 10){
      lcd.print(" ");
      lcd.print(MONTH);
      }
      else{
        lcd.print(MONTH);
      }
  }
  
  lcd.print("-");
    
  if(b == 2){
    if(SS % 2 == 0){
      if(DAY < 10){
        lcd.print("0");
        lcd.print(DAY);
      }
      else{
        lcd.print(DAY);
      }
    }
    else if(digitalRead(UP_BUTTON) == LOW || digitalRead(DOWN_BUTTON) == LOW){
      if(DAY < 10){
        lcd.print("0");
        lcd.print(DAY);
      }
      else{
        lcd.print(DAY);
      }
    }
    else{
      lcd.print("  ");
    }
  }
  else{
    if(DAY < 10){
      lcd.print("0");
      lcd.print(DAY);
      }
      else{
        lcd.print(DAY);
      }
  }
}

void lcdprintDate(int MONTH, int DAY, int YEAR){
  cursorStart();
  lcd.print(MONTH);
  lcd.print("-");
  lcd.print(DAY);
  lcd.print("-");
  lcd.print(YEAR);
}

void lcdprintDate2(int MONTH, int DAY){
  cursorStart();
  if(MONTH < 10){
    lcd.print(" ");
    lcd.print(MONTH);
  }
  else{
    lcd.print(MONTH);
  }
  lcd.print("-");
  if(DAY < 10){
    lcd.print(DAY);
    lcd.print(" ");
  }
  else{
    lcd.print(DAY);
  }
}

void lcdPrintYear(int YEAR){
  cursorStart();
  lcd.print(YEAR);
  lcd.print(" ");
}

void lcdSetYear(int YEAR, int SS){
  cursorStart();
  if(SS % 2 == 0) lcd.print(YEAR);
  else if(digitalRead(UP_BUTTON) == LOW || digitalRead(DOWN_BUTTON) == LOW) lcd.print(YEAR);
  else lcd.print("     ");
}





void lcdprintSecond(int SS){
  lcd.write(254);
  lcd.write(206);
  if(SS < 10){
    lcd.print("0");
    lcd.print(SS);
  }
  else{
    lcd.print(SS);
  }
}

void lcd_inital_start(){
  lcd.begin(9600);
  delay(500);
  lcd.write(254);
  lcd.write(0xC);
  delay(LCDdelay);
  clearLCD();
}


// Transitions
void lcdDash(){
  cursorStart();
  lcd.print("-----");
}

void wipeRight(){
  cursorStart();
  int x = 0;
  while(x < 16){
    lcd.print(" ");
    x += 1;
    delay(50);
  }
}

void wipeLeft(){
  int x = 5;
  int y = 132;
  while(x > 0){
    lcd.write(254);
    lcd.write(y);
    lcd.print(" ");
    y -= 1;
    x -= 1;
    delay(50);
  }
}

// END Transitions

// LCD General Control
void cursorStart(){
  lcd.write(254);
  lcd.write(128);
}

void clearLCD(){
  lcd.write(0xFE);
  lcd.write(0x01);
  delay(LCDdelay);
}
// END LCD General Control
    
