//copy from here:
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
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

void setup() 
{
// initialize serial communication:
Serial.begin(112500);
pinMode(echo,INPUT);
pinMode(SPEAKER_OUT, OUTPUT);
Serial.print("Doing average tests on ");
Serial.print(MAX_BUFFERSIZE);
Serial.println(" readings");
}

void loop()
{

}
// function that returns the latest read value. refer to global conastants for tones.
int read()
{
    parameter = readDistance();
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
  Serial.print("Average for the batch: ");
  Serial.print(average);
  
  trueAvg = ((trueAvg * (overall_c-1)) + average)/(overall_c);
  overall_c++;

  Serial.print("   Total current average: ");
  Serial.println(trueAvg);
 
//  Serial.print("Packet:  ");
//  Serial.print(counter);
//  Serial.print("  ");
//  Serial.print(duration);
//  Serial.print(" microsecods read...");
  buffer[counter] = duration;
//  Serial.print("  buffer with index of ");
//  Serial.print(counter);
//  Serial.print(" Has been set to:  ");
//  Serial.println(buffer[counter]);
  counter++;
  delay(DELAY);
  return average;
}



