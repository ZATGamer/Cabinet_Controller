////////// DEAD ZONE SETTINGS MENU //////////
void deadZoneSettings(){
  int new_dz_start, new_dz_end;

  clearLCD();
  cursorStart();
  lcd.print("IN DZ SET MENU");
  waitForRelease();
  clearLCD();
  
  
  // We will write all settings to EEPROM right after getting it. (But only if it changed).
  
  // Set the Default Dead Zone setting.
  //default_dz_start, default_dz_end = DZ_menu_item(default_dz_start, default_dz_end, 11);
  //if(EEPROM.read(dz_start_default_add) != default_dz_start) EEPROM.write(dz_start_default_add, default_dz_start);
  //if(EEPROM.read(dz_end_default_add) != default_dz_end) EEPROM.write(dz_end_default_add, default_dz_end);
  
  dz_startH_default, dz_startM_default = DZ_menu_item(dz_startH_default, dz_startM_default, 11);
  Serial.println("----------");
  Serial.println(dz_startH_default);
  Serial.println(dz_startM_default);
  Serial.println("----------");
  
  Serial.println(EEPROM.read(dz_startH_default_add));
  Serial.println(dz_startH_default);
  Serial.println(EEPROM.read(dz_startM_default_add));
  Serial.println(dz_startM_default);
  
  if(EEPROM.read(dz_startH_default_add) != dz_startH_default) EEPROM.write(dz_startH_default_add, dz_startH_default);
  if(EEPROM.read(dz_startM_default_add) != dz_startM_default) EEPROM.write(dz_startM_default_add, dz_startM_default);
  
  Serial.println(EEPROM.read(dz_startH_default_add));
  Serial.println(dz_startH_default);
  Serial.println(EEPROM.read(dz_startM_default_add));
  Serial.println(dz_startM_default);
  
  dz_endH_default, dz_endM_default = DZ_menu_item(dz_endH_default, dz_endM_default, 0);
  if(EEPROM.read(dz_endH_default_add) != dz_endH_default) EEPROM.write(dz_endH_default_add, dz_endH_default);
  if(EEPROM.read(dz_endM_default_add) != dz_endM_default) EEPROM.write(dz_endM_default_add, dz_endM_default);
  
  // Now check to see if we want to customize indivual days of the week.
  dz_custom_default = customize_DZ(11);
  if(EEPROM.read(dz_custom_default_add) != dz_custom_default) EEPROM.write(dz_custom_default_add, dz_custom_default);
  
  
  if(dz_custom_default == 1){
    // Now if we want to customize the other days of the week, lets get the settings for that now.
    dz_custom_0 = customize_DZ(0);
    if(EEPROM.read(dz_custom_0_add) != dz_custom_0) EEPROM.write(dz_custom_0_add, dz_custom_0);
    
    if(dz_custom_0 == 1) {
      dz_startH_0, dz_startM_0 = DZ_menu_item(dz_startH_0, dz_startM_0, 0);
      if(EEPROM.read(dz_startH_0_add) != dz_startH_0) EEPROM.write(dz_startH_0_add, dz_startH_0);
      if(EEPROM.read(dz_startM_0_add) != dz_startM_0) EEPROM.write(dz_startM_0_add, dz_startM_0);
      dz_endH_0, dz_endH_0 = DZ_menu_item(dz_endH_0, dz_endM_0, 0);
      if(EEPROM.read(dz_endH_0_add) != dz_endH_0) EEPROM.write(dz_endH_0_add, dz_endH_0);
      if(EEPROM.read(dz_endM_0_add) != dz_endM_0) EEPROM.write(dz_endM_0_add, dz_endM_0);
    }
    
    /* if(dz_custom_1 == 1) {
      dz_start_1, dz_end_1 = DZ_menu_item(dz_start_1, dz_end_1, 1);
      if(EEPROM.read(dz_start_1_add) != dz_start_1) EEPROM.write(dz_start_1_add, dz_start_1);
      if(EEPROM.read(dz_end_1_add) != dz_end_1) EEPROM.write(dz_end_1_add, dz_end_1);      
    }
    
    if(dz_custom_2 == 1) {
      dz_start_2, dz_end_2 = DZ_menu_item(dz_start_2, dz_end_2, 2);
      if(EEPROM.read(dz_start_2_add) != dz_start_2) EEPROM.write(dz_start_2_add, dz_start_2);
      if(EEPROM.read(dz_end_2_add) != dz_end_2) EEPROM.write(dz_end_2_add, dz_end_2);      
    }
    
    if(dz_custom_3 == 1) {
      dz_start_3, dz_end_3 = DZ_menu_item(dz_start_3, dz_end_3, 3);
      if(EEPROM.read(dz_start_3_add) != dz_start_3) EEPROM.write(dz_start_3_add, dz_start_3);
      if(EEPROM.read(dz_end_3_add) != dz_end_3) EEPROM.write(dz_end_3_add, dz_end_3);      
    }
    
    if(dz_custom_4 == 1) {
      dz_start_4, dz_end_4 = DZ_menu_item(dz_start_4, dz_end_4, 4);
      if(EEPROM.read(dz_start_4_add) != dz_start_4) EEPROM.write(dz_start_4_add, dz_start_4);
      if(EEPROM.read(dz_end_4_add) != dz_end_4) EEPROM.write(dz_end_4_add, dz_end_4);      
    }
    
    if(dz_custom_5 == 1) {
      dz_start_5, dz_end_5 = DZ_menu_item(dz_start_5, dz_end_5, 5);
      if(EEPROM.read(dz_start_5_add) != dz_start_5) EEPROM.write(dz_start_5_add, dz_start_5);
      if(EEPROM.read(dz_end_5_add) != dz_end_5) EEPROM.write(dz_end_5_add, dz_end_5);      
    }
    
    if(dz_custom_6 == 1) {
      dz_start_6, dz_end_6 = DZ_menu_item(dz_start_6, dz_end_6, 6);
      if(EEPROM.read(dz_start_6_add) != dz_start_6) EEPROM.write(dz_start_6_add, dz_start_6);
      if(EEPROM.read(dz_end_6_add) != dz_end_6) EEPROM.write(dz_end_6_add, dz_end_6);      
    }    */
  }
}

