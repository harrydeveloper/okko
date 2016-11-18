//copy from here:
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

// Function declarations
int read();
long readDistance();
long lowPassFilter(long);
void generateTone(int, long);
long normalizer(long);
int getLED(int[]);
int getColor(int[]);
int getDuration(int[]);
int getNote(int[]);
void updateIndex();
void setColor(int, int, int, int, int);

long delayAlpha = 0.5;
long delay_prev = 0;
long overall_c = 1;
long trueAvg = 0;
//config global consts.
const int MAX_BUFFERSIZE = 20;
const int DELAY = 5;
const int OFFSET = 30;
//line limit variables:
//integer values stored for ranges.
const int x1Val = 563;
const int x2Val = 1114;
const int x3Val = 1675;
const int x4Val = 2227;
const int x5Val = 2782;
const int x6Val = 3353;
const int endLine = 3930;
long buffer[MAX_BUFFERSIZE];
const int trig = 13; // attach pin 3 to Trig
const int echo = 12; //attach pin 4 to Echo
const int SPEAKER_OUT = 9;
long counter = 0;
long duration = 0;




//LEDS
int leftRed = 1; int leftGreen = 2; int leftBlue =3;
int rightRed = 4; int rightGreen = 5; int rightBlue = 6; 

// ===============================================================
// Song Arrays with necessary colors and LEDs

// the color codes
int twinkleColors[] = { 1, 1, 7, 7, 2, 2, 7,
                        6, 6, 3, 3, 4, 4, 1,
                        7, 7, 6, 6, 3, 3, 4,
                        7, 7, 6, 6, 3, 3, 4,
                        1, 1, 7, 7, 2, 2, 7,
                        6, 6, 3, 3, 4, 4, 1};

// The LED to be blinked. 0 for left 1, 1 for right
int twinkleLED[] = { 0, 0, 1, 1, 1, 1, 1,
                     1, 1, 1, 1, 1, 1, 0,
                     1, 1, 1, 1, 1, 1, 0,
                     1, 1, 1, 1, 1, 1, 0,      
                     0, 0, 1, 1, 1, 1, 1,
                     1, 1, 1, 1, 1, 1, 0};
                     
// LED blink duration
int twinkleDuration[] = { 8, 8, 8, 8, 8, 8, 4,
                          8, 8, 8, 8, 8, 8, 4,
                          8, 8, 8, 7, 6, 6, 4,
                          8, 8, 8, 7, 6, 6, 4,
                          8, 8, 8, 8, 8, 8, 4,
                          8, 8, 8, 8, 8, 8, 4};

//C = 1   D =2    E = 3   F = 4   G = 5   A = 6                          
int twinkleNotes[] = { 1, 1, 5, 5, 6, 6, 5,
                       4, 4, 3, 3, 2, 2, 1,
                       5, 5, 4, 4, 3, 3, 2,
                       5, 5, 4, 4, 3, 3, 2,
                       1, 1, 5, 5, 6, 6, 5,
                       4, 4, 3, 3, 2, 2, 1};
                       
                          
//Temp Data for indexes

int colorIndex = 0;
int LEDIndex =  0;
int durationIndex = 0;
int noteIndex = 0;
int dura = 500;
                          
// ==================================================================              

void setup() 
{
// initialize serial communication:
Serial.begin(112500);
pinMode(echo,INPUT);
pinMode(SPEAKER_OUT, OUTPUT);
//Serial.print("Doing average tests on ");
//Serial.print(MAX_BUFFERSIZE);
//Serial.println(" readings");
//TODO : set pin 8 to OUTPUT
pinMode(8, OUTPUT);

for (int i = 1; i < 7; i++){
 pinMode(i, OUTPUT);
} 
}

void loop()
{
  //TODO : Init game
  
  // First, let's light up the relevant LED, and see whether the user steps on it.
  // If the user steps on the right box, we play the tune.
   //Serial.print("Size of arry:"); Serial.print(sizeof(twinkleColors));
   
   

  // set left LED which shoes the current box to be stepped
  setColor(getColor(twinkleColors), leftRed, leftGreen, leftBlue, getDuration(twinkleDuration));
  
  if(colorIndex + 1 < sizeof(twinkleColors)/2)
  setColor(getColor(twinkleColors)+1, rightRed, rightGreen, rightBlue, getDuration(twinkleDuration));
  
  while(true){
      if(read() == getNote(twinkleNotes)) { generateTone(getNote(twinkleNotes), getDuration(twinkleDuration)); break; }
  }
  
  //Serial.print("Note : "); Serial.print(getNote(twinkleNotes)); Serial.print("\n");
  generateTone(0, dura);
  updateIndex();
  //delay(10);
}
// function that returns the latest read value. refer to global conastants for tones.
int read()
{
    
    float parameter = readDistance();
    parameter = lowPassFilter(parameter);
    parameter = normalizer(parameter);  
     //returns matrix value from specified range index.
     if(x1Val + OFFSET <= parameter && parameter < x2Val - OFFSET) // C
    {
      return 1;
    }
    else if(x2Val + OFFSET <= parameter && parameter < x3Val - OFFSET) // D
    {
      return 2;
    }
    else if(x3Val + OFFSET <= parameter && parameter < x4Val - OFFSET) // E
    {
      return 3;
    }
    else if(x4Val + OFFSET <= parameter && parameter < x5Val - OFFSET) // F
    {
      return 4;
    }
    else if(x5Val + OFFSET <= parameter && parameter < x6Val - OFFSET) // G
    {
      return 5;
    }
    else if(x6Val + OFFSET <= parameter && parameter < endLine - OFFSET) // A
    {
      return 6;
    }
    else 
    {
      if(parameter > x1Val && parameter < endLine)
      {
        return 7;
      }
      else
      {
        return 0;
      }
    }
}

