void printTime(int HH, int MM, int SS){
  Serial.print(HH);
  Serial.print(":");
  Serial.print(MM);
  Serial.print(":");
  Serial.println(SS);
}

void printDate(int MONTH, int DAY, int YEAR){
  Serial.print(MONTH);
  Serial.print("-");
  Serial.print(DAY);
  Serial.print("-");
  Serial.println(YEAR);
}

void printDate2(int MONTH, int DAY){
  Serial.print(MONTH);
  Serial.print("-");
  Serial.println(DAY);
}
