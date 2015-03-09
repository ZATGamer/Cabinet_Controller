#include <Wire.h>
#include <RTClib.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

RTC_DS1307 RTC;

// Defining Veriables to Pins
#define PIR 2
#define PHOTO 2

#define PIR_LED 13
#define OVERRIDE_LED 3
#define CAB_POWER_LED 6
#define CAB_LIGHTS_LED 5

#define CAB_POWER 9
#define CAB_LIGHTS 10

#define CAB_POWER_SWITCH 4
#define CAB_LIGHTS_SWITCH 7
#define OVERRIDE 8

#define BRIGHT_POT 3

#define UP_BUTTON 11
#define DOWN_BUTTON 12

// Setting up SoftwareSerial to talk to the LCD pannel.
SoftwareSerial lcd(20, 14);

// Global Variables

////////// EEPROM ADDRESSES //////////
// Dead Zone Settings address.
int dead_zone_add = 0;
int dz_custom_default_add = 1;
int dz_startH_default_add = 2;
int dz_startM_default_add = 3;
int dz_endH_default_add = 4;
int dz_endM_default_add = 5;

int dz_custom_0_add = 6;
int dz_startH_0_add = 7;
int dz_startM_0_add = 8;
int dz_endH_0_add = 9;
int dz_endM_0_add = 10;

int dz_custom_1_add = 7;
int dz_startH_1_add = 5;
int dz_startM_1_add = 5;
int dz_endH_1_add = 6;
int dz_endM_1_add = 6;

int dz_custom_2_add = 10;
int dz_startH_2_add = 5;
int dz_startM_2_add = 5;
int dz_endH_2_add = 6;
int dz_endM_2_add = 6;

int dz_custom_3_add = 13;
int dz_startH_3_add = 5;
int dz_startM_3_add = 5;
int dz_endH_3_add = 6;
int dz_endM_3_add = 6;

int dz_custom_4_add = 16;
int dz_startH_4_add = 5;
int dz_startM_4_add = 5;
int dz_endH_4_add = 6;
int dz_endM_4_add = 6;

int dz_custom_5_add = 19;
int dz_startH_5_add = 5;
int dz_startM_5_add = 5;
int dz_endH_5_add = 6;
int dz_endM_5_add = 6;

int dz_custom_6_add = 22;
int dz_startH_6_add = 5;
int dz_startM_6_add = 5;
int dz_endH_6_add = 6;
int dz_endM_6_add = 6;

// DST Settings Addresses
int dst_start_month_add = 25;
int dst_start_week_add = 26;
int dst_start_dow_add = 27;
int dst_start_hour_add = 28;
  
  // DST End Settings
int dst_end_month_add = 29;
int dst_end_week_add = 30;
int dst_end_dow_add = 31;
int dst_end_hour_add = 32;

// Fade Delay
int base_fade_delay_add = 33;
  
// Timeout Delay
int timeout_add = 34;

////////// END EEPROM ADDRESSES //////////





// This is the last time the lights were told to turn on.
long last_time;
int last_second, last_minute;

// Global Variables for Entering Menues.
int enter_settime, enter_settings, enter_dead_zone_settings;

// This is how long the Cab Lights and Power will stay on with no motion detected.
int timeout = 15;

// Cab Lights Fade in/out delay.
int base_fade_delay = 10;

// 
int max_brightness, last_brightness, switch_brightness;

// Inital Setting for Dead Zone time.
int dz_start = 2300;
int dz_end = 800;

// variables used for current status
int override = 0;
int cab_power_on = 0;
int cab_lights_on = 0;

// variables used for time
// This is so I can be lazy and not pass these variables everywhere as they are global.
int rtc_year, rtc_month, rtc_day, rtc_dayOfWeek, rtc_hour, rtc_minute, rtc_second;
long rtc_unixtime = 0;

// Defining functions for optional variables.
void lcdprintTime(int HH, int MM, int SS, int b = 0);
void lcdprintDate(int MONTH, int DAY, int SS = 0, int b = 0);
void lcdprintYear(int YEAR, int SS = 0, int b = 0);

