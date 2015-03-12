////////// SETTINGS MENU //////////


void settings(){
  clearLCD();
  lcd.print("IN SETTINGS MENU");
  delay(1000);
  clearLCD();
  waitForRelease();
  int x = 0;
  int option = 0;
  int up_pressed, down_pressed;
  int last_option;
  while(x == 0){
    
    if(last_option != option) clearLCD();
    
    if(option == 0) cursorStart(), lcd.print("Timeout"), last_option = 0;
    if(option == 1) cursorStart(), lcd.print("Fade Delay"), last_option = 1;
    if(option == 2) cursorStart(), lcd.print("Switch Bright"), last_option = 2;
    if(option == 3) cursorStart(), lcd.print("EXIT"), last_option = 3;
        
    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW) {
      if(option == 0) timeout_menu();
      if(option == 1) update_single_setting("Fade Delay", base_fade_delay_add);
      if(option == 2); 
      if(option == 3) x = 1;
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
    
    if(option > 3) option = 0;
    if(option < 0) option = 3;
  }
}

////////// END SETTINGS MENU //////////

void update_single_setting(String item_name, int address){
  waitForRelease();
  int x = 0;
  int clear_screen = 1;
  int up_pressed, down_pressed;
  int item_variable = EEPROM.read(address);
  while (x == 0) {
    DateTime current_time = RTC.now();

    // CREATE a display for this.
    clear_screen = singleItem(clear_screen, item_name, item_variable);

    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW) x += 1;

    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if (up_pressed == 5) item_variable += 1, up_pressed = 0;
    }
    else up_pressed = 0;

    if (digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if (down_pressed == 5) item_variable -= 1, down_pressed = 0;
    }
    else down_pressed = 0;

    if (item_variable < 0) item_variable = 255;
    if (item_variable > 255) item_variable = 0;
  }
  clearLCD();
  if(item_variable != EEPROM.read(address)) EEPROM.write(address, item_variable);
  waitForRelease();
}


void timeout_menu(){
  waitForRelease();
  int x = 0;
  int up_pressed, down_pressed;
  int item_variable = EEPROM.read(cab_timeout_modifier_add);
  clearLCD();
  int last_option;
  while (x == 0) {
    DateTime current_time = RTC.now();
    
    if(last_option != item_variable) clearLCD();

    // CREATE a display for this.
    if(item_variable == 0) cursorStart(), lcd.print("Timeout Type"), cursor2Start(), lcd.print("Seconds"), last_option = 0;
    if(item_variable == 1) cursorStart(), lcd.print("Timeout Type"), cursor2Start(), lcd.print("Minutes"), last_option = 1;
    
    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW) x += 1;

    if (digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if (up_pressed == 5) item_variable += 1, up_pressed = 0;
    }
    else up_pressed = 0;

    if (digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if (down_pressed == 5) item_variable -= 1, down_pressed = 0;
    }
    else down_pressed = 0;

    if (item_variable < 0) item_variable = 1;
    if (item_variable > 1) item_variable = 0;
  }
  if(EEPROM.read(cab_timeout_modifier_add) != item_variable) EEPROM.write(cab_timeout_modifier_add, item_variable);
  
  clearLCD();
  waitForRelease();
  
  if(item_variable == 0) update_single_setting("Timeout Seconds", cab_timeout_add);
  if(item_variable == 1) update_single_setting("Timeout Minutes", cab_timeout_add);
  
  waitForRelease();
}
