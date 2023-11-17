void updateEncoder(){
  int currentCLK = digitalRead(CLK);
  int currentDT = digitalRead(DT);
  // String currentDIR = "";
  if(currentCLK != formerCLK && currentCLK ==1){
   if(digitalRead(DT) != currentCLK){
     counter++;
    //  currentDIR ="CW";
   } else {
     counter++;
    //  currentDIR = "CCW";
     }
  }
  formerCLK = currentCLK;
}