void setup() {  
  // Setting up the Real Time Clock
  Wire.begin();
  RTC.begin();
  
  // For Debugging.
  Serial.begin(9600);
  
  // Inital LCD Settings
  lcd_inital_start();
  
  // Setting Pin Modes
  pinMode(PIR, INPUT);
  pinMode(PHOTO, INPUT);
  pinMode(CAB_POWER, OUTPUT);
  pinMode(CAB_LIGHTS, OUTPUT);
  pinMode(CAB_POWER_LED, OUTPUT);
  pinMode(CAB_LIGHTS_LED, OUTPUT);
  pinMode(CAB_POWER_SWITCH, INPUT);
  pinMode(CAB_LIGHTS_SWITCH, INPUT);
  pinMode(OVERRIDE, INPUT);
  pinMode(PIR_LED, OUTPUT);
  pinMode(OVERRIDE_LED, OUTPUT);
  pinMode(UP_BUTTON, INPUT);
  pinMode(DOWN_BUTTON, INPUT);
  
  digitalWrite(OVERRIDE_LED, LOW);
  
  // Checking to see if the RTC is running, If not print message.
  if (! RTC.isrunning()) {
    clearLCD();
    lcd.print("8888");
    int x = 0;
    int y = 0;
    while(x == 0){
      if(y < 15000) digitalWrite(OVERRIDE_LED, HIGH), y += 1;
      else digitalWrite(OVERRIDE_LED, LOW), y += 1;
      if(y == 30000) y = 0;
      if(digitalRead(OVERRIDE) == LOW){
        RTC.adjust(DateTime(2015, 1, 1, 1, 1, 1));
        settime();
        x = 1;
      }
    }
  }
  
  // Read in all the Stored Global Variables from EEPROM.
  intial_read_EEPROM();
  for(int x = 0; x < 35; x++){
    int value = EEPROM.read(x);
    Serial.print(x);
    Serial.print(": ");
    Serial.println(value);
  }
}


void loop() {
  // Get Current time.
  current_time();
  
  if(in_DST()){
    rtc_hour += 1;
  }
  
  //custom_DZ();
    
  // Get the value for the max brightness.
  max_brightness = analogRead(BRIGHT_POT) / 4;
  int photo_cell = analogRead(PHOTO) / 4;
  
  // read in switch setting
  int cab_power_setting = digitalRead(CAB_POWER_SWITCH);
  int cab_lights_setting = digitalRead(CAB_LIGHTS_SWITCH);
  
  // Check the override button
  override = digitalRead(OVERRIDE);
  
  // read the PIR
  int motion = read_PIR();
  
  // Check if in deadzone
  int dead_zone = in_dead_zone(int_time());
  
  if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == LOW){
    enter_settime += 1;
    if(enter_settime == 100) settime(), enter_settime = 0;
  }
  else enter_settime = 0;
  
  if(digitalRead(UP_BUTTON) == LOW && digitalRead(DOWN_BUTTON) == HIGH){
    enter_settings += 1;
    if(enter_settings == 100) settings(), enter_settings = 0;
  }
  else enter_settings = 0;
  
  if(digitalRead(UP_BUTTON) == HIGH && digitalRead(DOWN_BUTTON) == LOW){
    enter_dead_zone_settings += 1;
    if(enter_dead_zone_settings == 100) deadZoneSettings(), enter_dead_zone_settings = 0;
  }
  else enter_dead_zone_settings = 0;
  
  // Update Output
  if(last_second != rtc_second){
    last_second = rtc_second; 
  
    // Display Date with Transitions. 
      if(rtc_second >= 45 && rtc_second <= 52){
        if(rtc_second == 45) wipeLeft(), lcdprintDate(rtc_month, rtc_day);
        if(rtc_second > 45 && rtc_second < 48) lcdprintDate(rtc_month, rtc_day);
        if(rtc_second == 48) wipeLeft(), lcdprintYear(rtc_year);
        if(rtc_second > 48 && rtc_second < 52) lcdprintYear(rtc_year);
        if(rtc_second == 52) wipeLeft(), lcdprintTime(rtc_hour, rtc_minute, rtc_second);
      }
      else{
        lcdprintTime(rtc_hour, rtc_minute, rtc_second);
      }
  }
  
  // TEMP code for Development
  lcdprintSecond(rtc_second);
  
    
  if(max_brightness != last_brightness && cab_lights_on == 1){
    analogWrite(CAB_LIGHTS, max_brightness);
    last_brightness = max_brightness;
  }
  
  if(photo_cell <= 50){
    switch_brightness = 10;
  }
  else{
    switch_brightness = 255;
  }
  
  if(cab_power_setting == LOW) {
    analogWrite(CAB_POWER_LED, switch_brightness);
  }
  else{
    digitalWrite(CAB_POWER_LED, LOW);
  }
  if(cab_lights_setting == LOW){
    analogWrite(CAB_LIGHTS_LED, switch_brightness);
  }
  else{
    digitalWrite(CAB_LIGHTS_LED, LOW);
  }
  
  // Control the Override button light depending on what is happening
  // Turn the light on if in the dead zone AND the Cab power, and Lights are both off.
  // Also if at least one of the switches are set to ON.
  // If no switch is set to on. Then nothing will happen when the button is pressed.
  
  if(dead_zone == 1 && (cab_power_setting == 0 || cab_lights_setting == 0) && (cab_power_on == 0 && cab_lights_on == 0)){
    analogWrite(OVERRIDE_LED, switch_brightness);
  }
  else{
    digitalWrite(OVERRIDE_LED, LOW);
  }
  
  if(override == LOW){
    digitalWrite(OVERRIDE_LED, LOW);
  }
  
  // If in deadzone and Override pressed Turn on lights and power as by settings.
  if(dead_zone == 1 && override == LOW){
    override_on(cab_power_setting, cab_lights_setting);
  }
  
  // If in deadzone and Lights or Power is on. Check if it needs to be turned off.
  if(dead_zone == 0 || cab_power_on == 1 || cab_lights_on == 1){    
    control_lights(cab_power_setting, cab_lights_setting, motion);
  }
}


