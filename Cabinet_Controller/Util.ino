void intial_read_EEPROM(){
  // DST Settings
  /* dst_start_month = EEPROM.read(0);
  dst_start_week = EEPROM.read(1);
  dst_start_dow = EEPROM.read(2);
  dst_start_hour = EEPROM.read(3);
  
  // DST End Settings
  dst_end_month = EEPROM.read(4);
  dst_end_week = EEPROM.read(5);
  dst_end_dow = EEPROM.read(6);
  dst_end_hour = EEPROM.read(7);
  */
  
  // Dead Zone Settings
  // Any Dead Zone at all?
  dead_zone = EEPROM.read(dead_zone_add);
  
  // Default Deadzone
  dz_custom_default = EEPROM.read(dz_custom_default_add);
  dz_startH_default = EEPROM.read(dz_startH_default_add);
  dz_startM_default = EEPROM.read(dz_startM_default_add);
  dz_endH_default = EEPROM.read(dz_endH_default_add);
  dz_endM_default = EEPROM.read(dz_endM_default_add);
  
  // Custom Dead Zones Per day.
  dz_custom_0 = EEPROM.read(dz_custom_0_add);
  dz_startH_0 = EEPROM.read(dz_startH_0_add);
  dz_startM_0 = EEPROM.read(dz_startM_0_add);
  dz_endH_0 = EEPROM.read(dz_endH_0_add);
  dz_endM_0 = EEPROM.read(dz_endM_0_add);
  
  /*dz_custom_1 = EEPROM.read(dz_custom_1_add);
  dz_start_1 = EEPROM.read(dz_start_1_add);
  dz_end_1 = EEPROM.read(dz_end_1_add);
  
  dz_custom_2 = EEPROM.read(dz_custom_2_add);
  dz_start_2 = EEPROM.read(dz_start_2_add);
  dz_end_2 = EEPROM.read(dz_end_2_add);
  
  dz_custom_3 = EEPROM.read(dz_custom_3_add);
  dz_start_3 = EEPROM.read(dz_start_3_add);
  dz_end_3 = EEPROM.read(dz_end_3_add);
  
  dz_custom_4 = EEPROM.read(dz_custom_4_add);
  dz_start_4 = EEPROM.read(dz_start_4_add);
  dz_end_4 = EEPROM.read(dz_end_4_add);
  
  dz_custom_5 = EEPROM.read(dz_custom_5_add);
  dz_start_5 = EEPROM.read(dz_start_5_add);
  dz_end_5 = EEPROM.read(dz_end_5_add);
  
  dz_custom_6 = EEPROM.read(dz_custom_6_add);
  dz_start_6 = EEPROM.read(dz_start_6_add);
  dz_end_6 = EEPROM.read(dz_end_6_add);
  */
  
  
  // Fade Delay
  //base_fade_delay = EEPROM.read(33);
  
  
  // Timeout Delay
  //timeout = EEPROM.read(34);
}

