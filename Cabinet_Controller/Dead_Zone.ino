// Global Variables for Dead Zone stuff.
int dz_custom_0, dz_startH_0, dz_startM_0, dz_endH_0, dz_endM_0;
int dz_custom_1, dz_startH_1, dz_startM_1, dz_endH_1, dz_endM_1;
int dz_custom_2, dz_startH_2, dz_startM_2, dz_endH_2, dz_endM_2;
int dz_custom_3, dz_startH_3, dz_startM_3, dz_endH_3, dz_endM_3;
int dz_custom_4, dz_startH_4, dz_startM_4, dz_endH_4, dz_endM_4;
int dz_custom_5, dz_startH_5, dz_startM_5, dz_endH_5, dz_endM_5;
int dz_custom_6, dz_startH_6, dz_startM_6, dz_endH_6, dz_endM_6;

int dz_day_custom, dz_custom_default, default_dz_end, default_dz_start, dead_zone;

int dz_startH_default, dz_startM_default, dz_endH_default, dz_endM_default;

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

void custom_DZ(){
  if(dz_custom_default == 1){
    // Now that we know we want daily DZ's lets figure out what they are going to be for each day.
    
    // Read in what day of the week it is and get the values for each day.
    if(rtc_dayOfWeek == 0) {
      dz_day_custom = dz_custom_0;
      if(dz_day_custom == 1) dz_start = int_time_passed(dz_startH_0, dz_startM_0), dz_end = int_time_passed(dz_endH_0, dz_endM_0);
    }
    /*if(rtc_dayOfWeek == 1) {
      dz_day_custom = dz_custom_1;
      if(dz_day_custom == 1) dz_start = dz_start_1, dz_end = dz_end_1;
    }
    if(rtc_dayOfWeek == 2) {
      dz_day_custom = dz_custom_2;
      if(dz_day_custom == 1) dz_start = dz_start_2, dz_end = dz_end_2;
    }
    if(rtc_dayOfWeek == 3) {
      dz_day_custom = dz_custom_3;
      if(dz_day_custom == 1) dz_start = dz_start_3, dz_end = dz_end_3;
    }
    if(rtc_dayOfWeek == 4) {
      dz_day_custom = dz_custom_4;
      if(dz_day_custom == 1) dz_start = dz_start_4, dz_end = dz_end_4;
    }
    if(rtc_dayOfWeek == 5) {
      dz_day_custom = dz_custom_5;
      if(dz_day_custom == 1) dz_start = dz_start_5, dz_end = dz_end_5;
    }
    if(rtc_dayOfWeek == 6) {
      dz_day_custom = dz_custom_6;
      if(dz_day_custom == 1) dz_start = dz_start_6, dz_end = dz_end_6;
    }
    if(dz_day_custom == 0){
      dz_start = default_dz_start;
      dz_end = default_dz_end;
    }*/
  }
  else{
    dz_start = default_dz_start;
    dz_end = default_dz_end;
  }
}