// =====================================    FUNCTIONS    =================================================:

//functions:
long readDistance()
{
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);

// The same pin is used to read the signal from the PING))): a HIGH
// pulse whose duration is the time (in microseconds) from the sending
// of the ping to the reception of its echo off of an object.
  return pulseIn(echo, HIGH);
}
long lowPassFilter(long newVal)
{
  long save = newVal;
  newVal = delayAlpha*duration + (1-delayAlpha)*delay_prev;
  delay_prev = save;
  return newVal;
}

void generateTone(int index, long duration)
{
  //duration = 1000/duration;
  Serial.println("Sound!!!");
  switch(index)
  {
    case 0:
    //no Tone...
     noTone(SPEAKER_OUT);
     delay(duration);
     break;
     case 1:
     tone(SPEAKER_OUT, 261.63);
     delay(duration);
     break;
     case 2:
     tone(SPEAKER_OUT, 293.66);
     delay(duration);
     break;
     case 3:
     tone(SPEAKER_OUT, 329.63);
     delay(duration);
     break;
     case 4:
     tone(SPEAKER_OUT, 349.23);
     delay(duration);
     break;
     case 5:
     tone(SPEAKER_OUT, 392.00);
     delay(duration);
     break;
     case 6:
     tone(SPEAKER_OUT, 440.00);
     delay(duration);
     break;
     case 7:
     //do nothing
     break;
  }
}
long normalizer(long newVal)
{
  if(counter == MAX_BUFFERSIZE)
    {
      counter = 0;
    }
  
  long lcounter = 0;
  long sum = 0;
  boolean doLoop = true;
  while(doLoop == true)
  {
    sum = sum + buffer[lcounter];
    lcounter++;
    if(lcounter == MAX_BUFFERSIZE)
    {
      doLoop = false;
    }
  }
  long average = sum/MAX_BUFFERSIZE;
  //Serial.print("Average for the batch: ");
  //Serial.print(average);
  
  trueAvg = ((trueAvg * (overall_c-1)) + average)/(overall_c);
  overall_c++;

  //Serial.print("   Total current average: ");
  //Serial.println(trueAvg);
 
//  Serial.print("Packet:  ");
//  Serial.print(counter);
//  Serial.print("  ");
//  Serial.print(duration);
//  Serial.print(" microsecods read...");
  buffer[counter] = newVal;
//  Serial.print("  buffer with index of ");
//  Serial.print(counter);
//  Serial.print(" Has been set to:  ");
//  Serial.println(buffer[counter]);
  counter++;
  delay(DELAY);
  return average;
}

//=============================================================================
// This function focuses on returning the next input Note and Light up the LEDs
// 

int getColor(int clr[]){
   int temp = clr[colorIndex];
   //Serial.print("Color :");
   //Serial.print(temp);
   //Serial.print("\n");
   return temp;
}

// This function returns which LED to be blinked next

int getLED(int led[]){
   int temp = led[LEDIndex];
   return temp;
}

// This function returns which duration needs to adapted next

int getDuration(int dur[]){
   int temp = dur[durationIndex];
   
   return 2000/temp;
}

// This function returns which Npte needs to adapted next

int getNote(int note[]){
   int temp = note[noteIndex];
   return temp;
}

void updateIndex(){
  colorIndex++;
  LEDIndex++;
  durationIndex++;
  noteIndex++;
}

// This function sets the color

void setColor(int clr, int rp, int gp, int bp, int del)
{
  
  switch(clr){
    case 1: //GREEN
              analogWrite(rp, 255);
              analogWrite(gp, 0);
              analogWrite(bp,0);
              break;
    
    case 2://VIOLET
              analogWrite(rp, 30);
              analogWrite(gp, 128);
              analogWrite(bp,128);
              break;
    
    case 3://GREEN
              analogWrite(rp, 128);
              analogWrite(gp, 128);
              analogWrite(bp,0);
              break;    
              
    case 4://RED
              analogWrite(rp, 0);
              analogWrite(gp, 255);
              analogWrite(bp,0);
              break;    
    
    case 5://VIOLET
              analogWrite(rp, 0);
              analogWrite(gp, 255);
              analogWrite(bp,255);
              break; 
           
    case 6://BLUE
              analogWrite(rp, 0);
              analogWrite(gp, 0);
              analogWrite(bp,255);
              break;   
             
    case 7://CYAN
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
  //delay(5000/del);
  
  //delay(50);
  
}




