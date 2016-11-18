// GAME 1

int rr=1; int rg=2; int rb=3;
int lr=4; int lg=5; int lb=6;

void setup()
{
   for (int i = 1; i < 7; i++){
     pinMode(i, OUTPUT);
   }
   
   demo();
     
}

void loop(){
  
}



void demo(){
  
  setColor(1, lr, lg, lb, 8);
  setColor(1, lr, lg ,lb, 8);
  setColor(7, rr, rg ,rb, 8);
  setColor(7, rr, rg ,rb, 8);
  setColor(2, rr, rg ,rb, 8);
  setColor(2, rr, rg ,rb, 8);
  setColor(7, rr, rg ,rb, 4);
  
  setColor(6, rr, rg ,rb, 8);
  setColor(6, rr, rg ,rb, 8);
  setColor(3, rr, rg ,rb, 8);
  setColor(3, rr, rg ,rb, 8);
  setColor(4, rr, rg ,rb, 8);
  setColor(4, rr, rg ,rb, 8);
  setColor(1, lr, lg ,lb, 4);
  
  setColor(7, rr, rg ,rb, 8);
  setColor(7, rr, rg ,rb, 8);
  setColor(6, rr, rg ,rb, 8);
  setColor(6, rr, rg ,rb, 7);
  setColor(3, rr, rg ,rb, 6);
  setColor(3, rr, rg ,rb, 6);
  setColor(4, lr, lg ,lb, 4);
  
  setColor(7, rr, rg ,rb, 8);
  setColor(7, rr, rg ,rb, 8);
  setColor(6, rr, rg ,rb, 8);
  setColor(6, rr, rg ,rb, 7);
  setColor(3, rr, rg ,rb, 6);
  setColor(3, rr, rg ,rb, 6);
  setColor(4, lr, lg ,lb, 4);
  
  setColor(1, lr, lg, lb, 8);
  setColor(1, lr, lg ,lb, 8);
  setColor(7, rr, rg ,rb, 8);
  setColor(7, rr, rg ,rb, 8);
  setColor(2, rr, rg ,rb, 8);
  setColor(2, rr, rg ,rb, 8);
  setColor(7, rr, rg ,rb, 4);
  
  setColor(6, rr, rg ,rb, 8);
  setColor(6, rr, rg ,rb, 8);
  setColor(3, rr, rg ,rb, 8);
  setColor(3, rr, rg ,rb, 8);
  setColor(4, rr, rg ,rb, 8);
  setColor(4, rr, rg ,rb, 8);
  setColor(1, lr, lg ,lb, 4);
  
}



boolean isInRange(){
 
   return true; 
}

void setColor(int clr, int rp, int gp, int bp, int del)
{
  
  switch(clr){
    case 1:   //RED
              analogWrite(rp, 255);
              analogWrite(gp, 0);
              analogWrite(bp,0);
              break;
    
    case 2:   //ORANGE
              analogWrite(rp, 255);
              analogWrite(gp, 165);
              analogWrite(bp,0);
              break;
    
    case 3:   //YELLOW
              analogWrite(rp, 255);
              analogWrite(gp, 255);
              analogWrite(bp,0);
              break;    
              
    case 4:   //GREEN
              analogWrite(rp, 0);
              analogWrite(gp, 128);
              analogWrite(bp,0);
              break;    
    
    case 5:   //CYAN
              analogWrite(rp, 0);
              analogWrite(gp, 255);
              analogWrite(bp,255);
              break; 
             
    case 6:   //BLUE
              analogWrite(rp, 0);
              analogWrite(gp, 0);
              analogWrite(bp,255);
              break;   
             
    case 7:   //VIOLET
              analogWrite(rp, 238);
              analogWrite(gp, 130);
              analogWrite(bp,238);
              break; 
    
    case 8:   //WHITE
              analogWrite(rp, 0);
              analogWrite(gp, 0);
              analogWrite(bp,0);
              break;    
  }
  delay(2500/del);
  
  delay(50);
  
}
