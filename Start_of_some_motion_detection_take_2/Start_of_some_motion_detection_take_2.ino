#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;


// Defining Veriables to Pins
#define PIR 2
#define PIR_LED 13
#define OVERRIDE_LED 8

#define CAB_POWER 9
#define CAB_LIGHTS 10

#define CAB_POWER_SWITCH 6
#define CAB_LIGHTS_SWITCH 7
#define OVERRIDE 3

#define BRIGHT_POT 3

// Global Variables

// This is the last time the lights were told to turn on.
long last_time;

int timeout = 15;

int fade_delay = 10;
int max_brightness = 0;
int last_brightness = 0;

// Inital Setting for Dead Zone time.
int dz_start = 2300;
int dz_end = 800;

// variables used for current status
int override = 0;
int cab_power_on = 0;
int cab_lights_on = 0;

// variables used for time
// This is so I can be lazy and not pass these variables everywhere as they are global.
int rtc_year = 0;
int rtc_month = 0;
int rtc_day = 0;
int rtc_dayOfWeek = 0;
int rtc_hour = 0;
int rtc_minute = 0;
int rtc_second = 0;
long rtc_unixtime = 0;



void setup() {  
  // Setting up the Real Time Clock
  Wire.begin();
  RTC.begin();
  //Serial.begin(9600);
 
  // Setting Pin Modes
  pinMode(PIR, INPUT);
  pinMode(CAB_POWER, OUTPUT);
  pinMode(CAB_LIGHTS, OUTPUT);
  pinMode(CAB_POWER_SWITCH, INPUT);
  pinMode(CAB_LIGHTS_SWITCH, INPUT);
  pinMode(OVERRIDE, INPUT);
  pinMode(PIR_LED, OUTPUT);
  pinMode(OVERRIDE_LED, OUTPUT);
  //RTC.adjust(DateTime(2015, 3, 8, 1, 59, 40));
  //RTC.adjust(DateTime(__DATE__, __TIME__));
  
  digitalWrite(OVERRIDE_LED, LOW);
  
  // Checking to see if the RTC is running, If not print message.
  if (! RTC.isrunning()) {
    Serial.println("RTC NOT RUNNING");
    int x = 0;
    while(x == 0){
      digitalWrite(PIR_LED, HIGH);
      delay(1000);
      digitalWrite(PIR_LED, LOW);
      delay(1000);
      if(digitalRead(OVERRIDE) == LOW){
        RTC.adjust(DateTime(__DATE__, __TIME__));
        x = 1;
      }
    }
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  // Read in the current time
  //delay (500);
  Serial.println("---------------------");
  DateTime rtc_now = RTC.now();
  
  rtc_year = rtc_now.year();
  rtc_month = rtc_now.month();
  rtc_day = rtc_now.day();
  rtc_dayOfWeek = rtc_now.dayOfWeek();
  rtc_hour = rtc_now.hour();
  rtc_minute = rtc_now.minute();
  rtc_second = rtc_now.second();
  rtc_unixtime = rtc_now.unixtime();

  if(in_DST2() == 1){
    rtc_hour = rtc_hour + 1;
  }
  Serial.print("RTC Date: ");
  Serial.print(rtc_now.month());
  Serial.print("-");
  Serial.print(rtc_now.day());
  Serial.print("-");
  Serial.println(rtc_now.year());
  
  Serial.print("RTC TIME: ");
  Serial.print(rtc_now.hour());
  Serial.print(":");
  Serial.print(rtc_now.minute());
  Serial.print(":");
  Serial.println(rtc_now.second());
  
  Serial.print("DST Date: ");
  Serial.print(rtc_month);
  Serial.print("-");
  Serial.print(rtc_day);
  Serial.print("-");
  Serial.println(rtc_year);
  
  Serial.print("DST Time: ");
  Serial.print(rtc_hour);
  Serial.print(":");
  Serial.print(rtc_minute);
  Serial.print(":");
  Serial.println(rtc_second);
  
  // Get the value for the max brightness.
  max_brightness = read_pot();
  
  if(max_brightness != last_brightness && cab_lights_on == 1){
    analogWrite(CAB_LIGHTS, max_brightness);
    last_brightness = max_brightness;
  }
  // read in switch setting
  int cab_power_setting = digitalRead(CAB_POWER_SWITCH);
  int cab_lights_setting = digitalRead(CAB_LIGHTS_SWITCH);
  
  // Check the override button
  override = digitalRead(OVERRIDE);
  
  // read the PIR
  int motion = read_PIR();
  
  // Check if in deadzone
  int dead_zone = in_dead_zone(int_time());  
  
  // Control the Override button light depending on what is happening
  // Turn the light on if in the dead zone AND the Cab power, and Lights are both off.
  // Also if at least one of the switches are set to ON.
  // If no switch is set to on. Then nothing will happen when the button is pressed.
  
  if(dead_zone == 1 && (cab_power_setting == 0 || cab_lights_setting == 0) && (cab_power_on == 0 && cab_lights_on == 0)){
    digitalWrite(OVERRIDE_LED, HIGH);
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
  for(int fade = max_level; fade >= 0; fade--){
    analogWrite(CAB_LIGHTS, fade);
    delay(fade_delay);
  }
  return 0;
}


int fade_in(int max_level){
  for(int fade = 0; fade <= max_level; fade++){
    analogWrite(CAB_LIGHTS, fade);
    delay(fade_delay);
  }
  return 1;
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


int in_dead_zone(int current){
  if(dz_start < dz_end){
    if(dz_start <= current && current < dz_end){
      return 1;
    }
    else{
      return 0;
    }
  }
  else{
    if(! (dz_end <= current && current < dz_start)){
      return 1;
    }
    else {
      return 0;
    }
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

int read_pot(){
  int pot_value = analogRead(BRIGHT_POT) / 4;
  return pot_value;
}


// DST Settings
int dst_start_month = 3;
int dst_start_week = 1;
int dst_start_dow = 0;
int dst_start_hour = 2;

int dst_end_month = 11;
int dst_end_week = 1;
int dst_end_dow = 0;
int dst_end_hour = 2;

/* The RTC will return the following data in INT
YYYY/MM/DD HH:MM:SS DayOfWeek

Day of week will be 0 - 6
0 = Sunday - 6 = Saturday

*/


int in_DST(){
  if(rtc_month >= dst_start_month && rtc_month <= dst_end_month){
    Serial.println("inside Month");
    if((rtc_day > (dst_start_week * 7) - 7 && rtc_day <= dst_start_week * 7) && (rtc_day > (dst_end_week * 7) - 7 && rtc_day <= dst_end_week * 7)){
      Serial.println("inside Week");
      Serial.println(rtc_dayOfWeek);
      Serial.println(dst_start_dow);
      Serial.println(dst_end_dow);
      if(rtc_dayOfWeek >= dst_start_dow && rtc_dayOfWeek <= dst_end_dow){
        Serial.println("inside DOW");
        Serial.println(rtc_hour);
        Serial.println(dst_start_hour);
        Serial.println(dst_end_hour);
        if(rtc_hour >= dst_start_hour && rtc_hour < dst_end_hour){
          Serial.println("inside hour");
          // INSIDE DST
          return 1;
        }
        else{
          return 0;
        }
      }
      else{
        return 0;
      }
    }
    else{
      return 0;
    }
  }
  else{
    return 0;
  }
}


int in_DST1(){
  long current_int_dst_check = (rtc_month * 100000) + (rtc_day * 1000) + (rtc_dayOfWeek * 100) + rtc_hour;
  Serial.print("current dst int");
  Serial.println(current_int_dst_check);
  long start_int_dst_check = (dst_start_month * 100000) + (dst_start_week * 1000) + (dst_start_dow * 100) + dst_start_hour;
  Serial.print("start dst int");
  Serial.println(start_int_dst_check);
  long end_int_dst_check = (dst_end_month * 100000) + (dst_end_week * 1000) + (dst_end_dow * 100) + dst_end_hour;
  Serial.print("end dst int");
  Serial.println(end_int_dst_check);
  long current_int_time_test = (12 * 100000) + (31 * 1000) + (6 * 100) + 23;
  Serial.print("test dst int");
  Serial.println(current_int_time_test);
  
  if(current_int_dst_check >= start_int_dst_check && current_int_dst_check < end_int_dst_check){
    return 1;
  }
  else{
    return 0;
  }
}


int in_DST2(){
  /* So for this attempt What I am going to do is this
      Figure out the Unix time for NOW.
      Figure out what the Unix time for the Start would be.
        - Create a Date Time Object with the future date
        - Figure out the Date of the specified Week / Day.
          (What is the date of The Second Sunday of March)
      Figure out with the Unix time for the End would be.
        - Same as Start
        */
  long dst_start_unix = 0;
  long dst_end_unix = 2;
  
  Serial.print("Current Unix Time: ");
  Serial.println(rtc_unixtime);
  Serial.print("DST Start Unix Time: ");
  Serial.println(dst_start_unix);
  Serial.print("DST End Unix Time: ");
  Serial.println(dst_end_unix);
  
  if(dst_start_unix < rtc_unixtime && rtc_unixtime <= dst_end_unix){
    return 1;
  }
  else{
    return 0;
  }
  
}
