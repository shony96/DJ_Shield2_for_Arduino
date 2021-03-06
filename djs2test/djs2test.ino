/*
 DJ Shield 2 for Arduino - TEST sketch
 by dm9 records

  * Send Data on USB-Serial.(57600bps)
  
  more infomation : http://www.dm9records.com
  
  This code and schmantics is in Creative Commons 3.0 BY-SA
  http://creativecommons.org/licenses/by-sa/3.0/
  
  ----VERSION------
  10/--/2011 v1.0
  01/13/2012 v2.0 improve response
  
*/

#include <MsTimer2.h>

#include "Led.h"
#include "Pot.h"
#include "Sw.h"
#include "Re.h"

Led LED;
Pot POT = Pot();
Sw SW = Sw();
Re RE = Re();

int RE_Pos = 0;

unsigned long time = 0;

                                                                                                                                                                                                                                                                      void setup(){  
  Serial.begin(57600);
  POT.init();
  MsTimer2::set(3,re_Update);
  MsTimer2::start();
}

void loop(){
  time = millis();
  POT.update();
  SW.update();
  time = millis() - time;
  
  for(int i=0;i<13;i++){
    if(POT.changed(i)){
      Serial.print("POT ");
      Serial.print(i,DEC);
      Serial.print(" :");
      Serial.print(POT.value(i));
      Serial.print("  delay:");
      Serial.println(time);
    }
  }
  for(int i=0;i<12;i++){
    if(SW.changed(i)){
      Serial.print("SW ");
      Serial.print(i,DEC);
      Serial.print(" :");
      Serial.print(SW.value(i));
      Serial.print("  delay:");
      Serial.println(time);
    }
  }
  if(RE.changed()){
    RE_Pos = RE_Pos + RE.value();
    Serial.print("RE :");
    Serial.print(RE_Pos,DEC);
    Serial.print("  delay:");
    Serial.println(time);
  }
}

void re_Update(){
  RE.update();
}