int DZ_menu_item(int current_hour, int current_minute, int dow){
  int new_hour, new_minute, new_second;
  int last_new_hour, last_new_minute, last_new_second;
  int b, x;
  int up_pressed, down_pressed, both_pressed;
    // Set the Default Dead Zone first.
  lcd.print(dow);
  lcd.print(" Hour");
  delay(1000);
  clearLCD();
  b = 1;
  x = 0;
  
  while(x == 0){
    DateTime current_time = RTC.now();

    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW){
      x += 1;
    }
    
    lcdprintDZTime(new_hour, current_minute, current_time.second(), b);
    
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
  
  waitForRelease();
  clearLCD();
  lcd.print(dow);
  lcd.print(" Minute");
  delay(1000);
  clearLCD();
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
  
  Serial.println("++++++++++");
  Serial.println(new_hour);
  Serial.println(new_minute);
  Serial.println("++++++++++");
  return new_hour, new_minute;
}



int customize_DZ(int dow){
  // Pass the Day of Week for display purpose.
  int x = 0;
  int new_custom;
  int up_pressed, down_pressed, both_pressed;
  
  clearLCD();
  waitForRelease();
  
  while(x == 0){
    
    custom_DZ_display(dow, new_custom);
    
    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW){
      x += 1;
    }
    
    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if(up_pressed == 15) new_custom += 1, up_pressed = 0;
    }
    else{
      up_pressed = 0;
    }
    
    if(digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if(down_pressed == 15) new_custom -= 1, down_pressed = 0;
    }
    else{
      down_pressed = 0;
    }
    
    if(new_custom > 1) new_custom = 0;
    if(new_custom < 0) new_custom = 1;
  }
  return new_custom;
  
}

////////// END DEAD ZONE SETTINGS MENU //////////
