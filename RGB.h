/*
*  This Header file defines the setColor method for the RGB LEDs
*  Eight distingushable colors for Eight different notes  
*
*  @author: nuwanwre
*/

#include <Arduino.h>

void setColor(int clr, int rp, int gp, int bp, int del);


void setColor(int clr, int rp, int gp, int bp, int del)
{
  
  switch(clr){
    case 1:
              analogWrite(rp, 255);
              analogWrite(gp, 0);
              analogWrite(bp,0);
              break;
    
    case 2:
              analogWrite(rp, 255);
              analogWrite(gp, 165);
              analogWrite(bp,0);
              break;
    
    case 3:
              analogWrite(rp, 255);
              analogWrite(gp, 255);
              analogWrite(bp,0);
              break;    
              
    case 4:
              analogWrite(rp, 0);
              analogWrite(gp, 128);
              analogWrite(bp,0);
              break;    
    
    case 5:
              analogWrite(rp, 0);
              analogWrite(gp, 255);
              analogWrite(bp,255);
              break; 
           
    case 6:
              analogWrite(rp, 0);
              analogWrite(gp, 0);
              analogWrite(bp,255);
              break;   
             
    case 7:
              analogWrite(rp, 238);
              analogWrite(gp, 130);
              analogWrite(bp,238);
              break; 
    
    case 8:
              analogWrite(rp, 0);
              analogWrite(gp, 0);
              analogWrite(bp,0);
              break;    
  }
  delay(1000/del);
}
