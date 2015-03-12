#define _dead_zone_add 20
#define dz_option_add 21

#define dz_base_startH_add 22
#define dz_base_startM_add 23
#define dz_base_endH_add 24
#define dz_base_endM_add 25

#define dz_weekend_startH_add 26
#define dz_weekend_startM_add 27
#define dz_weekend_endH_add 28
#define dz_weekend_endM_add 29

#define dz_weekday_startH_add 30
#define dz_weekday_startM_add 31
#define dz_weekday_endH_add 32
#define dz_weekday_endM_add 33

#define dz_0_startH_add 34
#define dz_0_startM_add 35
#define dz_0_endH_add 36
#define dz_0_endM_add 37

#define dz_1_startH_add 38
#define dz_1_startM_add 39
#define dz_1_endH_add 40
#define dz_1_endM_add 41

#define dz_2_startH_add 42
#define dz_2_startM_add 43
#define dz_2_endH_add 44
#define dz_2_endM_add 45

#define dz_3_startH_add 46
#define dz_3_startM_add 47
#define dz_3_endH_add 48
#define dz_3_endM_add 49

#define dz_4_startH_add 50
#define dz_4_startM_add 51
#define dz_4_endH_add 52
#define dz_4_endM_add 53

#define dz_5_startH_add 54
#define dz_5_startM_add 55
#define dz_5_endH_add 56
#define dz_5_endM_add 57

#define dz_6_startH_add 58
#define dz_6_startM_add 59
#define dz_6_endH_add 60
#define dz_6_endM_add 61

int dead_zone(int dow, int current){  
  int _dead_zone = EEPROM.read(_dead_zone_add);
  int option = EEPROM.read(dz_option_add);
  int dz_start, dz_end;
  
  if (_dead_zone == 1){
    // Dead Zone Wanted, Now figure out what configuration
    if(option == 0){
      // One setting
      dz_start = int_time_passed(EEPROM.read(dz_base_startH_add), EEPROM.read(dz_base_startM_add));
      dz_end = int_time_passed(EEPROM.read(dz_base_endH_add), EEPROM.read(dz_base_endM_add));
    }
    
    if(option == 1){
      // Weekend/Weekday Settings
      if(dow == 0 || dow == 6){
        // Weekend Setting
        dz_start = int_time_passed(EEPROM.read(dz_weekend_startH_add), EEPROM.read(dz_weekend_startM_add));
        dz_end = int_time_passed(EEPROM.read(dz_weekend_endH_add), EEPROM.read(dz_weekend_endM_add));
      }
      else{
        // Weekday Setting
        dz_start = int_time_passed(EEPROM.read(dz_weekday_startH_add), EEPROM.read(dz_weekday_startM_add));
        dz_end = int_time_passed(EEPROM.read(dz_weekday_endH_add), EEPROM.read(dz_weekday_endM_add));
      }
    }
    if(option == 2){
    // Every Day different Settings
      if(dow == 0){
        // Sunday Settings
        dz_start = int_time_passed(EEPROM.read(dz_0_startH_add), EEPROM.read(dz_0_startM_add));
        dz_end = int_time_passed(EEPROM.read(dz_0_endH_add), EEPROM.read(dz_0_endM_add));
      }
      if(dow == 1){
        // Monday Settings
        dz_start = int_time_passed(EEPROM.read(dz_1_startH_add), EEPROM.read(dz_1_startM_add));
        dz_end = int_time_passed(EEPROM.read(dz_1_endH_add), EEPROM.read(dz_1_endM_add));
      }
      if(dow == 2){
        // Tuesday Settings
        dz_start = int_time_passed(EEPROM.read(dz_2_startH_add), EEPROM.read(dz_2_startM_add));
        dz_end = int_time_passed(EEPROM.read(dz_2_endH_add), EEPROM.read(dz_2_endM_add));
      }
      if(dow == 3){
        // Wednesday Settings
        dz_start = int_time_passed(EEPROM.read(dz_3_startH_add), EEPROM.read(dz_3_startM_add));
        dz_end = int_time_passed(EEPROM.read(dz_3_endH_add), EEPROM.read(dz_3_endM_add));
      }
      if(dow == 4){
        // Thursday Settings
        dz_start = int_time_passed(EEPROM.read(dz_4_startH_add), EEPROM.read(dz_4_startM_add));
        dz_end = int_time_passed(EEPROM.read(dz_4_endH_add), EEPROM.read(dz_4_endM_add));
      }
      if(dow == 5){
        // Friday Settings
        dz_start = int_time_passed(EEPROM.read(dz_5_startH_add), EEPROM.read(dz_5_startM_add));
        dz_end = int_time_passed(EEPROM.read(dz_5_endH_add), EEPROM.read(dz_5_endM_add));
      }
      if(dow == 6){
        // Saturday Settings
        dz_start = int_time_passed(EEPROM.read(dz_6_startH_add), EEPROM.read(dz_6_startM_add));
        dz_end = int_time_passed(EEPROM.read(dz_6_endH_add), EEPROM.read(dz_6_endM_add));
      }
    }
  }
  else return 0; // If no dead zone selected. Return 0 to indicate Out of DeadZone.
    
  
  // Now we have the Dead Zone values, lets determin if we are in or out of the Dead Zone.
  if(dz_start < dz_end){
    if(dz_start <= current && current < dz_end) return 1;
    else return 0;
  }
  else if(! (dz_end <= current && current < dz_start)) return 1;
  else return 0;
}