void control_lights(int cab_power_setting, int cab_lights_setting, int motion){
  // This is the function that turns the lights on and off.
  if(motion == HIGH){
    // MOTION DETECTED
    // Turn on lights
    last_time = rtc_unixtime; 
    //////// CAB LIGHTS ////////
    // Check to see if the Cab LIGHTS should be ON.
    if(cab_lights_setting == LOW){  //LOW == YES
      // IF YES turn the LIGHTS ON.
      if(cab_lights_on != 1){
        cab_lights_on = fade_in(max_brightness);
      }
    }
    else{
      if(cab_lights_on == 1){
        cab_lights_on = fade_out(max_brightness);
      }
    }
    //////// CAB POWER ////////
    // Check to see if the Cab Power should be on.
    if(cab_power_setting == LOW){  //LOW == YES
      // IF YES turn POWER ON.
      digitalWrite(CAB_POWER, HIGH);
      cab_power_on = 1;
    }
    else{
      // IF NO turn POWER OFF.
      digitalWrite(CAB_POWER, LOW);
      cab_power_on = 0;
      }
  }
  else{
    // NO MOTION DETECTED
    digitalWrite(PIR_LED, LOW);
    // check to see how long no motion detected
    if(rtc_unixtime > last_time + timeout){
      // This means the timeout has been reachted and we are going to turn the lights off.
      if(cab_power_on == 1){
        digitalWrite(CAB_POWER, LOW);
        cab_power_on = 0;
      }
      if(cab_lights_on == 1){
        cab_lights_on = fade_out(max_brightness);
      }
    }
  }
}


int fade_out(int max_level){
  lcdDash();
  int fdelay = fade_delay(max_level);
  for(int fade = max_level; fade >= 0; fade--){
    analogWrite(CAB_LIGHTS, fade);
    delay(fdelay);
  }
  return 0;
}


int fade_in(int max_level){
  lcdDash();
  int fdelay = fade_delay(max_level);
  for(int fade = 0; fade <= max_level; fade++){
    analogWrite(CAB_LIGHTS, fade);
    delay(fdelay);
  }
  return 1;
}


int fade_delay(int max_brightness){
  if(max_brightness != 0){
    int temp = (base_fade_delay * 255);
    int temp2 = temp / max_brightness;
    return temp2;
  }
  else{
    return base_fade_delay;
  }
}


int int_time(){
  if(rtc_hour != 0){
    int time = (rtc_hour * 100) + rtc_minute;
    return time;
  }
  else{
    int time = rtc_minute;
    return time;
  }
}

int int_time_passed(int HH, int MM){
  if(HH != 0){
    int time = (HH * 100) + MM;
    return time;
  }
  else{
    int time = MM;
    return time;
  }
}


void override_on(int power, int lights){
  if(lights == LOW){
    cab_lights_on = fade_in(max_brightness);
  }
  if(power == LOW){
    digitalWrite(CAB_POWER, HIGH);
    cab_power_on = 1; 
  }
  last_time = rtc_unixtime;
}


int check_timeout(){
  if(last_time > rtc_unixtime + timeout){
    return 1;
  }
  else{
    return 0;
  }
}

int read_PIR(){
  int motion = digitalRead(PIR);
  
  // Toggle the PIR Status Light
  if(motion == HIGH){
    digitalWrite(PIR_LED, HIGH);
  }
  else{
    digitalWrite(PIR_LED, LOW);
  }
  return motion;
}

void current_time() {
  // Read in the current time and update the Global Variables.
  DateTime rtc_now = RTC.now();
  
  rtc_year = rtc_now.year();
  rtc_month = rtc_now.month();
  rtc_day = rtc_now.day();
  rtc_dayOfWeek = rtc_now.dayOfWeek();
  rtc_hour = rtc_now.hour();
  rtc_minute = rtc_now.minute();
  rtc_second = rtc_now.second();
  rtc_unixtime = rtc_now.unixtime();
}
