#define dst_start_month_add 12
#define dst_start_week_add 13
#define dst_start_dow_add 14
#define dst_start_hour_add 15

#define dst_end_month_add 16
#define dst_end_week_add 17
#define dst_end_dow_add 18
#define dst_end_hour_add 19

void set_time(){
  /*
  This is the Inital menu for all things Time. From here there will
  be 3 options. Set Clock, Set DST and EXIT.
  I will let the user select what they want to do. And then once both buttons
  are pressed I will go to the selected option.
  */
  clearLCD();
  cursorStart();
  lcd.print("SET TIME");
  waitForRelease();
  int x = 0;
  int option = 0;
  int up_pressed, down_pressed;
  while(x == 0){    
    if(option == 0) cursorStart(), lcd.print("Set Clock       ");
    if(option == 1) cursorStart(), lcd.print("Set DST         ");
    if(option == 2) cursorStart(), lcd.print("EXIT            ");

    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW) {
      if(option == 0) set_clock(), x = 1;
      if(option == 1) set_dst(), x = 1;
      if(option == 2) x += 1;
    }

    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if (up_pressed == 5) option += 1, up_pressed = 0;
    }
    else up_pressed = 0;

    if (digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if (down_pressed == 5) option -= 1, down_pressed = 0;
    }
    else down_pressed = 0;
    
    if(option > 2) option = 0;
    if(option < 0) option = 2;
  }
}

void set_clock(){
  // This is the function that will set the Time on the RTC.
  clearLCD();
  cursorStart();
  lcd.print("In Set Clock");
  delay(2000);
  waitForRelease();
  clearLCD();
  
  DateTime current_time = RTC.now();
  int new_hour = current_time.hour();
  if (in_DST()) {
    new_hour += 1;
    if (new_hour < 0) new_hour = 23;
    if (new_hour > 23) new_hour = 0;
  }
  
  new_hour = set_hour(new_hour, current_time.minute());
  int new_minute = set_minute(new_hour, current_time.minute());
  int new_year = set_year(current_time.year());
  int new_month = set_month(current_time.month(), current_time.day());
  int new_day = set_day(new_year, new_month, current_time.day());
  
  waitForRelease();
  
  if (in_DST()) {
    new_hour -= 1;
    if (new_hour < 0) new_hour = 23;
    if (new_hour > 23) new_hour = 0;
  }

  if (new_month != current_time.month() || new_day != current_time.day() || new_year != current_time.year() || new_hour != current_time.hour() || new_minute != current_time.minute()) {
    lcdDash();
    RTC.adjust(DateTime(new_year, new_month, new_day, new_hour, new_minute, 0));
    delay(250);
  }

  // Clear LCD after all done
  clearLCD();
  
}

void set_dst(){
  clearLCD();
  cursorStart();
  lcd.print("In Set DST");
  delay(2000);
  clearLCD();
  
  // We shall now get the current settings for DST and update if needed. 
  int start_month = set_month(EEPROM.read(dst_start_month_add), 0);
  if(start_month != EEPROM.read(dst_start_month_add)) EEPROM.write(dst_start_month_add, start_month);
  
  int start_week = set_month_week(EEPROM.read(dst_start_week_add));
  if(start_week != EEPROM.read(dst_start_week_add)) EEPROM.write(dst_start_week_add, start_week);
  
  int start_dow = set_dow(EEPROM.read(dst_start_dow_add));
  if(start_dow != EEPROM.read(dst_start_dow_add)) EEPROM.write(dst_start_dow_add, start_dow);
  
  int start_hour = set_hour(EEPROM.read(dst_start_hour_add), 0);
  if(start_hour != EEPROM.read(dst_start_hour_add)) EEPROM.write(dst_start_hour_add, start_hour);
  
  int end_month = set_month(EEPROM.read(dst_end_month_add), 0);
  if(end_month != EEPROM.read(dst_end_month_add)) EEPROM.write(dst_end_month_add, end_month);
  
  int end_week = set_month_week(EEPROM.read(dst_end_week_add));
  if(end_week != EEPROM.read(dst_end_week_add)) EEPROM.write(dst_end_week_add, end_week);
  
  int end_dow = set_dow(EEPROM.read(dst_end_dow_add));
  if(end_dow != EEPROM.read(dst_end_dow_add)) EEPROM.write(dst_end_dow_add, end_dow);
  
  int end_hour = set_hour(EEPROM.read(dst_end_hour_add), 0);
  if(end_hour != EEPROM.read(dst_end_hour_add)) EEPROM.write(dst_end_hour_add, end_hour);  
}