void dead_zone_menu(){  
  // PRINT SOMETHING TO INDICATE IN THE MENU
  lcdDash();
  
  // Wait for the buttons to be released
  waitForRelease();
  // Ask if there Should be a Dead Zone
  
  // Read in the dz variable form EEPROM and Error Check. If it has never been set. Set to 0.
  int dz = EEPROM.read(_dead_zone_add);
  if(dz == 255) dz = 0;
  
  // General Variables used for button presses.
  int up_pressed, down_pressed;
  int x = 0;
  while(x == 0){
    // At this point Lets display the current value.
    yes_no_option_display(00, dz);
        
    // Button Press Checking.
    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW) x += 1;
    
    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if(up_pressed == 15) dz += 1, up_pressed = 0;
    }
    else up_pressed = 0;
    
    if(digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if(down_pressed == 15) dz -= 1, down_pressed = 0;
    }
    else down_pressed = 0;
    
    if(dz > 1) dz = 0;
    if(dz < 0) dz = 1;
  }
  // Update the EEPROM value if it isn't the same as what was just set.
  if(EEPROM.read(_dead_zone_add) != dz) EEPROM.write(_dead_zone_add, dz);
  
  // Now if NO dead zone wanted, no need to set the rest. But if Dead Zone wanted, Check What type of settings.
  if(dz != 0){
    // What type of configurations?
    
    waitForRelease();
    x = 0;
    // Read in option variable and Error Check.
    int option = EEPROM.read(dz_option_add);
    if(option == 255) option = 0;
        
    while(x == 0){
      // Add display output.
      yes_no_option_display(1, option);
      
      if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW) x += 1;
    
      if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
        up_pressed += 1;
        if(up_pressed == 15) option += 1, up_pressed = 0;
      }
      else up_pressed = 0;
    
      if(digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
        down_pressed += 1;
        if(down_pressed == 15) option -= 1, down_pressed = 0;
      }
      else down_pressed = 0;
    
      if(option > 2) option = 0;
      if(option < 0) option = 2;
    }
    // Update Value in EEPROM if needed.
    if(EEPROM.read(dz_option_add) != option) EEPROM.write(dz_option_add, option);
    
    // 1 DZ all week?
    if(option == 0){
      // All Week Settings
      dz_set_times(dz_base_startH_add, dz_base_startM_add, dz_base_endH_add, dz_base_endM_add);
    }
    
    // Weekend/Weekday?
    if(option == 1){
      // Weekend Settings
      dz_set_times(dz_weekend_startH_add, dz_weekend_startM_add, dz_weekend_endH_add, dz_weekend_endM_add);
      
      // Weekday Settings
      dz_set_times(dz_weekday_startH_add, dz_weekday_startM_add, dz_weekday_endH_add, dz_weekday_endM_add);
      }
    
    // Every Day different?
    if(option == 2){
      // Sunday Settings
      dz_set_times(dz_0_startH_add, dz_0_startM_add, dz_0_endH_add, dz_0_endM_add);
      
      // Monday Settings
      dz_set_times(dz_1_startH_add, dz_1_startM_add, dz_1_endH_add, dz_1_endM_add);

      // Tuesday Settings
      dz_set_times(dz_2_startH_add, dz_2_startM_add, dz_2_endH_add, dz_2_endM_add);

      // Wednesday Settings
      dz_set_times(dz_3_startH_add, dz_3_startM_add, dz_3_endH_add, dz_3_endM_add);

      // Thursday Settings
      dz_set_times(dz_4_startH_add, dz_4_startM_add, dz_4_endH_add, dz_4_endM_add);

      // Friday Settings
      dz_set_times(dz_5_startH_add, dz_5_startM_add, dz_5_endH_add, dz_5_endM_add);

      // Saturday Settings
      dz_set_times(dz_6_startH_add, dz_6_startM_add, dz_6_endH_add, dz_6_endM_add);      
    }
  }
}




