void waitForRelease(){
  while(digitalRead(UP_BUTTON) == LOW || digitalRead(DOWN_BUTTON) == LOW){
  }
}
