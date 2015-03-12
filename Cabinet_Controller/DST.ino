/* 
Here is where we will tell if we are in Daylights Savings Time
This is configurable. Just fill in the Month, which Week of the Month,
The Day (0 - 6 Sunday - Saturday) and the Hour to START and END on.
*/

boolean in_DST(){
  boolean dst = false; //Assume we're not in DST

  if(rtc_month > EEPROM.read(dst_start_month_add) && rtc_month < EEPROM.read(dst_end_month_add)) dst = true; //DST is happening!

  //Figure out what the date for the last day DST should start on.
  int previousSunday = rtc_day - rtc_dayOfWeek;
  
  // Calculating the start and end weeks.
  int start_week = (EEPROM.read(dst_start_week_add) * 7) - 7;
  int end_week = (EEPROM.read(dst_end_week_add) * 7) - 7;
  
  if (rtc_month == EEPROM.read(dst_start_month_add))
  {
    if(previousSunday > start_week) dst = true; 
  } 

  //In November we must be before the first Sunday to be dst.
  //That means the previous Sunday must be before the 1st.
  if(rtc_month == EEPROM.read(dst_end_month_add))
  {
    if(previousSunday <= end_week) dst = true;
  }
  
  // Make sure we are past 2am before switching to DST
  if (rtc_month == EEPROM.read(dst_start_month_add) && rtc_dayOfWeek == EEPROM.read(dst_start_dow_add) && rtc_hour < EEPROM.read(dst_start_hour_add)) dst = false;
  if (rtc_month == EEPROM.read(dst_end_month_add) && rtc_dayOfWeek == EEPROM.read(dst_end_dow_add) && rtc_hour < EEPROM.read(dst_end_hour_add)) dst = true;
  
  return dst;
}