// Specific Functions for use.
int set_year(int new_year){
  waitForRelease();
  int x = 0;
  int b = 1;
  int up_pressed, down_pressed;
  while (x == 0) {
    DateTime current_time = RTC.now();
    
    lcdprintYear(new_year, current_time.second(), b);
    
    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW) x += 1;

    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if (up_pressed == 15) new_year += 1, up_pressed = 0;
    }
    else up_pressed = 0;

    if (digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if (down_pressed == 15) new_year -= 1, down_pressed = 0;
    }
    else down_pressed = 0;
  }
  return new_year;
}

int set_month(int new_month, int current_day){
  waitForRelease();
  int x = 0;
  int b = 1;
  int up_pressed, down_pressed;
  while (x == 0) {
    DateTime current_time = RTC.now();

    lcdprintDate(new_month, current_day, current_time.second(), b);

    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW) x += 1;

    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if (up_pressed == 15) new_month += 1, up_pressed = 0;
    }
    else up_pressed = 0;

    if (digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if (down_pressed == 15) new_month -= 1, down_pressed = 0;
    }
    else down_pressed = 0;

    if (new_month < 1) new_month = 12;
    if (new_month > 12) new_month = 1;
  }
  return new_month;
}

int set_day(int zYear, int zMonth, int new_day){
  waitForRelease();
  int x = 0;
  int up_pressed, down_pressed;
  int b = 2;
  
  while (x == 0) {
    DateTime current_time = RTC.now();
    
    lcdprintDate(zMonth, new_day, current_time.second(), b);

    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW) x += 1;

    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if (up_pressed == 15) new_day += 1, up_pressed = 0;
    }
    else up_pressed = 0;

    if (digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if (down_pressed == 15) new_day -= 1, down_pressed = 0;
    }
    else down_pressed = 0;
    
    // Figure out how many days are allowed in the month.
    if (zMonth == 1 || zMonth == 3 || zMonth == 5 || zMonth == 7 || zMonth == 8 || zMonth == 10 || zMonth == 12) {
      if (new_day < 1) new_day = 31;
      if (new_day > 31) new_day = 1;
    }
    if (zMonth == 4 || zMonth == 6 || zMonth == 9 || zMonth == 11) {
      if (new_day < 1) new_day = 30;
      if (new_day > 30) new_day = 1;
    }
    if (zMonth == 2) {
      if (zYear % 4 == 0) {
        if (new_day < 1) new_day = 29;
        if (new_day > 29) new_day = 1;
      }
      else {
        if (new_day < 1) new_day = 28;
        if (new_day > 28) new_day = 1;
      }
    }
  }
  return new_day;
}


int set_month_week(int new_month_week){
  waitForRelease();
  int x = 0;
  int b = 1;
  int up_pressed, down_pressed;
  while (x == 0) {
    DateTime current_time = RTC.now();

    // CREATE a display for this.
    cursorStart();
    lcd.print(new_month_week);

    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW) x += 1;

    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if (up_pressed == 15) new_month_week += 1, up_pressed = 0;
    }
    else up_pressed = 0;

    if (digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if (down_pressed == 15) new_month_week -= 1, down_pressed = 0;
    }
    else down_pressed = 0;

    if (new_month_week < 1) new_month_week = 4;
    if (new_month_week > 4) new_month_week = 1;
  }
  return new_month_week;
}

int set_dow(int new_dow){
  waitForRelease();
  int x = 0;
  int b = 1;
  int up_pressed, down_pressed;
  while (x == 0) {
    DateTime current_time = RTC.now();

    // CREATE a display for this.
    cursorStart();
    lcd.print(new_dow);

    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW) x += 1;

    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if (up_pressed == 15) new_dow += 1, up_pressed = 0;
    }
    else up_pressed = 0;

    if (digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if (down_pressed == 15) new_dow -= 1, down_pressed = 0;
    }
    else down_pressed = 0;

    if (new_dow < 0) new_dow = 6;
    if (new_dow > 6) new_dow = 0;
  }
  return new_dow;
}


