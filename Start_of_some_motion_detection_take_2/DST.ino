/* 
Here is where we will tell if we are in Daylights Savings Time
This is configurable. Just fill in the Month, which Week of the Month,
The Day (0 - 6 Sunday - Saturday) and the Hour to START and END on.

At some point I plan on making this settable via a menu.
*/

// DST Start Settings
int dst_start_month = 3;
int dst_start_week = 2;
int dst_start_dow = 0;
int dst_start_hour = 2;

// DST End Settings
int dst_end_month = 11;
int dst_end_week = 1;
int dst_end_dow = 0;
int dst_end_hour = 2;

boolean in_DST(){
  boolean dst = false; //Assume we're not in DST

  if(rtc_month > dst_start_month && rtc_month < dst_end_month) dst = true; //DST is happening!

  //Figure out what the date for the last day DST should start on.
  int previousSunday = rtc_day - rtc_dayOfWeek;
  
  // Calculating the start and end weeks.
  int start_week = (dst_start_week * 7) - 7;
  int end_week = (dst_end_week * 7) - 7;
  
  if (rtc_month == dst_start_month)
  {
    if(previousSunday > start_week) dst = true; 
  } 

  //In November we must be before the first Sunday to be dst.
  //That means the previous Sunday must be before the 1st.
  if(rtc_month == dst_end_month)
  {
    if(previousSunday <= end_week) dst = true;
  }
  
  // Make sure we are past 2am before switching to DST
  if (rtc_month == dst_start_month && rtc_dayOfWeek == dst_start_dow && rtc_hour < dst_start_hour) dst = false;
  if (rtc_month == dst_end_month && rtc_dayOfWeek == dst_end_dow && rtc_hour < dst_end_hour) dst = true;
  
  return dst;
}
