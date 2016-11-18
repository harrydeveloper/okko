//Setup variables. Tweak them for different results.
const int MAX_BUFFERSIZE = 50 ;
const int DELAY = 0;
//lowpass fiter variables.
long delayAlpha = 0.5;
long delay_prev = 0;
long overall_c = 1;

//integer values stored for ranges.
int x1Reach;
int x2Reach;
int x3Reach;
int x4Reach;
int x5Reach;
int x6Reach;
int endLine;

//current status, zone in which the systems was last spotted at.:
int current_zone

/*
 * returned vlaue meanings.
 * 
 * int;;
 * 
 * 0 = out of range
 * 1 = x1 matrix.
 * 2 = x2 matrix.
 * 3 = x3 matrix.
 * 4 = x4 matrix.
 * 5 = x5 matrix.
 * 6 = x6 matrix.
 * 
 */
int currentRead() // function that returns currently read value.
{
  
  if()
  {
    
  }
  else if()
  {
    
  }
  else if()
  {
    
  }
  else if()
  {
    
  }
  else if()
  {
    
  }
  else if()
  {
    
  }
  else
  {
    // range has fallen in dead zone.
    return current_zone;
  }
}

void setup()
{
  // put your setup code here, to run once:

}

void loop() 
{
  // put your main code here, to run repeatedly:

}