int set_hour(int current_hour, int current_minute){
  waitForRelease();
  if(current_hour == 255) current_hour = 0;
  if(current_minute == 255) current_minute = 0;
  // Button Variables
  int up_pressed, down_pressed;
  int x = 0;
  int b = 1;
  
  // Set the Hour
  while(x == 0){
    DateTime current_time = RTC.now();

    // Display Output.
    lcdprintTime(current_hour, current_minute, current_time.second(), b);
        
    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW) x += 1;
    
    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if(up_pressed == 15) current_hour += 1, up_pressed = 0;
    }
    else up_pressed = 0;
    
    if(digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if(down_pressed == 15) current_hour -= 1, down_pressed = 0;
    }
    else down_pressed = 0;
    
    if(current_hour > 23) current_hour = 0;
    if(current_hour < 0) current_hour = 23;
  }
  return current_hour;
}


int set_minute(int current_hour, int current_minute){
  waitForRelease();
  if(current_hour == 255) current_hour = 0;
  if(current_minute == 255) current_minute = 0;
  // Button Variables
  int up_pressed, down_pressed;
  int x = 0;
  int b = 2;
  
  // Set the Minute
  while(x == 0){
    DateTime current_time = RTC.now();
    
    lcdprintTime(current_hour, current_minute, current_time.second(), b);
    
    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW) x += 1;
    
    if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH) {
      up_pressed += 1;
      if(up_pressed == 15) current_minute += 1, up_pressed = 0;
    }
    else up_pressed = 0;
    
    if(digitalRead(DOWN_BUTTON) == LOW && digitalRead(UP_BUTTON) == HIGH) {
      down_pressed += 1;
      if(down_pressed == 15) current_minute -= 1, down_pressed = 0;
    }
    else down_pressed = 0;
    
    if(current_minute > 59) current_minute = 0;
    if(current_minute < 0) current_minute = 59;
  }
  return current_minute;
}

void dz_set_times(int startH_add, int startM_add, int endH_add, int endM_add){
  // Set Start Hour
  int startH = set_hour(EEPROM.read(startH_add), EEPROM.read(startM_add));
  if(EEPROM.read(startH_add) != startH) EEPROM.write(startH_add, startH);
  // Set Start Minute
  int startM = set_minute(EEPROM.read(startH_add), EEPROM.read(startM_add));
  if(EEPROM.read(startM_add) != startM) EEPROM.write(startM_add, startM);
  // Set End Hour
  int endH = set_hour(EEPROM.read(endH_add), EEPROM.read(endM_add));
  if(EEPROM.read(endH_add) != endH) EEPROM.write(endH_add, endH);
  // Set End Minute
  int endM = set_minute(EEPROM.read(endH_add), EEPROM.read(endM_add));
  if(EEPROM.read(endM_add) != endM) EEPROM.write(endM_add, endM);
}
