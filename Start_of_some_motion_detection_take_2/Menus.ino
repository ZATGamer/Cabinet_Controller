void settime(){
  // This is the Menu for Setting the time.
  cursorStart();
  lcd.print("*****");
  waitForRelease();  
  DateTime current_time = RTC.now();
  int x = 0;
  int new_hour = current_time.hour();
  int new_minute = current_time.minute();
  int new_second = 0;
  int last_new_hour = current_time.hour();
  int last_new_minute = current_time.minute();
  int last_new_second = current_time.second();
  int b;
  int up_pressed, down_pressed, both_pressed;
  
  // HOUR SETTINGS
  b = 1;
  while(x == 0){
    DateTime current_time = RTC.now();

    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW){
      x += 1;
    }
    if(new_hour != last_new_hour){
      last_new_hour = new_hour;
      printTime(new_hour, current_time.minute(), new_second);
    }
    
    lcdprintTime(new_hour, current_time.minute(), current_time.second(), b);
    
    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if(up_pressed == 15) new_hour += 1, up_pressed = 0;
    }
    else{
      up_pressed = 0;
    }
    
    if(digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if(down_pressed == 15) new_hour -= 1, down_pressed = 0;
    }
    else{
      down_pressed = 0;
    }
    
    if(new_hour > 23) new_hour = 0;
    if(new_hour < 0) new_hour = 23;
  }

  // MINUTE SETTINGS
  waitForRelease();
  x = 0;
  b = 2;
  while(x == 0){
    DateTime current_time = RTC.now();
    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW){
      x += 1;
    }
    if(new_minute != last_new_minute){
      last_new_minute = new_minute;
      printTime(new_hour, new_minute, new_second);
    }

    lcdprintTime(new_hour, new_minute, current_time.second(), b);

    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if(up_pressed == 15) new_minute += 1, up_pressed = 0;
    }
    else{
      up_pressed = 0;
    }
    
    if(digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if(down_pressed == 15) new_minute -= 1, down_pressed = 0;
    }
    else{
      down_pressed = 0;
    }
    
    if(new_minute > 59) new_minute = 0;
    if(new_minute < 0) new_minute = 59;
  }
    
  // YEAR SETTINGS
  waitForRelease();
  x = 0;
  int last_new_year = current_time.year();
  int new_year = current_time.year();
  while(x == 0){
    DateTime current_time = RTC.now();

    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW){
      x += 1;
    }
    if(new_year != last_new_year){
      last_new_year = new_year;
      lcdPrintYear(new_year);
    }
    
    lcdSetYear(new_year, current_time.second());
    
    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if(up_pressed == 15) new_year += 1, up_pressed = 0;
    }
    else{
      up_pressed = 0;
    }
    
    if(digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if(down_pressed == 15) new_year -= 1, down_pressed = 0;
    }
    else{
      down_pressed = 0;
    }

  }
  
  // MONTH SETTINGS
  waitForRelease();
  x = 0;
  b = 1;
  int last_new_month = current_time.month();
  int new_month = current_time.month();
  while(x == 0){
    DateTime current_time = RTC.now();
    
    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW){
      x += 1;
    }
    if(new_month != last_new_month){
      last_new_month = new_month;
      printDate2(new_month, current_time.day());
    }
    
    lcdSetDate(new_month, current_time.day(), current_time.second(), b);
    
    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if(up_pressed == 15) new_month += 1, up_pressed = 0;
    }
    else{
      up_pressed = 0;
    }
    
    if(digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if(down_pressed == 15) new_month -= 1, down_pressed = 0;
    }
    else{
      down_pressed = 0;
    }
    
    if(new_month < 1) new_month = 12;
    if(new_month > 12) new_month = 1;
  }
  waitForRelease();
  
  
  // DAY SETTING
  waitForRelease();
  x = 0;
  b = 2;
  int last_new_day = current_time.day();
  int new_day = current_time.day();
  while(x == 0){
    DateTime current_time = RTC.now();
    
    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW){
      x += 1;
    }
    if(new_day != last_new_day){
      last_new_day = new_day;
      printDate2(new_month, new_day);
    }
    
    lcdSetDate(new_month, new_day, current_time.second(), b);
    
    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if(up_pressed == 15) new_day += 1, up_pressed = 0;
    }
    else{
      up_pressed = 0;
    }
    
    if(digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if(down_pressed == 15) new_day -= 1, down_pressed = 0;
    }
    else{
      down_pressed = 0;
    }
    
    if(new_month == 1 || new_month == 3 || new_month == 5 || new_month == 7 || new_month == 8 || new_month == 10 || new_month == 12){
      if(new_day < 1) new_day = 31;
      if(new_day > 31) new_day = 1;
    }
    if(new_month == 4 || new_month == 6 || new_month == 9 || new_month == 11){
      if(new_day < 1) new_day = 30;
      if(new_day > 30) new_day = 1;
    }
    if(new_month == 2){
      if(new_year % 4 == 0){
        if(new_day < 1) new_day = 29;
        if(new_day > 29) new_day = 1;
      }
      else{
        if(new_day < 1) new_day = 28;
        if(new_day > 28) new_day = 1;
      }
    }
  }
  waitForRelease();
  
  if(new_month != current_time.month() || new_day != current_time.day() || new_year != current_time.year() || new_hour != current_time.hour() || new_minute != current_time.minute()){
    lcdDash();
    RTC.adjust(DateTime(new_year, new_month, new_day, new_hour, new_minute, new_second));
    delay(250);
  }
  
  // Clear LCD after all done
  clearLCD();
  
}

void settings(){
  lcd.write(254);
  lcd.write(0x01);
  lcd.print("IN SETTINGS MENU");
  delay(1000);
  lcd.write(254);
  lcd.write(0x01);
}

void deadZoneSettings(){
  lcd.write(254);
  lcd.write(0x01);
  lcd.print("IN DZ SET MENU");
  delay(1000);
  lcd.write(254);
  lcd.write(0x01);
}


void waitForRelease(){
  while(digitalRead(UP_BUTTON) == LOW || digitalRead(DOWN_BUTTON) == LOW){
  }
}
