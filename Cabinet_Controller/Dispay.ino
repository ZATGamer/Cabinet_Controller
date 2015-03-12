/*
This is all code to control the display.
*/

////////// CLOCK DISPLAY //////////

void lcdprintTime(int HH, int MM, int SS, int b){
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

void lcdprintDate(int MONTH, int DAY, int SS, int b){
  cursorStart();
  
  // IF setting MONTH Blink, Else Display SOLID
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
    
  // IF Setting Day Blink, Else display SOLID  
  if(b == 2){
    if(SS % 2 == 0){
        lcd.print(DAY);
    }
    else if(digitalRead(UP_BUTTON) == LOW || digitalRead(DOWN_BUTTON) == LOW){
        lcd.print(DAY);
    }
    else{
      lcd.print("  ");
    }
  }
  else{
    lcd.print(DAY);
  }
}

void lcdprintYear(int YEAR, int SS, int b){
  // IF setting Year BLINK, Else Display SOLID
  if(b == 1){
    cursorStart();
    if(SS % 2 == 0) lcd.print(YEAR), lcd.print(" ");
    else if(digitalRead(UP_BUTTON) == LOW || digitalRead(DOWN_BUTTON) == LOW) lcd.print(YEAR);
    else lcd.print("     ");
  }
  else cursorStart(), lcd.print(YEAR), lcd.print(" ");
}

////////// END CLOCK DISPLAY //////////


////////// Transitions //////////

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

////////// END Transitions //////////


////////// LCD Utilities //////////

const int LCDdelay = 10;

void cursorStart(){
  lcd.write(254);
  lcd.write(128);
}

void cursor2Start(){
  lcd.write(254);
  lcd.write(192);
}

void clearLCD(){
  lcd.write(0xFE);
  lcd.write(0x01);
  delay(LCDdelay);
}

void lcd_inital_start(){
  lcd.begin(9600);
  delay(500);
  lcd.write(254);
  lcd.write(0xC);
  delay(LCDdelay);
  clearLCD();
}

////////// END LCD Utilities //////////


// This function is Strictly for Development Once Final, this will go away.
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



int singleItem(int clear_screen, String item_name, int item_variable){
  if(clear_screen == 1) clearLCD(), clear_screen = 0;
  cursorStart();
  lcd.print(item_name);
  cursor2Start();
  if(item_variable < 10) lcd.print(item_variable), lcd.print("  ");
  if(item_variable >= 10 && item_variable < 100) lcd.print(item_variable), lcd.print(" ");
  if(item_variable >= 100) lcd.print(item_variable);  
  return clear_screen;
}

int itemName(int clear_screen, String item_name){
  if(clear_screen == 1) clearLCD(), clear_screen = 0;
  cursorStart();
  lcd.print(item_name);
  return clear_screen;
}
